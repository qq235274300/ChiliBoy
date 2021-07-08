// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

struct FLoadingScreenSettings;
struct FDualSidebarLayoutSettings;

class SSCLOADINGSCREEN_API SSDualSidebarLayout : public SSLoadingScreenLayout
{
public:
	SLATE_BEGIN_ARGS(SSDualSidebarLayout)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FDualSidebarLayoutSettings& LayoutSettings);
};
