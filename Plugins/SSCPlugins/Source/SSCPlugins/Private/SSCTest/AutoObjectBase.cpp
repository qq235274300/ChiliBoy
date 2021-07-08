// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoObjectBase.h"

void UAutoObjectBase::ModelLoading()
{
	Super::ModelLoading();

	bIsAllowTick = true;
	//LoadClassEntry("WealthActorClass01", "BindSingleClassLoadEvnt");
	//LoadClassKindEntry("WealthActorClass", "BindKindClassLoadEvnt");
	//BuildSinglClassWealth(EWealthClassType::Actor, "WealthActorClass01", "BindBuildSingeActor", SpawnTransform);
	TArray<FTransform> SpawnTransforms;
	for (int i = 0; i < 3; ++i)
	{
		SpawnTransforms.Push(FTransform(SpawnTransform.GetLocation() + FVector(OffsetValue * i, 0.f, 0.f)));
	}
	//BuildKindClassWealth(EWealthClassType::Actor, "WealthActorClass", "BindBuildKindActors", SpawnTransforms);
	//BuildMultiClassWealth(EWealthClassType::Actor, "WealthActorClass02", 3, "BindMultiAcrtor", SpawnTransforms);
}

void UAutoObjectBase::ModelTick(float DeltaSeconds)
{
	Super::ModelTick(DeltaSeconds);
	if (SingleActor)
	{
		SingleActor->AddActorWorldRotation(FRotator(1.0f, 0.f, 0.f));
	}
	for (int i = 0; i < KindActors.Num(); ++i)
	{
		KindActors[i]->AddActorWorldRotation(FRotator(1.0f, 0.f, 0.f));
	}
}

void UAutoObjectBase::BindSingleClassLoadEvnt(FName WealthName, UClass* ClassInst)
{
	GetCurrentWorld()->SpawnActor<AActor>(ClassInst, SpawnTransform);
}

void UAutoObjectBase::BindKindClassLoadEvnt(TArray<FName> WealthNames, TArray<UClass*> ClassInsts)
{
	for (int i = 0; i < ClassInsts.Num(); ++i)
	{
		GetCurrentWorld()->SpawnActor<AActor>(ClassInsts[i], SpawnTransform.GetLocation()+FVector(OffsetValue*i,0.f,0.f),FQuat::Identity.Rotator());
	}
}

void UAutoObjectBase::BindBuildSingeActor(FName WealthName, AActor* WealthActor)
{
	//SSCHelper::Debug() << WealthName << SSCHelper::Endl;
	SingleActor = WealthActor;
}

void UAutoObjectBase::BindBuildKindActors(TArray<FName> WealthNames, TArray <AActor*> WealthActors)
{
	for (int i = 0; i < WealthNames.Num(); ++i)
	{
		SSCHelper::Debug() << WealthNames[i] << SSCHelper::Endl();
		
	}
	KindActors = WealthActors;
}

void UAutoObjectBase::BindMultiAcrtor(FName WealthNames, TArray <AActor*> WealthActors)
{
	SSCHelper::Debug() << WealthNames << SSCHelper::Endl();
	KindActors = WealthActors;

}
