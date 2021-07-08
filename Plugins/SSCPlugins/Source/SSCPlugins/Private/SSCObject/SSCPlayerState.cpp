// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCPlayerState.h"

ASSCPlayerState::ASSCPlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASSCPlayerState::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
