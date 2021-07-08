// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SSCGTypes.generated.h"


UCLASS()
class SSCPLUGINS_API USSCGTypes : public UObject
{
	GENERATED_BODY()
	
};


#pragma region GamePart

UENUM()
enum class ESSCGame : uint8
{
	Center = 0,
	HUD,
	Player,
};

#pragma endregion