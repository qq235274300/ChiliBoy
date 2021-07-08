// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SSCObjectInterface.h"
#include "SSCGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCGameModeBase : public AGameModeBase ,public ISSCObjectInterface
{
	GENERATED_BODY()

public:
	ASSCGameModeBase();

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
