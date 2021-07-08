// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SSCObjectInterface.h"
#include "SSCPawn.generated.h"

UCLASS()
class SSCPLUGINS_API ASSCPawn : public APawn , public ISSCObjectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASSCPawn();

protected:
	virtual void BeginPlay()override;
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
