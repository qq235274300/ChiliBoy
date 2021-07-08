// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleLocalPlayer.h"
#include "Engine/LocalPlayer.h"
#include "Misc/FileHelper.h"
#include "EngineDefines.h"
#include "EngineGlobals.h"
#include "Engine/Scene.h"
#include "Camera/CameraTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "UObject/UObjectAnnotation.h"
#include "Logging/LogScopedCategoryAndVerbosityOverride.h"
#include "UObject/UObjectIterator.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/PlayerController.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "UnrealEngine.h"
#include "EngineUtils.h"

#include "Matinee/MatineeActor.h"
#include "Matinee/InterpData.h"
#include "Matinee/InterpGroupInst.h"
#include "Net/OnlineEngineInterface.h"
#include "SceneManagement.h"
#include "PhysicsPublic.h"
#include "SkeletalMeshTypes.h"
#include "HAL/PlatformApplicationMisc.h"

#include "IHeadMountedDisplay.h"
#include "IXRTrackingSystem.h"
#include "IXRCamera.h"
#include "SceneViewExtension.h"
#include "Net/DataChannel.h"
#include "GameFramework/PlayerState.h"




#define LOCTEXT_NAMESPACE "SimpleLocalPlayer"
DEFINE_LOG_CATEGORY(Log_SimpleLocalPlayer);
DECLARE_CYCLE_STAT(TEXT("CalcMultiViews"), STAT_CalcMultiViews, STATGROUP_Engine);
const int32 USimpleLocalPlayer::MaxNumOfViews = 10;

USimpleLocalPlayer::USimpleLocalPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USimpleLocalPlayer::PostInitProperties()
{
	Super::PostInitProperties();
	ViewStateArray.SetNum(MaxNumOfViews);
	for (auto& stat : ViewStateArray)
	{
		stat.Allocate();
	}
}

void USimpleLocalPlayer::BeginDestroy()
{
	Super::BeginDestroy();
}

void USimpleLocalPlayer::FinishDestroy()
{
	if (true)
	{
		for (FSceneViewStateReference& viewStatetmp : ViewStateArray)
		{
			viewStatetmp.Destroy();
		}
	}

	Super::FinishDestroy();
}

bool USimpleLocalPlayer::GetProjectionData(FViewport* Viewport, EStereoscopicPass StereoPass, FSceneViewProjectionData& ProjectionData) const
{
	if (Super::GetProjectionData(Viewport, StereoPass, ProjectionData))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void USimpleLocalPlayer::GetViewPoint(FMinimalViewInfo& OutViewInfo, EStereoscopicPass StereoPass /*= eSSP_FULL*/) const
{
	Super::GetViewPoint(OutViewInfo, StereoPass);
	if (EnableMultiViews) 
	{
		if (ViewsManager.ViewsArray.Num() > CurrentViewIndex)
		{
			FView CurrentView = ViewsManager.ViewsArray[CurrentViewIndex];
			if (CurrentView.ViewPointType == EViewPointType::BindToViewTarget)
			{
				CurrentView.BindToViewTargte.GetViewInfo(OutViewInfo);
			}
		}

		OffsetViewLocationAndRotation(OutViewInfo);
	}
	
}

void USimpleLocalPlayer::OffsetViewLocationAndRotation(FMinimalViewInfo& InOutViewInfo) const
{
	if (EnableMultiViews)
	{
		if (ViewsManager.ViewsArray.Num() > CurrentViewIndex)
		{
			FView CurrentView = ViewsManager.ViewsArray[CurrentViewIndex];

			FVector ViewLocation = InOutViewInfo.Location;
			FRotator ViewRotation = InOutViewInfo.Rotation;

			const FTransform ViewRelativeTransform(CurrentView.RotationOffsetOfViewPort, CurrentView.LocationOffsetOfViewPort);
			const FTransform ViewWorldTransform(ViewRotation, ViewLocation);
			FTransform NewViewWorldTransform = ViewRelativeTransform * ViewWorldTransform;

			ViewLocation = NewViewWorldTransform.GetLocation();
			ViewRotation = NewViewWorldTransform.GetRotation().Rotator();

			InOutViewInfo.Location = ViewLocation;
			InOutViewInfo.Rotation = ViewRotation;
		}
	}
}


FSceneView* USimpleLocalPlayer::CalcSceneView(class FSceneViewFamily* ViewFamily, FVector& OutViewLocation, FRotator& OutViewRotation, FViewport* Viewport, class FViewElementDrawer* ViewDrawer /*= NULL*/, EStereoscopicPass StereoPass /*= eSSP_FULL*/)
{
	if (!EnableMultiViews)
	{
		return 	Super::CalcSceneView(ViewFamily,
			OutViewLocation,
			OutViewRotation,
			Viewport,
			ViewDrawer,
			StereoPass);
	}
	else
	{
		return 	CalcMultiViews(ViewFamily, OutViewLocation, OutViewRotation, Viewport, ViewDrawer, StereoPass);
	}
}





bool USimpleLocalPlayer::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return Super::Exec(InWorld, Cmd, Ar);
}

