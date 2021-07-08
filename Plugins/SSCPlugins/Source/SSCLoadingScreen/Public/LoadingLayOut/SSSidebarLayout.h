// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
struct FLoadingScreenSettings;
struct FSidebarLayoutSettings;

class SSCLOADINGSCREEN_API SSSidebarLayout : public SSLoadingScreenLayout
{
public:
	SLATE_BEGIN_ARGS(SSSidebarLayout)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FSidebarLayoutSettings& LayoutSettings);
};
