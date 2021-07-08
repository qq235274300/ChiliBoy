// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "SSCObjectInterface.h"
#include "SSCDefaultPawn.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCDefaultPawn : public ADefaultPawn, public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCDefaultPawn();
protected:
	virtual void BeginPlay()override;
public:
	virtual void ModelTick(float DeltaSeconds)override;
	virtual void ModelRelease()override;
public:
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ModuleName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ObjectName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ClassName;

private:
	bool isRegister = false;
};
