// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSCObjectInterface.h"
#include "SSCCharacter.generated.h"

UCLASS()
class SSCPLUGINS_API ASSCCharacter : public ACharacter,public ISSCObjectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSCCharacter();

protected:
	// Called when the game starts or when spawned
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
