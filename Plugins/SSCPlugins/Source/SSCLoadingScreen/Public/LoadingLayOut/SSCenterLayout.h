// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SSLoadingScreenLayout.h"

/**
 * 
 */

struct FLoadingScreenSettings;
struct FCenterLayoutSettings;

class SSCLOADINGSCREEN_API SSCenterLayout : public SSLoadingScreenLayout
{
public:
	SLATE_BEGIN_ARGS(SSCenterLayout)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FCenterLayoutSettings& LayoutSettings);
};
