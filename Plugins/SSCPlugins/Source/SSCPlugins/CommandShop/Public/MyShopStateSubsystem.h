// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "MyShopStateSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChange, int32, Value);

UCLASS()
class SSCPLUGINS_API UMyShopStateSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	bool ShouldCreateSubsystem(UObject* Outer)const override { return true; }
	 void Initialize(FSubsystemCollectionBase& Collection)override;
	 void Deinitialize()override;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetGold();
	UFUNCTION(BlueprintCallable)
		void AddGold(int32 GoldNum);
	UFUNCTION(BlueprintCallable)
		void ReduceGold(int32 GoldNum);

	UPROPERTY(BlueprintAssignable)
	FOnGoldChange GoldChangeDel;
private: 
	int32 Gold;
	
		
	
};
