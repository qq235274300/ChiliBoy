// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCPlayerController.h"

ASSCPlayerController::ASSCPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASSCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
