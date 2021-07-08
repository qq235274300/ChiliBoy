// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SSCObjectInterface.h"
#include "SSCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCPlayerState : public APlayerState , public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCPlayerState();
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