bool USimpleLocalPlayer::CalcSceneViewInitOptions_Custom(struct FSceneViewInitOptions& ViewInitOptions, FViewport* Viewport, const int32 IndexOfView,
	class FViewElementDrawer* ViewDrawer /*= NULL*/, EStereoscopicPass StereoPass /*= eSSP_FULL*/)
{
	if ((PlayerController == NULL) || (Size.X <= 0.f) || (Size.Y <= 0.f) || (Viewport == NULL))
	{
		return false;
	}
	if (GetProjectionData(Viewport, StereoPass, ViewInitOptions) == false)
	{
		return false;
	}

	if (!ViewInitOptions.IsValidViewRectangle())
	{
		return false;
	}

	if (PlayerController->PlayerCameraManager != NULL)
	{
		if (PlayerController->PlayerCameraManager->bEnableFading)
		{
			ViewInitOptions.OverlayColor = PlayerController->PlayerCameraManager->FadeColor;
			ViewInitOptions.OverlayColor.A = FMath::Clamp(PlayerController->PlayerCameraManager->FadeAmount, 0.0f, 1.0f);
		}

	
		if (PlayerController->PlayerCameraManager->bEnableColorScaling)
		{
			ViewInitOptions.ColorScale = FLinearColor(
				PlayerController->PlayerCameraManager->ColorScale.X,
				PlayerController->PlayerCameraManager->ColorScale.Y,
				PlayerController->PlayerCameraManager->ColorScale.Z
			);
		}

		
		ViewInitOptions.bInCameraCut = PlayerController->PlayerCameraManager->bGameCameraCutThisFrame;
	}

	check(PlayerController && PlayerController->GetWorld());

	switch (StereoPass)
	{
	case eSSP_FULL:
	case eSSP_LEFT_EYE:
		ViewInitOptions.SceneViewStateInterface = ViewStateArray[IndexOfView].GetReference();
		break;

	case eSSP_RIGHT_EYE:
		ViewInitOptions.SceneViewStateInterface = ViewStateArray[IndexOfView].GetReference();
		break;
	}

	ViewInitOptions.ViewActor = PlayerController->GetViewTarget();
	ViewInitOptions.PlayerIndex = GetControllerId();
	ViewInitOptions.ViewElementDrawer = ViewDrawer;
	ViewInitOptions.BackgroundColor = FLinearColor::Black;
	ViewInitOptions.LODDistanceFactor = PlayerController->LocalPlayerCachedLODDistanceFactor;
	ViewInitOptions.StereoPass = StereoPass;
	ViewInitOptions.WorldToMetersScale = PlayerController->GetWorldSettings()->WorldToMeters;
	ViewInitOptions.CursorPos = Viewport->HasMouseCapture() ? FIntPoint(-1, -1) : FIntPoint(Viewport->GetMouseX(), Viewport->GetMouseY());
	ViewInitOptions.OriginOffsetThisFrame = PlayerController->GetWorld()->OriginOffsetThisFrame;

	return true;
}

