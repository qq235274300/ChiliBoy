// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCGameModeBase.h"

ASSCGameModeBase::ASSCGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ASSCGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
