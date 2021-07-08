// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCHUD.h"

ASSCHUD::ASSCHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASSCHUD::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
