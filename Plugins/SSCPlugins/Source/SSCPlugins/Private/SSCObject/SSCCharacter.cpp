// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCCharacter.h"

// Sets default values
ASSCCharacter::ASSCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASSCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterToModule(ModuleName, ObjectName, ClassName);
}

void ASSCCharacter::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	GetCurrentWorld()->DestroyActor(this);
}

