// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShopItem.generated.h"
/**
 * 
 */
class SSCPLUGINS_API ShopItem
{
public:
	ShopItem();
	~ShopItem();
};

USTRUCT(BlueprintType)
struct FMyShopItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Gold; 
};