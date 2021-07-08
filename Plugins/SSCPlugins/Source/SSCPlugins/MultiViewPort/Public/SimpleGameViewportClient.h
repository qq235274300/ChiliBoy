// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "SimpleGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USimpleGameViewportClient : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void Draw(FViewport* _Viewport, FCanvas* SceneCanvas) override;
	virtual void FinalizeViews(class FSceneViewFamily* ViewFamily, const TMap<ULocalPlayer*, FSceneView*>& PlayerViewMap)override;
};
