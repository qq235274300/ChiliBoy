// Fill out your copyright notice in the Description page of Project Settings.


#include "SSTipWidget.h"
#include "SlateOptMacros.h"
#include "SSCLoadingFunctionLibrary.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSTipWidget::Construct(const FArguments& InArgs, const FTipSettings& Settings)
{
	if (Settings.TipText.Num() > 0)
	{
		int32 TipIndex = FMath::RandRange(0, Settings.TipText.Num() - 1);

		if (Settings.bSetDisplayTipTextManually == true)
		{
			if (Settings.TipText.IsValidIndex(USSCLoadingFunctionLibrary::GetDisplayTipTextIndex()))
			{
				TipIndex = USSCLoadingFunctionLibrary::GetDisplayTipTextIndex();
			}
		}

		ChildSlot
			[
				SNew(STextBlock)
				.ColorAndOpacity(Settings.Appearance.ColorAndOpacity)
			.Font(Settings.Appearance.Font)
			.ShadowOffset(Settings.Appearance.ShadowOffset)
			.ShadowColorAndOpacity(Settings.Appearance.ShadowColorAndOpacity)
			.Justification(Settings.Appearance.Justification)
			.WrapTextAt(Settings.TipWrapAt)
			.Text(Settings.TipText[TipIndex])
			];

	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
