// Fill out your copyright notice in the Description page of Project Settings.


#include "SSLoadingCompleteText.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSLoadingCompleteText::Construct(const FArguments& InArgs, const FLoadingCompleteTextSettings& CompleteTextSettings)
{
	CompleteTextColor = CompleteTextSettings.Appearance.ColorAndOpacity.GetSpecifiedColor();
	CompleteTextAnimationSpeed = CompleteTextSettings.AnimationSpeed;

	ChildSlot
		[
			SNew(STextBlock)
			.Font(CompleteTextSettings.Appearance.Font)
		.ShadowOffset(CompleteTextSettings.Appearance.ShadowOffset)
		.ShadowColorAndOpacity(CompleteTextSettings.Appearance.ShadowColorAndOpacity)
		.Justification(CompleteTextSettings.Appearance.Justification)
		.Text(CompleteTextSettings.LoadingCompleteText)
		.ColorAndOpacity(this, &SSLoadingCompleteText::GetLoadingCompleteTextColor)
		.Visibility(this, &SSLoadingCompleteText::GetLoadingCompleteTextVisibility)
		];

	// Register animated image sequence active timer event
	if (CompleteTextSettings.bFadeInFadeOutAnim && !bIsActiveTimerRegistered)
	{
		bIsActiveTimerRegistered = true;
		RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &SSLoadingCompleteText::AnimateText));
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

EVisibility SSLoadingCompleteText::GetLoadingCompleteTextVisibility() const
{
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Visible : EVisibility::Hidden;
}

FSlateColor SSLoadingCompleteText::GetLoadingCompleteTextColor() const
{
	return CompleteTextColor;
}

EActiveTimerReturnType SSLoadingCompleteText::AnimateText(double InCurrentTime, float InDeltaTime)
{
	const float MinAlpha = 0.1f;
	const float MaxAlpha = 1.0f;

	float TextAlpha = CompleteTextColor.A;

	if (TextAlpha >= MaxAlpha)
	{
		bCompleteTextReverseAnim = true;
	}
	else if (TextAlpha <= MinAlpha)
	{
		bCompleteTextReverseAnim = false;
	}

	if (!bCompleteTextReverseAnim)
	{
		TextAlpha += InDeltaTime * CompleteTextAnimationSpeed;
	}
	else
	{
		TextAlpha -= InDeltaTime * CompleteTextAnimationSpeed;
	}

	CompleteTextColor.A = TextAlpha;

	return EActiveTimerReturnType::Continue;
}
