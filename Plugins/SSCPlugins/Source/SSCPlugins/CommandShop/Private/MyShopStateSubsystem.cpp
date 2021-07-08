// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShopStateSubsystem.h"

void UMyShopStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Gold = 10;

}

void UMyShopStateSubsystem::Deinitialize()
{
	Super::Deinitialize();
	GoldChangeDel.Clear();
}

int32 UMyShopStateSubsystem::GetGold()
{
	return Gold;
}

void UMyShopStateSubsystem::AddGold(int32 GoldNum)
{
	Gold += GoldNum;
	GoldChangeDel.Broadcast(GetGold());
}

void UMyShopStateSubsystem::ReduceGold(int32 GoldNum)
{
	Gold -= GoldNum;
	GoldChangeDel.Broadcast(GetGold());
}
