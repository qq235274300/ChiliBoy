// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCenterLayout.h"
#include "SlateOptMacros.h"
#include "LoadingSettingTypes.h"
#include "SSBackgroundWidget.h"
#include "LoadingLayOut/SSTipWidget.h"
#include "LoadingLayOut/SSVerticalLoadingWidget.h"
#include "LoadingLayOut/SSHorizontalLoadingWidget.h"
#include "LoadingLayOut/SSLoadingCompleteText.h"
#include "Widgets/Layout/SSafeZone.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "SSCLoadingScreenSettings.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSCenterLayout::Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FCenterLayoutSettings& LayoutSettings)
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

	// Add loading widget at center
	Root->AddSlot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			LoadingWidget
		];


	if (LayoutSettings.bIsTipAtBottom)
	{
		// Add tip widget at bottom
		Root->AddSlot()
			.HAlign(LayoutSettings.BorderHorizontalAlignment)
			.VAlign(VAlign_Bottom)
			.Padding(0, 0, 0, LayoutSettings.BorderVerticalOffset)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.BorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.BorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSCenterLayout::GetDPIScale)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			]
			]
			]
			];
	}
	else
	{
		// Add tip widget at top
		Root->AddSlot()
			.HAlign(LayoutSettings.BorderHorizontalAlignment)
			.VAlign(VAlign_Top)
			.Padding(0, LayoutSettings.BorderVerticalOffset, 0, 0)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.BorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.BorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSCenterLayout::GetDPIScale)
			[
				SNew(SSTipWidget, Settings.TipWidget)
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

	// Add root to this widget
	ChildSlot
		[
			Root
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
