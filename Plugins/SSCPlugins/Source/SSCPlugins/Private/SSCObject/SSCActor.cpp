// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCActor.h"

// Sets default values
ASSCActor::ASSCActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASSCActor::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterToModule(ModuleName, ObjectName, ClassName);
}

void ASSCActor::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	GetCurrentWorld()->DestroyActor(this);
}

  