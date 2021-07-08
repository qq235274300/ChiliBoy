// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameplayGameMode.h"
#include <SubSystem/InteractiveMeshSceneSubsystem.h>
#include <SubSystem/InteractiveToolsSubsystem.h>
#include <Tools/RuntimeDrawPolygonTool.h>

AGameplayGameMode::AGameplayGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AGameplayGameMode::StartPlay()
{
	Super::StartPlay();
	//³õÊ¼»¯ITF SubSystem
	InitSubSystem();
}

void AGameplayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (toolSystem)
	{
		toolSystem->Tick(DeltaTime);
	}
}

void AGameplayGameMode::InitSubSystem()
{
	UWorld* world = GetWorld();
	UGameInstance* gameInstance = GetGameInstance();
	check(world && gameInstance);
	toolSystem = UGameInstance::GetSubsystem<UInteractiveToolsSubsystem>(gameInstance);
	UInteractiveToolsSubsystem::InitSubSysytem(toolSystem);
	meshSystem = UGameInstance::GetSubsystem<UInteractiveMeshSceneSubsystem>(gameInstance);
	UInteractiveMeshSceneSubsystem::InitSubSysytem(meshSystem);
	check(toolSystem && meshSystem);
	toolSystem->Init(world);
	meshSystem->SetTransactionAPI(toolSystem->GetTransactionAPI());

	RegisterTools();
}

void AGameplayGameMode::ShutdownSubSystem()
{
	if (toolSystem)
	{
		delete toolSystem;
		toolSystem = nullptr;
	}
}

void AGameplayGameMode::RegisterTools()
{
	//ToolManger Create ToolInstance;
	if (toolSystem == nullptr)
	{
		return;
	}
	UInteractiveToolManager* toolManager = toolSystem->GetToolContext()->ToolManager;
	IToolsContextAssetAPI* assetAPI = toolSystem->GetAssetAPI();
	if (toolManager == nullptr || assetAPI == nullptr)
	{
		return;
	}
	URuntimeDrawPolygonToolBuilder* DrawPloygonBuilder = NewObject<URuntimeDrawPolygonToolBuilder>();
	DrawPloygonBuilder->AssetAPI = assetAPI;
	toolManager->RegisterToolType("DrawPolygon", DrawPloygonBuilder);

}

