// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSCObjectInterface.h"
#include "SSCUserWidget.generated.h"

/**
 * 
 */

UCLASS()
class SSCPLUGINS_API USSCUserWidget : public UUserWidget, public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	virtual void ModelRelease()override;

};
