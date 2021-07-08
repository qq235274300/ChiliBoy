// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SSLoadingWidget.h"

struct FLoadingWidgetSettings;
/**
 * 
 */
class SSCLOADINGSCREEN_API SSHorizontalLoadingWidget : public SSLoadingWidget
{
public:
	SLATE_BEGIN_ARGS(SSHorizontalLoadingWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FLoadingWidgetSettings& Settings);
};
