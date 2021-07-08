// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryData.h"
#include "Widgets/Views/STreeView.h"
#include "InventoryDataMgr.generated.h"

class UInventoryData;

UENUM()
enum class EBagType : uint8
{	
	BuildingBag = 0,
	PlantBag,
	CommanBag,
	CustomBag,	
};
UENUM()
enum class EItemType : uint8
{
	Building =0,
	FBX,
	Obj,
};

USTRUCT()
struct FIvItemInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
		uint8 BlockId;
	UPROPERTY()
		uint8 ItemId;
	UPROPERTY()
		EItemType ItemType;
	UPROPERTY()
		uint8 ItemKind;
	UPROPERTY()
		uint32 Number;

public:
	FIvItemInfo() {}
	void Init(uint8 _BlockId, uint8 _ItemId, uint8  _Num )
	{
		BlockId = _BlockId;
		ItemId = _ItemId;
		Number = _Num;
	}
	
	bool IsEmpty()const {
		return Number <= 0;
	}


};

USTRUCT()
struct FBagData 
{
	GENERATED_BODY()

	EItemType ItemType;
	uint8 ItemKind;
	FBagData(){}
	FBagData(EItemType _ItemType, uint8 _ItemKind) : ItemType(_ItemType), ItemKind(_ItemKind) {}
};


//Update
DECLARE_DELEGATE_TwoParams(FUpdateBagBlockDel,EBagType,uint8)


UCLASS()
class SSCPLUGINS_API UInventoryDataMgr : public UObject
{
	GENERATED_BODY()

public:
	static UInventoryDataMgr* Get();
protected:

	static UInventoryDataMgr* DataMgr;
	
public:
	void LoadTotalData();
	UTexture* GetItemTexture(int32 Index);
	uint8 GetKindByItemID(int32 Index);
	EItemType GetTypeByItemID(int32 Index);
	void ChangeItemInfo(EBagType _Type, FItemInfo ItemInfo);
public:
	//目前需要手动填充 
	UPROPERTY()
		TMap<uint8, FIvItemInfo> BuildingBagGroup;
	UPROPERTY()
		TMap<uint8, FIvItemInfo> PlantBagGroup;
	UPROPERTY()
		TMap<uint8, FIvItemInfo> CommanBagGroup;
	UPROPERTY()
		TMap<uint8, FIvItemInfo> CustomBagGroup;
	UPROPERTY()
		TMap<uint8, FBagData> InventoryDataGroup;

protected:
	UPROPERTY()
		UInventoryData* TotalData;

public:
	FUpdateBagBlockDel FUpdateBagBlockDel;
};

