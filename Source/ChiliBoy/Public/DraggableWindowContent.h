// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "DraggableWindowContent.generated.h"


class UCanvasPanelSlot;
class UBorder;
class UDraggableWindow;

/**
 * 
 */
UCLASS()
class CHILIBOY_API UDraggableWindowContent : public UUserWidget
{
	GENERATED_BODY()
public:
	UDraggableWindowContent(const FObjectInitializer& ObjectInitializer);
/********************************************************/
	virtual void NativeConstruct()override;

	
public:
	UPROPERTY()
	UCanvasPanelSlot* ParentCanvas;
	UPROPERTY(meta = (BindWidget))
	UBorder* BorderTitle;

public:
	UFUNCTION()
	FEventReply OnMouseButtonUpEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent);
	UFUNCTION()
	FEventReply OnMouseButtonDownEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent);
public:
	UDraggableWindow* Parent;
	
	
};