FSceneView* USimpleLocalPlayer::CalcMultiViews(class FSceneViewFamily* ViewFamily, FVector& OutViewLocation, FRotator& OutViewRotation, FViewport* Viewport,
	class FViewElementDrawer* ViewDrawer /*= NULL*/, EStereoscopicPass StereoPass /*= eSSP_FULL*/)
{
	FSceneView* View = nullptr;
	for (int32 IndexOfView = 0; IndexOfView < ViewsManager.ViewsArray.Num()
		&& IndexOfView < MaxNumOfViews; IndexOfView++)
	{
		CurrentViewIndex = IndexOfView;
		FView CurrentView = ViewsManager.ViewsArray[IndexOfView];
		FSceneView* ViewTemp = CalcView_Custom(ViewFamily, OutViewLocation, OutViewRotation, Viewport, CurrentView, IndexOfView, ViewDrawer, StereoPass);
		if (View == nullptr)
		{
			View = ViewTemp;
		}
	}

	return 	View;
}

FSceneView* USimpleLocalPlayer::CalcView_Custom(class FSceneViewFamily* ViewFamily, FVector& OutViewLocation, FRotator& OutViewRotation, FViewport* Viewport, const FView ViewSetting, const int32 IndexOfView, class FViewElementDrawer* ViewDrawer /*= NULL*/, EStereoscopicPass StereoPass /*= eSSP_FULL*/)
{
	SCOPE_CYCLE_COUNTER(STAT_CalcMultiViews);

	FVector2D OriginCache = Origin;
	FVector2D SizeCache = Size;
	Origin = FVector2D(ViewSetting.LocationAndSizeOnScreen.X, ViewSetting.LocationAndSizeOnScreen.Y);
	Size = FVector2D(ViewSetting.LocationAndSizeOnScreen.Z, ViewSetting.LocationAndSizeOnScreen.W);

	FSceneViewInitOptions ViewInitOptions;

	if (!CalcSceneViewInitOptions_Custom(ViewInitOptions, Viewport, IndexOfView, ViewDrawer, StereoPass))
	{
		return nullptr;
	}
	FMinimalViewInfo ViewInfo;
	GetViewPoint(ViewInfo, StereoPass);
	OutViewLocation = ViewInfo.Location;
	OutViewRotation = ViewInfo.Rotation;
	ViewInitOptions.bUseFieldOfViewForLOD = ViewInfo.bUseFieldOfViewForLOD;
	ViewInitOptions.FOV = ViewInfo.FOV;
	ViewInitOptions.DesiredFOV = ViewInfo.DesiredFOV;

	ViewInitOptions.ViewFamily = ViewFamily;

	if (!PlayerController->bRenderPrimitiveComponents)
	{
		ViewInitOptions.ShowOnlyPrimitives.Emplace();
	}
	else
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_BuildHiddenComponentList);
		PlayerController->BuildHiddenComponentList(OutViewLocation, /*out*/ ViewInitOptions.HiddenPrimitives);
	}

	EngineShowFlagOrthographicOverride(ViewInitOptions.IsPerspectiveProjection(), ViewFamily->EngineShowFlags);

	FSceneView* const View = new FSceneView(ViewInitOptions);

	View->ViewLocation = OutViewLocation;
	View->ViewRotation = OutViewRotation;

	ViewFamily->Views.Add(View);

	{
		//此处与引擎冲突
		//View->StartFinalPostprocessSettings(OutViewLocation);

		if (PlayerController->PlayerCameraManager)
		{
			TArray<FPostProcessSettings> const* CameraAnimPPSettings;
			TArray<float> const* CameraAnimPPBlendWeights;
			PlayerController->PlayerCameraManager->GetCachedPostProcessBlends(CameraAnimPPSettings, CameraAnimPPBlendWeights);

			for (int32 PPIdx = 0; PPIdx < CameraAnimPPBlendWeights->Num(); ++PPIdx)
			{
				View->OverridePostProcessSettings((*CameraAnimPPSettings)[PPIdx], (*CameraAnimPPBlendWeights)[PPIdx]);
			}
		}
		View->OverridePostProcessSettings(ViewInfo.PostProcessSettings, ViewInfo.PostProcessBlendWeight);

		View->EndFinalPostprocessSettings(ViewInitOptions);
	}

	for (int ViewExt = 0; ViewExt < ViewFamily->ViewExtensions.Num(); ViewExt++)
	{
		ViewFamily->ViewExtensions[ViewExt]->SetupView(*ViewFamily, *View);
	}

	

	Origin = OriginCache;
	Size = SizeCache;

	return View;
}

#undef LOCTEXT_NAMESPACE