// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimplePhotoWindow.generated.h"

class UButton;
class UCanvasPanelSlot;
class UScrollBox;

//Î´Ð´Íê
/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USimplePhotoWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USimplePhotoWindow(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "SSCSimplePhoto")
	bool GetIsConstructSuccessful()const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintCosmetic, Category = "SSCSimplePhoto")
		void OnCloseEvnt();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;
protected:
	virtual void NativeConstruct()override;


/********************Bind************************/
private:
	UFUNCTION()
		void SwitchLeftEvnt();
	
	UFUNCTION()
		void SwitchRightEvnt();

/*************************************************/

/********************Bind************************/
protected:
	UPROPERTY()
		UCanvasPanel* RootCanvas;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* Btn_left;
	
	UPROPERTY(meta = (BindWidgetOptional))
		UButton* Btn_Right;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* Btn_Quit;
	UPROPERTY(meta = (BindWidgetOptional))
		UScrollBox* Sc_BG;
/*************************************************/
private:
	bool ConstructSuccess;
	bool isSwitching;
	int32 MaxCount;
	int32 CurrentCount;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "MoveOffset"))
	float PhotoOffset;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "CurrentOffset"))
	float CurrentOffset;
	UPROPERTY(EditAnywhere, Category = "CustomData", meta = (DisplayName = "SwitchSpeed"))
	float SwitchSpeed;
};
