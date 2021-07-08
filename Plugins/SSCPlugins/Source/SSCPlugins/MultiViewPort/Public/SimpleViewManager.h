// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimpleView.h"
#include "SimpleViewManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType,Blueprintable,meta = (ShortToolTip=""))
struct SSCPLUGINS_API FViewsManager
{
public:
	GENERATED_USTRUCT_BODY()
public:
	FViewsManager(){}

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SSCMultiViews")
		TArray<FView> ViewsArray;
};





UCLASS()
class SSCPLUGINS_API USimpleViewManager : public UObject
{
	GENERATED_BODY()
	
};
