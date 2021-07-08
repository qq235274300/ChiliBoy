// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCUserWidget.h"
#include "SSCRootWidget.generated.h"

class UCanvasPanel;
class UImage;
class UOverlay;
class USSCPanelWidget;
/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCRootWidget : public USSCUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize()override;


public:
	UFUNCTION()
		void AdvanceLoadPanel(FName WealthName);
	UFUNCTION()
		void ShowPanel(FName WealthName);
	UFUNCTION()
		void HidePanel(FName WealthName);
	UFUNCTION()
		void ExitPanel(FName WealthName);

public:
/**********************绑定回调********************************/
	UFUNCTION()
		void BindAdvanceLoadEvnt(FName WealthName, UUserWidget* WeathWidget);
	UFUNCTION()
		void BindShowPanelEvnt(FName WealthName, UUserWidget* WeathWidget);

/************************************************************/

protected:

	void DoEnterPanel(FName WealthName);
	void DoDispalyPanel(FName WealthName);

	void EnterPanelDoNothing(UCanvasPanel* ParentLayout,USSCPanelWidget* PanelWidget);
	void EnterPanelDoNothing(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget);

	void EnterPanelHideOther(UCanvasPanel* ParentLayout, USSCPanelWidget* PanelWidget);
	void EnterPanelHideOther(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget);

	void EnterPanelPopsUp(UCanvasPanel* ParentLayout, USSCPanelWidget* PanelWidget);
	void EnterPanelPopsUp(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget);

	void DispalyPanelDoNothing(USSCPanelWidget* PanelWidget);
	void DispalyPanelHideOther(USSCPanelWidget* PanelWidget);
	void DispalyPanelPopsUp(USSCPanelWidget* PanelWidget);

	void HidePanelDoNothing(USSCPanelWidget* PanelWidget);
	void HidePanelHideOther(USSCPanelWidget* PanelWidget);
	void HidePanelPopsUp(USSCPanelWidget* PanelWidget);

	void ExitPanelDoNothing(USSCPanelWidget* PanelWidget);
	void ExitPanelHideOther(USSCPanelWidget* PanelWidget);
	void ExitPanelPopsUp(USSCPanelWidget* PanelWidget);

	UFUNCTION()
	void WaitShowPanel();
	//PanelExit 回调方法
	UFUNCTION()
		void BindPanelExit(ELayOutType LayoutType, UPanelWidget* InLayout);

protected:
/************************************************************/
	UPROPERTY()
		TArray<UCanvasPanel*> ActiveCanvasArray;
	UPROPERTY()
		TArray<UCanvasPanel*> UnActiveCanvasArray;
	UPROPERTY()
		TArray<UOverlay*> ActiveOverlayArray;
	UPROPERTY()
		TArray<UOverlay*> UnActiveOverlayArray;
	UPROPERTY()
		TArray<FName> LoadedPanelArray;

	TMap<FName, USSCPanelWidget*> AllPanelGroup;
	TMap<FName, USSCPanelWidget*> ShowPanelGroup;
	TMap<FName, USSCPanelWidget*> PopPanelGroup;
	
/************************************************************/


/************************************************************/
	void ActiveMask(UCanvasPanel* ParentLayout, EPanelTransparentType TransparentType);
	void ActiveMask(UOverlay* ParentLayout, EPanelTransparentType TransparentType);

	void TransferMask(USSCPanelWidget* PanelWidget);

	void RemoveMask(UPanelWidget* ParentLayout = NULL);

/************************************************************/


/************************************************************/
	UPROPERTY()
		UCanvasPanel* RootCanvas;
	UPROPERTY() 
		UImage* Mask; //弹窗遮罩

	UPROPERTY(EditAnywhere, Category = "CustomData",meta= (DisplayName = "FullMaskColor"))
		FLinearColor FullTransparentColor;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "HighMaskColor"))
		FLinearColor TranslucenceColor;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "LowMaskColor"))
		FLinearColor LowTransparentColor;
/************************************************************/


protected:
	TArray<FName> WaitShowPanelArray;
	FName WaitShowPanelTaskName;
};
