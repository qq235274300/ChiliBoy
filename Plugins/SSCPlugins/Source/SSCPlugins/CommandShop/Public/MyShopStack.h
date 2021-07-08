// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyShopStack.generated.h"

/**
 * 
 */

class UCommandShopBase;


UCLASS(Blueprintable)
class SSCPLUGINS_API UMyShopStack : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Push(UCommandShopBase* Command);
	UFUNCTION(BlueprintCallable)
	UCommandShopBase* Pop();

private:
	TArray<UCommandShopBase*> CommandArray;

		
};
