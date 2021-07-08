// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommandShopBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SSCPLUGINS_API UCommandShopBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		virtual void Execute() PURE_VIRTUAL(UCommandShopBase::Execute, ;);
	UFUNCTION(BlueprintCallable)
		virtual void Undo() PURE_VIRTUAL(UCommandShopBase::Undo, ;);
};
