// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "HelperTypes.h"
/**
 * 
 */




namespace DebugHelper
{

	FORCEINLINE DebugRecord& Count(float showTime, FColor showColor)
	{
		DebugRecord::Get()->SetShowPattern(0);
		DebugRecord::Get()->InitParam(showTime, showColor);
		return *DebugRecord::Get();
	}

	FORCEINLINE DebugRecord& Count(FColor showColor)
	{
		return Count(30.f, showColor);
	}

	FORCEINLINE DebugRecord& Count()
	{
		return Count(30.f, FColor::Yellow);
	}


	FORCEINLINE DebugRecord& Log(float showTime, FColor showColor)
	{
		DebugRecord::Get()->SetShowPattern(1);
		DebugRecord::Get()->InitParam(showTime, showColor);
		return *DebugRecord::Get();
	}

	FORCEINLINE DebugRecord& Warning(float showTime, FColor showColor)
	{
		DebugRecord::Get()->SetShowPattern(2);
		DebugRecord::Get()->InitParam(showTime, showColor);
		return *DebugRecord::Get();
	}

	FORCEINLINE DebugRecord& Error(float showTime, FColor showColor)
	{
		DebugRecord::Get()->SetShowPattern(3);
		DebugRecord::Get()->InitParam(showTime, showColor);
		return *DebugRecord::Get();
	}

	FORCEINLINE DebugRecord& Endl()
	{
		return *DebugRecord::Get();
	}

};

//namespace OBJLOAD
//{
//	HELPERKITS_API bool LoadMeshFromFile(const FString& fileName,FDynamicMesh3& MeshOut);
//};



