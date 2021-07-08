// Fill out your copyright notice in the Description page of Project Settings.


#include "SSLetterboxLayout.h"
#include "SlateOptMacros.h"
#include "LoadingLayOut/SSBackgroundWidget.h"
#include "LoadingLayOut/SSHorizontalLoadingWidget.h"
#include "LoadingLayOut/SSVerticalLoadingWidget.h"
#include "LoadingLayOut/SSTipWidget.h"
#include "LoadingLayOut/SSLoadingCompleteText.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSLetterboxLayout::Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FLetterboxLayoutSettings& LayoutSettings)
{
	// Root widget and background
	TSharedRef<SOverlay> Root = SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SSBackgroundWidget, Settings.Background)
		];

	// Placeholder for loading widget
	TSharedRef<SWidget> LoadingWidget = SNullWidget::NullWidget;
	if (Settings.LoadingWidget.LoadingWidgetType == ELoadingWidgetType::LWT_Horizontal)
	{
		LoadingWidget = SNew(SSHorizontalLoadingWidget, Settings.LoadingWidget);
	}
	else
	{
		LoadingWidget = SNew(SSVerticalLoadingWidget, Settings.LoadingWidget);
	}


	if (LayoutSettings.bIsLoadingWidgetAtTop)
	{
		// Add a border widget at top, then add Loading widget
		Root->AddSlot()
			.HAlign(LayoutSettings.TopBorderHorizontalAlignment)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.TopBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(LayoutSettings.LoadingWidgetAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.LoadingWidgetAlignment.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.TopBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSLetterboxLayout::GetDPIScale)
			[
				LoadingWidget
			]
			]
			]
			];

		// Add a border widget at bottom, then add Tip widget
		Root->AddSlot()
			.HAlign(LayoutSettings.BottomBorderHorizontalAlignment)
			.VAlign(VAlign_Bottom)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.BottomBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.BottomBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSLetterboxLayout::GetDPIScale)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			]
			]
			]
			];
	}
	else
	{
		// Add a border widget at top, then add Tip widget
		Root->AddSlot()
			.HAlign(LayoutSettings.TopBorderHorizontalAlignment)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.TopBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.TopBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSLetterboxLayout::GetDPIScale)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			]
			]
			]
			];

		// Add a border widget at bottom, then add Loading widget
		Root->AddSlot()
			.HAlign(LayoutSettings.BottomBorderHorizontalAlignment)
			.VAlign(VAlign_Bottom)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.BottomBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(LayoutSettings.LoadingWidgetAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.LoadingWidgetAlignment.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.BottomBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSLetterboxLayout::GetDPIScale)
			[
				LoadingWidget
			]
			]
			]
			];
	}

	// Construct loading complete text if enable
	if (Settings.bShowLoadingCompleteText)
	{
		Root->AddSlot()
			.VAlign(Settings.LoadingCompleteTextSettings.Alignment.VerticalAlignment)
			.HAlign(Settings.LoadingCompleteTextSettings.Alignment.HorizontalAlignment)
			.Padding(Settings.LoadingCompleteTextSettings.Padding)
			[
				SNew(SSLoadingCompleteText, Settings.LoadingCompleteTextSettings)
			];
	}

	// Add Root to this widget
	ChildSlot
		[
			Root
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
