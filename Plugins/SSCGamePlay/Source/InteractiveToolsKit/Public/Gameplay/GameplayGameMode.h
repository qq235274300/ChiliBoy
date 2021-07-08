// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCGameModeBase.h"
#include "GameplayGameMode.generated.h"

/**
 * 
 */
class UInteractiveToolsSubsystem;
class UInteractiveMeshSceneSubsystem;


UCLASS()
class INTERACTIVETOOLSKIT_API AGameplayGameMode : public ASSCGameModeBase
{
	GENERATED_BODY()
public:
	AGameplayGameMode();
	virtual void StartPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void InitSubSystem();
	virtual void ShutdownSubSystem();
	virtual void RegisterTools();
protected:
	UPROPERTY()
		UInteractiveToolsSubsystem* toolSystem;
	UPROPERTY()
		UInteractiveMeshSceneSubsystem* meshSystem;
};
