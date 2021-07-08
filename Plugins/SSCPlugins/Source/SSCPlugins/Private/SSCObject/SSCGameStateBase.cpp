// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCGameStateBase.h"

ASSCGameStateBase::ASSCGameStateBase()
{
	PrimaryActorTick.bCanEverTick = false;
}



void ASSCGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
