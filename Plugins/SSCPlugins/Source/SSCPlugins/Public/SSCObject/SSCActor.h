// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSCObjectInterface.h"
#include "SSCActor.generated.h"



UCLASS()
class SSCPLUGINS_API ASSCActor : public AActor,public ISSCObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSCActor();

protected:
	// Called when the game starts or when spawned
	// Actor BeginPlay Register  RegisterToModule(ModuelName,ObjectName,ClassName)
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
