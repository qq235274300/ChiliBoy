// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCLevelScriptActor.h"

ASSCLevelScriptActor::ASSCLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASSCLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
