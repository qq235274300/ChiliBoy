#include "SSCLoadingScreen.h"
#include "UObject/UObjectGlobals.h"
#include "SSCLoadingFunctionLibrary.h"
#include "SSCLoadingScreenSettings.h"
#include "SSCPlugins/Public/SSCCommon/SSCCommon.h"
#include "SSCStreamLevelsManager.h"

#define LOCTEXT_NAMESPACE "FSSCLoadingScreenModule"

// MoviePlayer is registered to PreLoadMap and PostLoadMapWithWorld delegates
void FSSCLoadingScreenModule::StartupModule()
{	
	if (!IsRunningDedicatedServer() && FSlateApplication::IsInitialized())
	{
		const USSCLoadingScreenSettings* _Settings = GetDefault<USSCLoadingScreenSettings>();
		if (IsMoviePlayerEnabled())
		{		
			//当没设置LoadingScreen时候启动
			GetMoviePlayer()->OnPrepareLoadingScreen().AddRaw(this, &FSSCLoadingScreenModule::BindPrepareLoadingScreen);		
		}
		SetUpLoadingScreen(_Settings->StartupLoadingScreen);
		//显示加载过程
		if (_Settings->bDisplayLoadingProgress)
		{
			FCoreUObjectDelegates::PostLoadMapWithWorld.AddRaw(this, &FSSCLoadingScreenModule::BindPostLoadMapEvnt);
		}
	}
	
}

void FSSCLoadingScreenModule::ShutdownModule()
{
	if (!IsRunningDedicatedServer())
	{
		GetMoviePlayer()->OnPrepareLoadingScreen().RemoveAll(this);
	}
}

bool FSSCLoadingScreenModule::IsGameModule() const
{
	return true;
}


void FSSCLoadingScreenModule::BindPrepareLoadingScreen()
{
	const USSCLoadingScreenSettings* Settings = GetDefault<USSCLoadingScreenSettings>();
	SetUpLoadingScreen(Settings->DefaultLoadingScreen);
}

void FSSCLoadingScreenModule::BindPostLoadMapEvnt(UWorld* _World)
{
	SSCHelper::Debug() << "Start Loading Level Streaming" << SSCHelper::Endl();
	USSCStreamLevelsManager::Get()->StartLoadStreamingLevel(_World);
}


void FSSCLoadingScreenModule::SetUpLoadingScreen(const FLoadingScreenSettings& LoadingScreenSettings)
{
	//SSCHelper::Debug() << "SetUp" << SSCHelper::Endl();
	TArray<FString> MoviesList = LoadingScreenSettings.MoviePaths;

	if (LoadingScreenSettings.bShuffle == true)
	{
		ShuffleMoives(MoviesList);
	}

	if (LoadingScreenSettings.bSetDisplayMovieIndexManually == true)
	{
		MoviesList.Empty();
		if (LoadingScreenSettings.MoviePaths.IsValidIndex(USSCLoadingFunctionLibrary::GetDisplayMovieIndex()))
		{
			MoviesList.Add(LoadingScreenSettings.MoviePaths[USSCLoadingFunctionLibrary::GetDisplayMovieIndex()]);
		}
		else
		{
			MoviesList = LoadingScreenSettings.MoviePaths;
		}
	}

	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.MinimumLoadingScreenDisplayTime = LoadingScreenSettings.MinimumLoadingScreenDisplayTime;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = LoadingScreenSettings.bAutoCompleteWhenLoadingCompletes;
	LoadingScreen.bMoviesAreSkippable = LoadingScreenSettings.bMoviesAreSkippable;
	LoadingScreen.bWaitForManualStop = LoadingScreenSettings.bWaitForManualStop;
	LoadingScreen.bAllowInEarlyStartup = LoadingScreenSettings.bAllowInEarlyStartup;
	LoadingScreen.bAllowEngineTick = LoadingScreenSettings.bAllowEngineTick;
	LoadingScreen.MoviePaths = MoviesList;
	LoadingScreen.PlaybackType = LoadingScreenSettings.PlaybackType;

	if (LoadingScreenSettings.bShowWidgetOverlay)
	{
		
		const USSCLoadingScreenSettings* Settings = GetDefault<USSCLoadingScreenSettings>();
	
		switch (LoadingScreenSettings.Layout)
		{
		case EAsyncLoadingScreenLayout::ALSL_Classic:
			
			LoadingScreen.WidgetLoadingScreen = SNew(SSClassicLayout, LoadingScreenSettings, Settings->Classic);
			break;
		case EAsyncLoadingScreenLayout::ALSL_Center:
			LoadingScreen.WidgetLoadingScreen = SNew(SSCenterLayout, LoadingScreenSettings, Settings->Center);
			break;
		case EAsyncLoadingScreenLayout::ALSL_Letterbox:
			LoadingScreen.WidgetLoadingScreen = SNew(SSLetterboxLayout, LoadingScreenSettings, Settings->Letterbox);
			break;
		/*case EAsyncLoadingScreenLayout::ALSL_Sidebar:
			LoadingScreen.WidgetLoadingScreen = SNew(SSSidebarLayout, LoadingScreenSettings, Settings->Sidebar);
			break;
		case EAsyncLoadingScreenLayout::ALSL_DualSidebar:
			LoadingScreen.WidgetLoadingScreen = SNew(SSDualSidebarLayout, LoadingScreenSettings, Settings->DualSidebar);
			break;*/
		}

	}
	
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void FSSCLoadingScreenModule::ShuffleMoives(TArray<FString>& MoiveList)
{
	
	if (MoiveList.Num() > 0)
	{
		int32 LastIndex = MoiveList.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				MoiveList.Swap(i, Index);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FSSCLoadingScreenModule, SSCLoadingScreen)

