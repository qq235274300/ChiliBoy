// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SimpleDraggableWindow.generated.h"

class UBorder;
class UCanvasPanel;
class UCanvasPanelSlot;
class UUserWidget;
/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USimpleDraggableWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	 USimpleDraggableWindow(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct()override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	
public:
	UFUNCTION(BlueprintCallable,BlueprintCosmetic,Category ="SSCDraggableWidget", meta = (WorldContext = "WorldContextObject"))
	static USimpleDraggableWindow* CreateDraggleWindow(const UObject* WorldContextObject, TSubclassOf<USimpleDraggableWindow> DraggableWigetClass, TSubclassOf<UUserWidget> ChildWidgetClass,
		const FVector2D StartSize = FVector2D(800.f,600.f), const bool canDrag = true, const bool canReszie = true, const bool CenterToScreen = true, int32 PlayerIndex = 0);

protected:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void CenterWindowToScreen();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void AddContentWidgetClass(TSubclassOf<UUserWidget> CreateWidgetClass, const bool bClearPrevious = true);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void AddContentWidget(UUserWidget* CreateWidget, const bool bClearPrevious = true);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void OnCloseEvnt();
	UFUNCTION( BlueprintCallable, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void SetTitleEvnt();
private:
	
	void OnMouseButtonUpEvnt();
	const FVector2D DetermineNewSize(const FVector2D& Delta)const;

	UFUNCTION()
		FEventReply OnTitleBorderMouseUpEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent);
	UFUNCTION()
		FEventReply OnTitleBorderMouseDownEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent);
	UFUNCTION()
		FEventReply OnReszieBorderMouseDownEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent);
	/*************************************************/
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void OnAddContentWidgetEvnt(const UUserWidget* AddedWidget);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void OnDragStart(const FPointerEvent& InMouseEvent);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "SSCDraggableWidget")
		void OnResizeStart(const FPointerEvent& InMouseEvent);
private:
	/*******************Data**************************/
	UPROPERTY(EditAnywhere,Category = "CustomData")
	uint8 bEnableDrag : 1;
	UPROPERTY(EditAnywhere, Category = "CustomData")
	uint8 bEnableResize : 1;
	UPROPERTY(EditAnywhere, Category = "CustomData")
	uint8 bIsDragging : 1;
	UPROPERTY(EditAnywhere, Category = "CustomData")
	uint8 bIsResizing : 1; 
	UPROPERTY(EditAnywhere, Category = "CustomData",meta= (EditCondition = "bEnableResize"))
	float ResizeMinWidth;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (EditCondition = "bEnableResize"))
	float ResizeMaxWidth;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (EditCondition = "bEnableResize"))
	float ReszieMinHeight;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (EditCondition = "bEnableResize"))
	float ResizeMaxHeight;
	
	
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "CustomData", meta = (EditCondition = "bEnableDrag"))
		FKey DragKey;
	/*************************************************/
	
	/********************Bind************************/
	UPROPERTY(meta = (BindWidgetOptional))
	UBorder* TitleBorder;
	UPROPERTY(meta = (BindWidgetOptional))
	UBorder* ResizeBorder;
	UPROPERTY(meta = (BindWidgetOptional))
	UCanvasPanel* ChildPanel;
	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* Title_Text;
	UPROPERTY()
		UCanvasPanelSlot* ParentSlot;
	/*************************************************/

	/*************************************************/
	FVector2D LastMousePos;

	
	FVector2D PreDragSize;
	
	FVector2D PreResizeOffset;
	FVector2D PreResizeAlignment;

	uint8 bIsAlignmentAccounted : 1;
	uint8 bStartInCenterScreen : 1;
	uint8 bIsMouseButtonDown : 1;
	int32 CurrentZOrder = -1;
public:
	UPROPERTY(EditAnywhere, Category = "CustomData",meta = (DisplayName = "MoveLimited"))
		FVector2D Boundary;
	UPROPERTY(EditAnywhere, Category = "CustomData",meta = (DisplayName = "DisplaySize"))
		FVector2D StartSize;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "TitleName"))
		FString Title;
};
