// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCPlayerCameraManager.h"

ASSCPlayerCameraManager::ASSCPlayerCameraManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASSCPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
