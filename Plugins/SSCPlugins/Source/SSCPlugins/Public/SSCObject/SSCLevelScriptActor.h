// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SSCObjectInterface.h"
#include "SSCLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCLevelScriptActor : public ALevelScriptActor ,public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCLevelScriptActor();
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
