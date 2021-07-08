// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SSCObjectInterface.h"
#include "SSCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCGameInstance : public UGameInstance,public ISSCObjectInterface
{
	GENERATED_BODY()
	
};
