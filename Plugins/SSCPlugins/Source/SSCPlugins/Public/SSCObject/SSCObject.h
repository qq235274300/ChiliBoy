// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SSCObjectInterface.h"
#include "SSCObject.generated.h"

/**
 * 
 */

UCLASS()
class SSCPLUGINS_API USSCObject : public UObject, public ISSCObjectInterface
{
	GENERATED_BODY()
	
public:
	virtual void ModelRelease()override;
};
