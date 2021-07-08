// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Images/SThrobber.h"
/**
 * 
 */
class FDeferredCleanupSlateBrush;
struct FLoadingWidgetSettings;


class SSCLOADINGSCREEN_API SSLoadingWidget : public SCompoundWidget
{
public:
	/** Active timer event for animating the image sequence */
	EActiveTimerReturnType AnimatingImageSequence(double InCurrentTime, float InDeltaTime);

	/** Gets the combined value of the animation properties as a single SThrobber::EAnimation value. */
	SThrobber::EAnimation GetThrobberAnimation(FThrobberSettings ThrobberSettings) const;

	/** Construct loading icon*/
	void ConstructLoadingIcon(const FLoadingWidgetSettings& Settings);

protected:
	// Placeholder widgets
	TSharedRef<SWidget> LoadingIcon = SNullWidget::NullWidget;
	// Image slate brush list
	TArray<TSharedPtr<FDeferredCleanupSlateBrush>> CleanupBrushList;
	// Current image sequence index
	int32 ImageIndex = 0;
	// Play image sequence in reverse
	bool bPlayReverse = false;

	bool bIsActiveTimerRegistered = false;
};
