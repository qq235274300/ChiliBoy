// Fill out your copyright notice in the Description page of Project Settings.


#include "SSClassicLayout.h"
#include "SlateOptMacros.h"
#include "LoadingSettingTypes.h"
#include "LoadingLayOut/SSBackgroundWidget.h"
#include "LoadingLayOut/SSHorizontalLoadingWidget.h"
#include "LoadingLayOut/SSVerticalLoadingWidget.h"
#include "LoadingLayOut/SSTipWidget.h"
#include "LoadingLayOut/SSLoadingCompleteText.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSClassicLayout::Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FClassicLayoutSettings& LayoutSettings)
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

	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);

	if (LayoutSettings.bIsLoadingWidgetAtLeft)
	{
		// Add Loading widget on left first
		HorizontalBox.Get().AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.AutoWidth()
			[
				LoadingWidget
			];

		// Add spacer at midder
		HorizontalBox.Get().AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(LayoutSettings.Space, 0.0f))
			];

		// Tip Text on the right
		HorizontalBox.Get().AddSlot()
			.FillWidth(1.0f)
			.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			];
	}
	else
	{
		// Tip Text on the left
		HorizontalBox.Get().AddSlot()
			.FillWidth(1.0f)
			.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			[
				// Add tip text
				SNew(SSTipWidget, Settings.TipWidget)
			];

		// Add spacer at midder
		HorizontalBox.Get().AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(LayoutSettings.Space, 0.0f))
			];

		// Add Loading widget on right
		HorizontalBox.Get().AddSlot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.AutoWidth()
			[
				LoadingWidget
			];
	}


	EVerticalAlignment VerticalAlignment;
	// Set vertical alignment for widget
	if (LayoutSettings.bIsWidgetAtBottom)
	{
		VerticalAlignment = EVerticalAlignment::VAlign_Bottom;
	}
	else
	{
		VerticalAlignment = EVerticalAlignment::VAlign_Top;
	}

	// Creating loading theme
	Root->AddSlot()
		.HAlign(LayoutSettings.BorderHorizontalAlignment)
		.VAlign(VerticalAlignment)
		[
			SNew(SBorder)
			.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.BorderImage(&LayoutSettings.BorderBackground)
		.BorderBackgroundColor(FLinearColor::White)
		[
			SNew(SSafeZone)
			.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.IsTitleSafe(true)
		.Padding(LayoutSettings.BorderPadding)
		[
			SNew(SDPIScaler)
			.DPIScale(this, &SSClassicLayout::GetDPIScale)
		[
			HorizontalBox
		]
		]
		]
		];

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
