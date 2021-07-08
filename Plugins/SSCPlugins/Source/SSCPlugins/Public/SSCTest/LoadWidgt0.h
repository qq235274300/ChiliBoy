// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCUserWidget.h"
#include "LoadWidgt0.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ULoadWidgt0 : public USSCUserWidget
{
	GENERATED_BODY()
	
public:
	void ModelInit()override;
	void ModelLoading()override;
public:

	UPROPERTY(meta = (BindWidgetOptional))
		UImage* ViewImage;
	UPROPERTY()
	TArray<UTexture2D*> Textures;
	int32 TextureIndex = 0;
	
public:
	/*************»Øµ÷********************/
	UFUNCTION()
		void BindLoadSingleObjectEntryEvnt(FName WealthName, UObject* WealthObject);
	UFUNCTION()
		void BindLoadKindObjectEntryEvnt(TArray<FName> WealthNames, TArray<UObject*> WealthObjects);

	UFUNCTION()
		void InvokeRepetedEvnt();
};
