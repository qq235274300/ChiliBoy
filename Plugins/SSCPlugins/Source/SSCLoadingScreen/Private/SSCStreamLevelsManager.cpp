#include "SSCStreamLevelsManager.h"
#include "SSCLoadingScreenSettings.h"
#include "SSCPlugins/Public/SSCCommon/SSCCommon.h"
#include "VisualLoadingProgressWidget.h"
#include <Engine/LevelStreaming.h>
#include <Templates/SharedPointer.h>


TSharedPtr<USSCStreamLevelsManager> USSCStreamLevelsManager::LevelsManagerInstance = NULL;


USSCStreamLevelsManager::USSCStreamLevelsManager()
{

}


TSharedPtr<USSCStreamLevelsManager> USSCStreamLevelsManager::Get()
{
	if (!LevelsManagerInstance.IsValid())
	{
		LevelsManagerInstance = MakeShareable(new USSCStreamLevelsManager);
	}
	return LevelsManagerInstance;
}

void USSCStreamLevelsManager::StartLoadStreamingLevel(UWorld* _World)
{
	if (_World)
	{
		const USSCLoadingScreenSettings* Settings = GetDefault<USSCLoadingScreenSettings>();
		if (Settings->bDisplayLoadingProgress)
		{
			// ����UI������
			LoadingWidget = CreateWidget<UVisualLoadingProgressWidget>(_World, Settings->LoadingWidget);
			LoadingWidget->AddToViewport(10);
			//���ü��عؿ�����
			TArray<ULevelStreaming*> Levels = _World->GetStreamingLevels();
			LoadingWidget->TotalLevel = Levels.Num() - Settings->MapsToExclude.Num();
			for (ULevelStreaming* StreamLevel : Levels)
			{
				StreamLevel->OnLevelShown.AddDynamic(LoadingWidget, &UVisualLoadingProgressWidget::BindLoadingStateEvnt);
			}
		}
		
	}
	
}



