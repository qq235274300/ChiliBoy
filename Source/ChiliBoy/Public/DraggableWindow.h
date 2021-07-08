// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Widgets/Layout/Anchors.h>
#include "DraggableWindow.generated.h"

/**
 * 
 */
class UDraggableWindowContent;
class UCanvasPanelSlot;
class UCanvasPanel;

UCLASS()
class CHILIBOY_API UDraggableWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	UDraggableWindow(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct()override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget", meta = (WorldContext = "WorldContextObject"))
	void AddWindowContent(const UObject* WorldContextObject,TSubclassOf<UDraggableWindowContent> InWindowContent);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget")
	void SetDragging(bool InIsDragging);
private:
	FVector2D GetCurrentMousePosByDPI();
public:
	UPROPERTY()
	UCanvasPanelSlot* WindowContentSlot;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* WindowContent;

private:
	FAnchors WindowContenAnchors;
	bool bIsDragging; 
	FVector2D ReltivePos;
};
