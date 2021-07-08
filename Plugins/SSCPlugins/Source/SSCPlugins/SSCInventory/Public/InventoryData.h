// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryData.generated.h"

/*********************¡Ÿ ±∑Ω∞∏*********************************/

class UTexture;
UCLASS()
class SSCPLUGINS_API UInventoryData : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category = "SSCInventory")
		TArray<UTexture*> TextureArray;
};
