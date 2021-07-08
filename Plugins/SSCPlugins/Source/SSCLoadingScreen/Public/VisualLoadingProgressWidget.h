// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSCPlugins/Public/SSCUI/SSCPanelWidget.h"
#include "VisualLoadingProgressWidget.generated.h"



/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadStreamLevelsFinishDelegate, float, Progress);

UCLASS()
class SSCLOADINGSCREEN_API UVisualLoadingProgressWidget : public USSCPanelWidget
{
	GENERATED_BODY()
	
public:
	UVisualLoadingProgressWidget(const FObjectInitializer& ObjectInitializer);

	void ModelInit()override;
	void ModelLoading()override;


	UPROPERTY(BlueprintAssignable)
		FLoadStreamLevelsFinishDelegate LoadingFinishDelegate;
public:
	
	UFUNCTION()
		void BindLoadingStateEvnt();

	
public:
	UPROPERTY(BlueprintReadOnly)
		int32 LevelLoaded;
	UPROPERTY(BlueprintReadOnly)
		int32 TotalLevel;
	UPROPERTY(BlueprintReadOnly)
		float LoadingProgress;
};

