// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDataMgr.h"
#include "SSCBaseBag.generated.h"


class USSCBagBlock;

UCLASS()
class SSCPLUGINS_API USSCBaseBag : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "SSCBag")
		TArray<USSCBagBlock*> BlockArray;
};
