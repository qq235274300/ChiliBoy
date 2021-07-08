// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualRootWidget.h"
#include "SSCPlugins/Public/SSCCommon/SSCCommon.h"

void UVisualRootWidget::ModelInit()
{
	/*FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	USSCCommon::Get()->GetPlayerController()->bShowMouseCursor = true;
	USSCCommon::Get()->GetPlayerController()->SetInputMode(InputMode);*/
	Super::ModelInit();
	//AddToViewport(0);
	//ShowLoadingProgress();
}

void UVisualRootWidget::ShowLoadingProgress()
{
	/*AdvanceLoadPanel("LoadingProgressWidget");
	ShowPanel("LoadingProgressWidget");	*/
}
