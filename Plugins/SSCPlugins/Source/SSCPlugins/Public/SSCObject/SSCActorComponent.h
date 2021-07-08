// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SSCObjectInterface.h"
#include "SSCActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SSCPLUGINS_API USSCActorComponent : public UActorComponent , public ISSCObjectInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void ModelRelease()override;


public:
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ModuleName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ObjectName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ClassName;



		
};
