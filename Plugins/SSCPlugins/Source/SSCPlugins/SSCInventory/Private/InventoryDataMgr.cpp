// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDataMgr.h"

UInventoryDataMgr* UInventoryDataMgr::DataMgr = NULL;

UInventoryDataMgr* UInventoryDataMgr::Get()
{
	if(DataMgr == NULL)
	{
		DataMgr = NewObject<UInventoryDataMgr>();
		DataMgr->AddToRoot();
		DataMgr->LoadTotalData();
	}

	return DataMgr;
}



void UInventoryDataMgr::LoadTotalData()
{
	TotalData = LoadObject<UInventoryData>(NULL, TEXT("InventoryData'/SSCPlugins/BP/Inventory/Data/InventoryData_BP.InventoryData_BP'"));
	InventoryDataGroup.Reset();

	InventoryDataGroup.Add(0, FBagData(EItemType::Building, 0));
	InventoryDataGroup.Add(1, FBagData(EItemType::Building, 1));
	InventoryDataGroup.Add(2, FBagData(EItemType::Building, 2));

	InventoryDataGroup.Add(3, FBagData(EItemType::FBX, 0));
	InventoryDataGroup.Add(4, FBagData(EItemType::FBX, 1));
	InventoryDataGroup.Add(5, FBagData(EItemType::FBX, 2));
}

UTexture* UInventoryDataMgr::GetItemTexture(int32 Index)
{
	return TotalData->TextureArray[Index];
	
}

uint8 UInventoryDataMgr::GetKindByItemID(int32 Index)
{
	return  InventoryDataGroup.Find(Index)->ItemKind;
}

EItemType UInventoryDataMgr::GetTypeByItemID(int32 Index)
{
	return  InventoryDataGroup.Find(Index)->ItemType;
}
