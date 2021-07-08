// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
struct FLoadingCompleteTextSettings;

class SSCLOADINGSCREEN_API SSLoadingCompleteText : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSLoadingCompleteText)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FLoadingCompleteTextSettings& CompleteTextSettings);

	// Getter for text visibility
	EVisibility GetLoadingCompleteTextVisibility() const;

	// Getter for complete text color and opacity
	FSlateColor GetLoadingCompleteTextColor() const;

	/** Active timer event for animating the image sequence */
	EActiveTimerReturnType AnimateText(double InCurrentTime, float InDeltaTime);

private:
	// Complete text color
	FLinearColor CompleteTextColor = FLinearColor::White;

	// Complete text fade in or fade out animation
	bool bCompleteTextReverseAnim = false;

	// Complete text animation speed
	float CompleteTextAnimationSpeed = 1.0f;

	// Active timer registered flag
	bool bIsActiveTimerRegistered = false;
};
