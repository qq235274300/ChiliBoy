// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

struct FBackgroundSettings;
class FDeferredCleanupSlateBrush;

class SSCLOADINGSCREEN_API SSBackgroundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSBackgroundWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs,FBackgroundSettings Settings);

private:
	TSharedPtr<FDeferredCleanupSlateBrush> ImageBrush;
	
};
