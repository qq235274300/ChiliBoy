// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGameViewportClient.h"

USimpleGameViewportClient::USimpleGameViewportClient(const FObjectInitializer& ObjectInitializer)
{
}

void USimpleGameViewportClient::Draw(FViewport* _Viewport, FCanvas* SceneCanvas)
{
	Super::Draw(_Viewport, SceneCanvas);
}

void USimpleGameViewportClient::FinalizeViews(FSceneViewFamily * ViewFamily, const TMap<ULocalPlayer*, FSceneView*>& PlayerViewMap)
{
	Super::FinalizeViews(ViewFamily, PlayerViewMap);
}
