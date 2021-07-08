// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SSCDefine.h"
#include "SSCGame/SSCGCommon.h"
#include "SSCCommon.generated.h"

/**
 * 
 */
namespace SSCHelper
{
	
	FORCEINLINE SSCRecord& Debug(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(0);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Debug(FColor showColor)
	{
		return Debug(300.f, showColor);	
	}

	FORCEINLINE SSCRecord& Debug()
	{
		return Debug(300.f, FColor::Yellow);
	}


	FORCEINLINE SSCRecord& Log(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(1);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Warning(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(2);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Error(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(3);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Endl()
	{
		return *SSCRecord::Get();
	}


	template<typename TEnum>
	FORCEINLINE FString GetEnumValueAsString(const FString& EnumName, TEnum Element)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!EnumPtr) return FString("InValid Enum Name");
		return EnumPtr->GetEnumName(int32(Element));

	}

	template<typename TEnum>
	FORCEINLINE FString GetEnumValueAsName(const FString& EnumName, TEnum Element)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!EnumPtr) return FName("InValid Enum Name");
		return FName(*EnumPtr->GetEnumName(int32(Element)));

	}

	template<typename TEnum>
	FORCEINLINE TEnum GetEnumValueFromName(const FString& EnumName, FName ElementName)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!EnumPtr) return TEnum(0);
		return TEnum(EnumPtr->GetIndexByName(ElementName));
	}

	
	FORCEINLINE int32 GetEnumIndexFromName(const FString& EnumName, FName ElementName)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!EnumPtr) return -1;
		return EnumPtr->GetIndexByName(ElementName);
	}

	FORCEINLINE FString GetCallResult(ERelfectCallResult Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *FString("ERelfectCallResult"), true);
		return EnumPtr->GetNameStringByIndex((int32)Value);
	}
	
}

class ASSCDriver;
class APlayerController;

UCLASS()
class SSCPLUGINS_API USSCCommon : public UObject
{
	GENERATED_BODY()

//设置为全局类
public:
	static USSCCommon* Get();
private:
	static USSCCommon*  CommonPtr;
	
public:
	void SetDirver(ASSCDriver* _Dirver);
	ASSCDriver* GetDirver();
	void SetCurrentWorld(UWorld* _World);
	UWorld* GetCurrentWorld();
	void SetPlayerController(APlayerController* _Controller);
	APlayerController* GetPlayerController();
	void SetGamePause(bool bPauseGame);
	bool IsGamePause()const;

private:
	ASSCDriver* Dirver;
	UWorld* CurrentWorld;
	APlayerController* PlayerController;
};
