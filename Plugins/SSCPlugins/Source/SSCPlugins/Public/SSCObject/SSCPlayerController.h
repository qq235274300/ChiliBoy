// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSCObjectInterface.h"
#include "SSCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCPlayerController : public APlayerController , public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCPlayerController();
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
