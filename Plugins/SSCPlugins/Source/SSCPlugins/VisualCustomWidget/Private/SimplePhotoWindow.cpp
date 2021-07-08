// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplePhotoWindow.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Kismet/KismetMathLibrary.h"

USimplePhotoWindow::USimplePhotoWindow(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	ConstructSuccess = false;
	isSwitching = false;
	PhotoOffset = 0.f;
	CurrentOffset = 0.f;
	SwitchSpeed = 1000.f;
	CurrentCount = 0;
}

bool USimplePhotoWindow::GetIsConstructSuccessful() const
{
	return ConstructSuccess;
}

void USimplePhotoWindow::NativeConstruct()
{
	RootCanvas = Cast<UCanvasPanel>(GetRootWidget());
	if (RootCanvas && Sc_BG)
	{
		MaxCount = Sc_BG->GetAllChildren().Num() - 1;
		
		
		ConstructSuccess = true;
	}
	if (Btn_left)
	{
		FScriptDelegate Del;
		Del.BindUFunction(this, "SwitchLeftEvnt");
		Btn_left->OnClicked.Add(Del);
	}

	if (Btn_Right)
	{
		FScriptDelegate Del;
		Del.BindUFunction(this, "SwitchRightEvnt");
		Btn_Right->OnClicked.Add(Del);
	}

	if (Btn_Quit)
	{
		FScriptDelegate Del;
		Del.BindUFunction(this, "OnCloseEvnt");
		Btn_Quit->OnClicked.Add(Del);
	}

	Super::NativeConstruct();
}

void USimplePhotoWindow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (GetIsConstructSuccessful())
	{
		Sc_BG->SetScrollOffset(UKismetMathLibrary::FInterpTo_Constant(Sc_BG->GetScrollOffset(), CurrentOffset, SwitchSpeed, InDeltaTime));
		if (CurrentOffset == Sc_BG->GetScrollOffset())
		{
			isSwitching = false;
		}
		else
		{
			isSwitching = true;
		}
	}

	Super::NativeTick(MyGeometry, InDeltaTime);
}

void USimplePhotoWindow::SwitchLeftEvnt()
{
	if (GetIsConstructSuccessful() && !isSwitching && CurrentCount>=1 )
	{
		CurrentOffset -= PhotoOffset;
	
		CurrentCount--;
	}
}

void USimplePhotoWindow::SwitchRightEvnt()
{
	if (GetIsConstructSuccessful() && !isSwitching && CurrentCount<MaxCount && CurrentCount >= 0)
	{
		CurrentOffset += PhotoOffset;
		
		CurrentCount++;
	}
}

void USimplePhotoWindow::OnCloseEvnt_Implementation()
{
	RemoveFromParent();
}
