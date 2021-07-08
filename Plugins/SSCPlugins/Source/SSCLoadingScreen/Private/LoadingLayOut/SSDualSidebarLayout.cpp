// Fill out your copyright notice in the Description page of Project Settings.


#include "SSDualSidebarLayout.h"
#include "SlateOptMacros.h"
#include "LoadingSettingTypes.h"
#include "LoadingLayOut/SSBackgroundWidget.h"
#include "LoadingLayOut/SSHorizontalLoadingWidget.h"
#include "LoadingLayOut/SSVerticalLoadingWidget.h"
#include "LoadingLayOut/SSTipWidget.h"
#include "LoadingLayOut/SSLoadingCompleteText.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSDualSidebarLayout::Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FDualSidebarLayoutSettings& LayoutSettings)
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



	if (LayoutSettings.bIsLoadingWidgetAtRight)
	{
		// Add loading widget at right
		Root.Get().AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(LayoutSettings.RightBorderVerticalAlignment)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.RightBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(HAlign_Fill)
			.VAlign(LayoutSettings.RightVerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.RightBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSDualSidebarLayout::GetDPIScale)
			[
				LoadingWidget
			]
			]
			]
			];

		// Add tip widget at left
		Root.Get().AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(LayoutSettings.LeftBorderVerticalAlignment)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.LeftBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(HAlign_Fill)
			.VAlign(LayoutSettings.LeftVerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.LeftBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSDualSidebarLayout::GetDPIScale)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			]
			]
			]
			];
	}

	else
	{
		// Add Tip widget at right
		Root.Get().AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(LayoutSettings.RightBorderVerticalAlignment)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.RightBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(HAlign_Fill)
			.VAlign(LayoutSettings.RightVerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.RightBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSDualSidebarLayout::GetDPIScale)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			]
			]
			]
			];

		// Add Loading widget at left
		Root.Get().AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(LayoutSettings.LeftBorderVerticalAlignment)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.LeftBorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(HAlign_Fill)
			.VAlign(LayoutSettings.LeftVerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.LeftBorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSDualSidebarLayout::GetDPIScale)
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

	// Add root to this widget
	ChildSlot
		[
			Root
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
