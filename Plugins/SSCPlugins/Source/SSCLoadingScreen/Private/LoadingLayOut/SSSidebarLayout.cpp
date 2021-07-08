// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSidebarLayout.h"
#include "SlateOptMacros.h"
#include "LoadingLayOut/SSBackgroundWidget.h"
#include "LoadingLayOut/SSHorizontalLoadingWidget.h"
#include "LoadingLayOut/SSVerticalLoadingWidget.h"
#include "LoadingLayOut/SSTipWidget.h"
#include "LoadingLayOut/SSLoadingCompleteText.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSSidebarLayout::Construct(const FArguments& InArgs, const FLoadingScreenSettings& Settings, const FSidebarLayoutSettings& LayoutSettings)
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


	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	if (LayoutSettings.bIsLoadingWidgetAtTop)
	{
		// Add loading widget at top
		VerticalBox.Get().AddSlot()
			.AutoHeight()
			.HAlign(LayoutSettings.LoadingWidgetAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.LoadingWidgetAlignment.VerticalAlignment)
			[
				LoadingWidget
			];

		// Add SSpacer at middle
		VerticalBox.Get().AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.AutoHeight()
			[
				SNew(SSpacer)
				.Size(FVector2D(0.0f, LayoutSettings.Space))
			];

		// Add tip widget at bottom
		VerticalBox.Get().AddSlot()
			.AutoHeight()
			.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			];
	}
	else
	{
		// Add tip widget at top
		VerticalBox.Get().AddSlot()
			.AutoHeight()
			.HAlign(LayoutSettings.TipAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.TipAlignment.VerticalAlignment)
			[
				SNew(SSTipWidget, Settings.TipWidget)
			];

		// Add SSpacer at middle
		VerticalBox.Get().AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.AutoHeight()
			[
				SNew(SSpacer)
				.Size(FVector2D(0.0f, LayoutSettings.Space))
			];

		// Add loading widget at bottom
		VerticalBox.Get().AddSlot()
			.AutoHeight()
			.HAlign(LayoutSettings.LoadingWidgetAlignment.HorizontalAlignment)
			.VAlign(LayoutSettings.LoadingWidgetAlignment.VerticalAlignment)
			[
				LoadingWidget
			];
	}



	if (LayoutSettings.bIsWidgetAtRight)
	{
		// Add widget at right
		Root.Get().AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(LayoutSettings.BorderVerticalAlignment)
			.Padding(0, 0, LayoutSettings.BorderHorizontalOffset, 0)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.BorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(HAlign_Fill)
			.VAlign(LayoutSettings.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.BorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSSidebarLayout::GetDPIScale)
			[
				VerticalBox
			]
			]
			]
			];
	}
	else
	{
		// Add widget at left
		Root.Get().AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(LayoutSettings.BorderVerticalAlignment)
			.Padding(LayoutSettings.BorderHorizontalOffset, 0, 0, 0)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.BorderImage(&LayoutSettings.BorderBackground)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SSafeZone)
				.HAlign(HAlign_Fill)
			.VAlign(LayoutSettings.VerticalAlignment)
			.IsTitleSafe(true)
			.Padding(LayoutSettings.BorderPadding)
			[
				SNew(SDPIScaler)
				.DPIScale(this, &SSSidebarLayout::GetDPIScale)
			[
				VerticalBox
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
