// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadWidgt0.h"
#include "Components/Image.h"

void ULoadWidgt0::ModelInit()
{
	Super::ModelInit();
	AddToViewport(0);
}

void ULoadWidgt0::ModelLoading()
{
	Super::ModelLoading();
	//LoadObjectEntry("ViewImage01", "BindLoadSingleObjectEntryEvnt");
	//LoadObjectKindEntry("ViewImage", "BindLoadKindObjectEntryEvnt");
}

void ULoadWidgt0::BindLoadSingleObjectEntryEvnt(FName WealthName, UObject* WealthObject)
{
	if (WealthObject)
	{
		ViewImage->SetBrushFromTexture(Cast<UTexture2D>(WealthObject));
	}
}

void ULoadWidgt0::BindLoadKindObjectEntryEvnt(TArray<FName> WealthNames, TArray<UObject*> WealthObjects)
{
	for (int i = 0; i < WealthObjects.Num(); ++i)
	{
		SSCHelper::Debug() << WealthNames[i] << SSCHelper::Endl();
		Textures.Push(Cast<UTexture2D>(WealthObjects[i]));
	}
	TextureIndex = 0;
	StartInvokeRepeated("InvokeRepetedEvnt", 1.f, 1.f, this, &ULoadWidgt0::InvokeRepetedEvnt);
}

void ULoadWidgt0::InvokeRepetedEvnt()
{
	ViewImage->SetBrushFromTexture(Textures[TextureIndex]);
	TextureIndex = TextureIndex+1 >= Textures.Num() ? 0 : TextureIndex + 1;
}

