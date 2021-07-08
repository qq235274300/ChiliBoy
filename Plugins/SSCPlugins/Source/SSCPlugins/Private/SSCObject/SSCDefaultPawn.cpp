// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCObject/SSCDefaultPawn.h"

ASSCDefaultPawn::ASSCDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsAllowTick = true;
}

void ASSCDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}

void ASSCDefaultPawn::ModelTick(float DeltaSeconds)
{
	/*if (!isRegister)
	{
		RegisterToModule(ModuleName, ObjectName, ClassName);
		isRegister = true;
	}*/
	
}

void ASSCDefaultPawn::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	GetCurrentWorld()->DestroyActor(this);
}
