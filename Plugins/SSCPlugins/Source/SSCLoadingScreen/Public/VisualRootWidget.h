// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCPlugins/Public/SSCUI/SSCRootWidget.h"
#include "VisualRootWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSCLOADINGSCREEN_API UVisualRootWidget : public USSCRootWidget
{
	GENERATED_BODY()

public:
	virtual void ModelInit()override;
	
protected:

	void ShowLoadingProgress();
};
