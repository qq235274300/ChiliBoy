// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "SSCPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCPlayerCameraManager : public APlayerCameraManager , public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCPlayerCameraManager();
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
