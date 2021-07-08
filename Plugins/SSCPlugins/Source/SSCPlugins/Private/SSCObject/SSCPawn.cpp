// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCPawn.h"

// Sets default values
ASSCPawn::ASSCPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASSCPawn::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName, ObjectName, ClassName);
}

void ASSCPawn::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	GetCurrentWorld()->DestroyActor(this);
}


