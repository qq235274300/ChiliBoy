#include "VisualLoadingProgressWidget.h"
#include "SSCStreamLevelsManager.h"

UVisualLoadingProgressWidget::UVisualLoadingProgressWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) 
	,LevelLoaded(0),
	TotalLevel(0),
	LoadingProgress(0.f)	
{
	
}



void UVisualLoadingProgressWidget::ModelInit()
{
	Super::ModelInit();
	
}

void UVisualLoadingProgressWidget::ModelLoading()
{
	Super::ModelLoading();
}

void UVisualLoadingProgressWidget::BindLoadingStateEvnt()
{

	++LevelLoaded;
	LoadingProgress = (float)LevelLoaded / (float)TotalLevel;
	LoadingFinishDelegate.Broadcast(LoadingProgress);

	SSCHelper::Debug() << LoadingProgress << SSCHelper::Endl();
}



