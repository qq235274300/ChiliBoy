// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCCommon.h"
#include "SSCDriver.h"

USSCCommon* USSCCommon::Get()
{
	if (!CommonPtr)
	{
		CommonPtr = NewObject<USSCCommon>();
		CommonPtr->AddToRoot();
	}
	
	return CommonPtr;
}

USSCCommon* USSCCommon::CommonPtr = NULL;

void USSCCommon::SetDirver(ASSCDriver* _Dirver)
{
	Dirver = _Dirver;
}

ASSCDriver* USSCCommon::GetDirver()
{
	return Dirver;
}

void USSCCommon::SetCurrentWorld(UWorld* _World)
{
	CurrentWorld = _World;
}

UWorld* USSCCommon::GetCurrentWorld()
{
	return CurrentWorld;
}

void USSCCommon::SetPlayerController(APlayerController* _Controller)
{
	PlayerController = _Controller;
}

APlayerController* USSCCommon::GetPlayerController()
{
	return PlayerController;
}

void USSCCommon::SetGamePause(bool bPauseGame)
{
	if (PlayerController) {
		PlayerController->SetPause(bPauseGame);
	}
}

bool USSCCommon::IsGamePause() const
{
	return PlayerController->IsPaused();
}
