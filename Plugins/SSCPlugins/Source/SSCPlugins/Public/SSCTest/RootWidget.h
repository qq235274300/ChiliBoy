// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCUI/SSCRootWidget.h"
#include "RootWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API URootWidget : public USSCRootWidget
{
	GENERATED_BODY()

public:
	virtual void ModelInit()override;

protected:

	
};
