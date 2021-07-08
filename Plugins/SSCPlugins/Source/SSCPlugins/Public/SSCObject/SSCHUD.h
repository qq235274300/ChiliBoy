// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSCObjectInterface.h"
#include "SSCHUD.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCHUD : public AHUD , public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCHUD();

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
