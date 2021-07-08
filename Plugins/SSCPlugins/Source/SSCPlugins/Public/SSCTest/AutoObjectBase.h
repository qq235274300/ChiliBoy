// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCObject.h"
#include "AutoObjectBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class SSCPLUGINS_API UAutoObjectBase : public USSCObject
{
	GENERATED_BODY()
	
public:
	virtual void ModelLoading()override;
	virtual void ModelTick(float DeltaSeconds)override;
	
	UFUNCTION()
		void BindSingleClassLoadEvnt(FName WealthName, UClass* ClassInst);
	UFUNCTION()
		void BindKindClassLoadEvnt(TArray<FName> WealthNames, TArray<UClass*> ClassInsts);
	
	UFUNCTION()
		void BindBuildSingeActor(FName WealthName,AActor* WealthActor);

	UFUNCTION()
		void BindBuildKindActors(TArray<FName> WealthNames, TArray <AActor*> WealthActors );
	UFUNCTION()
		void BindMultiAcrtor(FName WealthNames, TArray <AActor*> WealthActors);


	UPROPERTY(EditAnywhere)
		FTransform SpawnTransform;
	UPROPERTY(EditAnywhere)
		float OffsetValue;

	AActor* SingleActor;
	TArray<AActor*> KindActors;
};
