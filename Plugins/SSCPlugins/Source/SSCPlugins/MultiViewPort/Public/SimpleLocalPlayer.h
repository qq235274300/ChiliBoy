// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "SimpleViewManager.h"
#include "SceneView.h"
#include "SimpleLocalPlayer.generated.h"


//FSceneView 返回当前玩家画面 存在对应关系(两个玩家就是两个SCENEVIEW) CalcSceneView
//注： 分屏思路是创建两个viewPort,如果不考虑性能可选择两个RenderTarget SceneRenderer后者Buffer为前者一倍
//Ps: UE4已经实现分屏方案 CreatePlayer :) 

DECLARE_LOG_CATEGORY_EXTERN(Log_SimpleLocalPlayer, Log, All);

UCLASS(classGroup = "SSCMultiViews",BlueprintType,Blueprintable,meta = (ShortTooltip = "user for MultiViews"))
class SSCPLUGINS_API USimpleLocalPlayer : public ULocalPlayer
{
	GENERATED_UCLASS_BODY()
		
public:
	virtual void PostInitProperties()override;
	virtual void BeginDestroy()override;
	virtual void FinishDestroy()override;
	//获得视口位移及旋转
	virtual void GetViewPoint(FMinimalViewInfo& OutViewInfo, EStereoscopicPass StereoPass = eSSP_FULL) const override;
	virtual FSceneView* CalcSceneView(class FSceneViewFamily* ViewFamily,
		FVector& OutViewLocation,
		FRotator& OutViewRotation,
		FViewport* Viewport,
		class FViewElementDrawer* ViewDrawer = NULL,
		EStereoscopicPass StereoPass = eSSP_FULL)override;
	//获得 ViewOrigin 及 ViewRotationMatrix
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
