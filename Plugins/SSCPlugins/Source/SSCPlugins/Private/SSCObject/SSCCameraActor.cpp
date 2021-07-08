// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCCameraActor.h"

ASSCCameraActor::ASSCCameraActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASSCCameraActor::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	GetCurrentWorld()->DestroyActor(this);
}

void ASSCCameraActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterToModule(ModuleName,ObjectName,ClassName);
	
}
