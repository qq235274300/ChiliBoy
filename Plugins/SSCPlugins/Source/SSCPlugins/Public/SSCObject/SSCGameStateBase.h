// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SSCObjectInterface.h"
#include "SSCGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCGameStateBase : public AGameStateBase , public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCGameStateBase();
protected:
	virtual void BeginPlay()override;
public:
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ModuleName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ObjectName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ClassName;
};
