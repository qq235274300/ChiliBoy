// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

struct FTipSettings;
class SSCLOADINGSCREEN_API SSTipWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSTipWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FTipSettings& Settings);
};
