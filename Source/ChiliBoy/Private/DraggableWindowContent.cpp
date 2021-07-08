// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableWindowContent.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "DraggableWindow.h"
#include <Blueprint/WidgetLayoutLibrary.h>

UDraggableWindowContent::UDraggableWindowContent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDraggableWindowContent::NativeConstruct()
{
	
	ParentCanvas = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);

	check(ParentCanvas && BorderTitle);
	BorderTitle->OnMouseButtonUpEvent.BindUFunction(this, FName("OnMouseButtonUpEvnt"));
	BorderTitle->OnMouseButtonDownEvent.BindUFunction(this, FName("OnMouseButtonDownEvnt"));

	Super::NativeConstruct();
}

FEventReply UDraggableWindowContent::OnMouseButtonUpEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent)
{
	check(Parent);
	Parent->SetDragging(false);
	FEventReply EvntReply = FEventReply();
	//EvntReply.NativeReply = NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	return EvntReply;
	
}

FEventReply UDraggableWindowContent::OnMouseButtonDownEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent)
{
	check(Parent);
	Parent->SetDragging(true);
	FEventReply EvntReply = FEventReply();
	//EvntReply.NativeReply = NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	return EvntReply;
}
