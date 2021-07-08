// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableWindow.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include <DraggableWindowContent.h>

UDraggableWindow::UDraggableWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsDragging = false;
}

void UDraggableWindow::NativeConstruct()
{
	WindowContentSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowContent);
	WindowContentSlot->SetAnchors(FAnchors(0.f));
	WindowContentSlot->SetAutoSize(true);
	Super::NativeConstruct();
}

void UDraggableWindow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bIsDragging)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		float MouseX = 0.f;
		float MouseY = 0.f;
		UWidgetLayoutLibrary::GetMousePositionScaledByDPI(playerController, MouseX, MouseY);
		const FVector2D CurrentMousePos = FVector2D(MouseX, MouseY);

		FVector2D FollowPos =  CurrentMousePos - ReltivePos;
		WindowContentSlot->SetPosition(FollowPos);
	}
		
}

void UDraggableWindow::AddWindowContent(const UObject* WorldContextObject, TSubclassOf<UDraggableWindowContent> InWindowContent)
{
	if (!InWindowContent) return;
	APlayerController*  playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	UDraggableWindowContent* WindowContent0 = Cast<UDraggableWindowContent>(CreateWidget(playerController, InWindowContent));
	WindowContent0->Parent = this;
	UCanvasPanelSlot* ChildSlot = WindowContent->AddChildToCanvas(WindowContent0);
	ChildSlot->SetAutoSize(true);
}

void UDraggableWindow::SetDragging(bool InIsDragging)
{
	if (!InIsDragging)
	{
		bIsDragging = false;
		return;
	}
	ReltivePos = GetCurrentMousePosByDPI();
	bIsDragging = true;
}

FVector2D UDraggableWindow::GetCurrentMousePosByDPI()
{
	float MouseX = 0.f;
	float MouseY = 0.f;
	APlayerController*  playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(playerController);
	UWidgetLayoutLibrary::GetMousePositionScaledByDPI(playerController, MouseX, MouseY);
	const FVector2D CurrentMousePos = FVector2D(MouseX, MouseY);
	const FVector2D SlotPos = WindowContentSlot->GetPosition();
	return CurrentMousePos - SlotPos;
}
