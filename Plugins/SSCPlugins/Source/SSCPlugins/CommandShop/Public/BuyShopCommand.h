// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommandShopBase.h"
#include "ShopItem.h"
#include "UObject/NoExportTypes.h"
#include "BuyShopCommand.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SSCPLUGINS_API UBuyShopCommand : public UCommandShopBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite,EditInstanceOnly,meta=(ExposeOnSpawn))
	FMyShopItem Item;

public:
	
	virtual void Execute()override;
	
	virtual void Undo()override;
	
};
