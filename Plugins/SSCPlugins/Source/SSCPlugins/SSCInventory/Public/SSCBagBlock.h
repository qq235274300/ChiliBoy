// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDataMgr.h"
#include "SSCBagBlock.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCBagBlock : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SSCBag")
		void InitBlockInfo(EBagType _BagType, uint8 _Id);

public:
	UPROPERTY(BlueprintReadOnly, Category = "SSCBag")
		EBagType BagType;
	UPROPERTY(BlueprintReadOnly, Category = "SSCBag")
		uint8 BlockId;
};
