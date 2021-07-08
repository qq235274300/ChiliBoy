// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCLoadingScreenSettings.h"
#include "UObject/ConstructorHelpers.h"

#define LOCTEXT_NAMESPACE "SSCLoadingSettings"


USSCLoadingScreenSettings::USSCLoadingScreenSettings(const FObjectInitializer& Initializer) : Super(Initializer)
{
	StartupLoadingScreen.TipWidget.TipWrapAt = 1000.0f;
	StartupLoadingScreen.bShowWidgetOverlay = false;
	DefaultLoadingScreen.TipWidget.TipWrapAt = 1000.0f;
	bDisplayLoadingProgress = true;
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		StartupLoadingScreen.TipWidget.Appearance.Font = FSlateFontInfo(RobotoFontObj.Object, 20, FName("Normal"));
		DefaultLoadingScreen.TipWidget.Appearance.Font = FSlateFontInfo(RobotoFontObj.Object, 20, FName("Normal"));
		StartupLoadingScreen.LoadingWidget.Appearance.Font = FSlateFontInfo(RobotoFontObj.Object, 32, FName("Bold"));
		DefaultLoadingScreen.LoadingWidget.Appearance.Font = FSlateFontInfo(RobotoFontObj.Object, 32, FName("Bold"));
		StartupLoadingScreen.LoadingCompleteTextSettings.Appearance.Font = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Normal"));
		DefaultLoadingScreen.LoadingCompleteTextSettings.Appearance.Font = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Normal"));
	}
}
#undef  LOCTEXT_NAMESPACE