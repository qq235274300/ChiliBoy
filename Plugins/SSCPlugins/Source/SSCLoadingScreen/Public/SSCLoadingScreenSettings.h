// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoadingSettingTypes.h"
#include <Blueprint/UserWidget.h>
#include "SSCLoadingScreenSettings.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct SSCLOADINGSCREEN_API FLoadingScreenSettings
{
	GENERATED_BODY()
public:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "MinimumShowTime", EditCondition = "bEnableDrag"))
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings",meta = (DisplayName =  "MinimumPlayTime"))
		float MinimumLoadingScreenDisplayTime = -1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "AutoComplete"))
		bool bAutoCompleteWhenLoadingCompletes = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "Skippable"))
		bool bMoviesAreSkippable = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "ManualStop"))
		bool bWaitForManualStop = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		TEnumAsByte<EMoviePlaybackType> PlaybackType;
	// 视频位置必须放在Content/Movie  输入名字即可
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "MoviePaths"))
		TArray<FString> MoviePaths;
	//if ture Shuffle Moive PlayLists Before Play
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings", meta = (DisplayName = "RandomPlay"))
		bool bShuffle = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings",meta = (DisplayName = "MovieIndex"))
		bool bSetDisplayMovieIndexManually = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bAllowInEarlyStartup = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movies Settings")
		bool bAllowEngineTick = false;

	/**
	 * Show Widget(Tips,BG ...) set true ,Play Movie set this false
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings",meta = (DisplayName = "ShowWidget"))
		bool bShowWidgetOverlay = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		bool bShowLoadingCompleteText = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FLoadingCompleteTextSettings LoadingCompleteTextSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FBackgroundSettings Background;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FTipSettings TipWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		FLoadingWidgetSettings LoadingWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Screen Settings")
		EAsyncLoadingScreenLayout Layout = EAsyncLoadingScreenLayout::ALSL_Classic;
};






UCLASS(Config = "Game", defaultconfig, meta = (DisplayName = "SSCLoadingScreen"))
class SSCLOADINGSCREEN_API USSCLoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	USSCLoadingScreenSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	//是否显示进度条
	UPROPERTY(Config, EditAnywhere, Category = "Loading Progress Settings")
		bool bDisplayLoadingProgress;
	UPROPERTY(config, EditAnywhere, Category = "Loading Progress Settings", meta = (EditCondition = "bDisplayLoadingProgress"))
		TSubclassOf<class UUserWidget> LoadingWidget;
	//需要手动Load的地图
	UPROPERTY(config, EditAnywhere, Category = "Loading Progress Settings", meta = (DisplayName = "List of maps to exclude while loading", AllowedClasses = "World", EditCondition = "bDisplayLoadingProgress"))
		TArray<FSoftObjectPath> MapsToExclude;
	//第一次打开游戏
	UPROPERTY(Config, EditAnywhere, Category = "Loading Movie Settings")
		FLoadingScreenSettings DefaultLoadingScreen;
	//Openlevel
	UPROPERTY( EditAnywhere, Category = "Loading Screen Settings")
		FLoadingScreenSettings StartupLoadingScreen;
	//样式
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FClassicLayoutSettings Classic;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FCenterLayoutSettings Center;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FLetterboxLayoutSettings Letterbox;
	/*UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FSidebarLayoutSettings Sidebar;
	UPROPERTY(Config, EditAnywhere, Category = "Layout")
		FDualSidebarLayoutSettings DualSidebar;*/
};
