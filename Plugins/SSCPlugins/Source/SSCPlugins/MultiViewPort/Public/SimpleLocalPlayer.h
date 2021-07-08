// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "SimpleViewManager.h"
#include "SceneView.h"
#include "SimpleLocalPlayer.generated.h"


//FSceneView ���ص�ǰ��һ��� ���ڶ�Ӧ��ϵ(������Ҿ�������SCENEVIEW) CalcSceneView
//ע�� ����˼·�Ǵ�������viewPort,������������ܿ�ѡ������RenderTarget SceneRenderer����BufferΪǰ��һ��
//Ps: UE4�Ѿ�ʵ�ַ������� CreatePlayer :) 

DECLARE_LOG_CATEGORY_EXTERN(Log_SimpleLocalPlayer, Log, All);

UCLASS(classGroup = "SSCMultiViews",BlueprintType,Blueprintable,meta = (ShortTooltip = "user for MultiViews"))
class SSCPLUGINS_API USimpleLocalPlayer : public ULocalPlayer
{
	GENERATED_UCLASS_BODY()
		
public:
	virtual void PostInitProperties()override;
	virtual void BeginDestroy()override;
	virtual void FinishDestroy()override;
	//����ӿ�λ�Ƽ���ת
	virtual void GetViewPoint(FMinimalViewInfo& OutViewInfo, EStereoscopicPass StereoPass = eSSP_FULL) const override;
	virtual FSceneView* CalcSceneView(class FSceneViewFamily* ViewFamily,
		FVector& OutViewLocation,
		FRotator& OutViewRotation,
		FViewport* Viewport,
		class FViewElementDrawer* ViewDrawer = NULL,
		EStereoscopicPass StereoPass = eSSP_FULL)override;
	//��� ViewOrigin �� ViewRotationMatrix
	virtual bool GetProjectionData(FViewport* Viewport, EStereoscopicPass StereoPass, FSceneViewProjectionData& ProjectionData) const override;

	virtual void OffsetViewLocationAndRotation(FMinimalViewInfo& InOutViewInfo) const;

	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	bool CalcSceneViewInitOptions_Custom(
		struct FSceneViewInitOptions& ViewInitOptions,
		FViewport* Viewport,
		const int32 IndexOfView,
		class FViewElementDrawer* ViewDrawer = NULL,
		EStereoscopicPass StereoPass = eSSP_FULL);

	virtual FSceneView* CalcMultiViews(class FSceneViewFamily* ViewFamily,
		FVector& OutViewLocation,
		FRotator& OutViewRotation,
		FViewport* Viewport,
		class FViewElementDrawer* ViewDrawer = NULL,
		EStereoscopicPass StereoPass = eSSP_FULL);

	virtual FSceneView* CalcView_Custom(class FSceneViewFamily* ViewFamily,
		FVector& OutViewLocation,
		FRotator& OutViewRotation,
		FViewport* Viewport,
		const FView ViewSetting,
		const int32 IndexOfView,
		class FViewElementDrawer* ViewDrawer = NULL,
		EStereoscopicPass StereoPass = eSSP_FULL);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		bool EnableMultiViews = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		FViewsManager ViewsManager;
	
	static const int32 MaxNumOfViews;
		
public:
	UFUNCTION(BlueprintCallable,  Category = "SSCMultiViews")
		int32 GetMaxNumOfViews()
	{
		return MaxNumOfViews;
	}
	
	

private:
	TArray<FSceneViewStateReference> ViewStateArray;
	int32 CurrentViewIndex = 0;
};
