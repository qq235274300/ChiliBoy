// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCPanelWidget.h"


FName USSCPanelWidget::InvokeDelayName = TEXT("ExitInvoke");
 

int32 USSCPanelWidget::UIFarmeModuleIndex(1);

FName USSCPanelWidget::SSCUIRootName(TEXT("SSCUIRoot"));

FName USSCPanelWidget::PanelExitCallBackName(TEXT("PanelExitCallBack"));

FName USSCPanelWidget::ShowUIPanelName(TEXT("ShowPanel"));

FName USSCPanelWidget::HideUIPanelName(TEXT("HidePanel"));

FName USSCPanelWidget::ExitUIPanelName(TEXT("ExitPanel"));

FName USSCPanelWidget::AdvanceLoadPanelName(TEXT("AdvanceLoadPanel"));

void USSCPanelWidget::PanelEnter()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayPanelEnterAnim();
}

void USSCPanelWidget::PanelHidden()
{
	StartInvokeDelay(InvokeDelayName, PlayPanelExitAnim(), this, &USSCPanelWidget::SetPanelHidden);
	//PlayPanelExitAnim();	
}

void USSCPanelWidget::PanelDisplay()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayPanelEnterAnim();
}

void USSCPanelWidget::PanelFreeze()
{

}

void USSCPanelWidget::PanelUnFreeze()
{

}

void USSCPanelWidget::PanelExit()
{
	if (GetVisibility() != ESlateVisibility::Hidden)
	{
		StartInvokeDelay(InvokeDelayName, PlayPanelExitAnim(), this, &USSCPanelWidget::SetPanelExit);
	}
	else
	{
		SetPanelExit();
	}
}

void USSCPanelWidget::SetPanelHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USSCPanelWidget::SetPanelExit()
{
	UPanelWidget* ParentLayout = GetParent();
	if (ParentLayout)
	{
		RemoveFromParent();

		PanelExitCallBack(UIFarmeModuleIndex, SSCUIRootName, PanelExitCallBackName, UINature.LayOutType, ParentLayout);
	}
	DestroySelf();
}

void USSCPanelWidget::ShowSelfPanel()
{
	ShowUIPanel(GetObjectName());
}

void USSCPanelWidget::HideSelfPanel()
{
	HideUIPanel(GetObjectName());
}

void USSCPanelWidget::ExitSelfPanel()
{
	ExitUIPanel(GetObjectName());
}

void USSCPanelWidget::AdvanceLoadSelfPanel(FName PanelName)
{
	OperatorUIPanel(UIFarmeModuleIndex, SSCUIRootName, AdvanceLoadPanelName, PanelName);
}

void USSCPanelWidget::ShowUIPanel(FName PanelName)
{
	OperatorUIPanel(UIFarmeModuleIndex, SSCUIRootName, ShowUIPanelName, PanelName);
}

void USSCPanelWidget::HideUIPanel(FName PanelName)
{
	OperatorUIPanel(UIFarmeModuleIndex, SSCUIRootName, HideUIPanelName, PanelName);
}

void USSCPanelWidget::ExitUIPanel(FName PanelName)
{
	OperatorUIPanel(UIFarmeModuleIndex, SSCUIRootName, ExitUIPanelName, PanelName);
}

