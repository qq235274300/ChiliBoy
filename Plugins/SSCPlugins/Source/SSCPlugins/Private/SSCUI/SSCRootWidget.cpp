// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCRootWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "SSCPanelWidget.h"


bool USSCRootWidget::Initialize()
{
	if (!Super::Initialize()) return false;
	
	RootCanvas = Cast<UCanvasPanel>(GetRootWidget());
	RootCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible); 
	
	Mask = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());

	FullTransparentColor = FLinearColor(1.f, 1.0f, 1.0f, 0.f);
	TranslucenceColor = FLinearColor(1.f, 1.0f, 1.0f, 0.6f);
	LowTransparentColor = FLinearColor(1.f, 1.0f, 1.0f, 0.3f);

	WaitShowPanelTaskName = FName("WaitShowPanelTask");

	return true;
}

void USSCRootWidget::AdvanceLoadPanel(FName WealthName)
{
	if (AllPanelGroup.Contains(WealthName) || LoadedPanelArray.Contains(WealthName))
		return;
	BuildSinglClassWealth(EWealthClassType::Widget, WealthName, "BindAdvanceLoadEvnt");
	
	LoadedPanelArray.Push(WealthName);
}

void USSCRootWidget::ShowPanel(FName WealthName)
{
	if (ShowPanelGroup.Contains(WealthName) || PopPanelGroup.Contains(WealthName))
		return;
	if (!AllPanelGroup.Contains(WealthName) && !LoadedPanelArray.Contains(WealthName))
	{
		BuildSinglClassWealth(EWealthClassType::Widget, WealthName, "BindShowPanelEvnt");
		LoadedPanelArray.Push(WealthName);
		return;
	}
	if (!AllPanelGroup.Contains(WealthName) && LoadedPanelArray.Contains(WealthName) && !WaitShowPanelArray.Contains(WealthName))
	{
		WaitShowPanelArray.Push(WealthName);
		StartInvokeRepeated(WaitShowPanelTaskName,0.3f,0.3f,this,&USSCRootWidget::WaitShowPanel);
		return;
	}


	if (AllPanelGroup.Contains(WealthName) )
	{
		USSCPanelWidget* tmpWidget = *AllPanelGroup.Find(WealthName);
		//如有父节点 表示不是第一次显示
		if (tmpWidget->GetParent())
		{
			DoDispalyPanel(WealthName);
		}
		else
		{
			DoEnterPanel(WealthName);
		}
	}
}

void USSCRootWidget::HidePanel(FName WealthName)
{
	if (!ShowPanelGroup.Contains(WealthName) && !PopPanelGroup.Contains(WealthName))
		return;
	USSCPanelWidget* _PanelWidget = *AllPanelGroup.Find(WealthName);
	if (_PanelWidget)
	{
		switch (_PanelWidget->UINature.PanelShowType)
		{
		case EPanelShowType::DoNothing:
			HidePanelDoNothing(_PanelWidget);
			break;
		case EPanelShowType::HideOther:
			HidePanelHideOther(_PanelWidget);
			break;
		case EPanelShowType::PopUps:
			HidePanelPopsUp(_PanelWidget);
			break;
		}
	}

}

void USSCRootWidget::ExitPanel(FName WealthName)
{
	if (!AllPanelGroup.Contains(WealthName) && LoadedPanelArray.Contains(WealthName))
		return;
	if (!AllPanelGroup.Contains(WealthName))
		return;	
	USSCPanelWidget* PanelWidget = *AllPanelGroup.Find(WealthName);
	
	if (!ShowPanelGroup.Contains(WealthName) && !PopPanelGroup.Contains(WealthName))
	{
		AllPanelGroup.Remove(WealthName);
		LoadedPanelArray.Remove(WealthName);
		PanelWidget->PanelExit();
		return;
	}

	switch (PanelWidget->UINature.PanelShowType)
	{
	case EPanelShowType::DoNothing:
		ExitPanelDoNothing(PanelWidget);
		break;
	case EPanelShowType::HideOther:
		ExitPanelHideOther(PanelWidget);
		break;
	case EPanelShowType::PopUps:
		ExitPanelPopsUp(PanelWidget);
		break;
	}
}

void USSCRootWidget::BindAdvanceLoadEvnt(FName WealthName, UUserWidget* WeathWidget)
{
	USSCPanelWidget* PanelWidget = Cast<USSCPanelWidget>(WeathWidget);
	if (!PanelWidget)
	{
		SSCHelper::Debug() << WealthName << "Set Parent Class Wrong" << SSCHelper::Endl();
		return;
	}
	PanelWidget->RegisterToModule(ModuleIndex, WealthName);
	AllPanelGroup.Add(WealthName, PanelWidget);
}

void USSCRootWidget::BindShowPanelEvnt(FName WealthName, UUserWidget* WeathWidget)
{
	USSCPanelWidget* PanelWidget = Cast<USSCPanelWidget>(WeathWidget);
	if (!PanelWidget)
	{
		SSCHelper::Debug() << WealthName << "Set Parent Class Wrong" << SSCHelper::Endl();
		return;
	}
	PanelWidget->RegisterToModule(ModuleIndex, WealthName);
	AllPanelGroup.Add(WealthName, PanelWidget);
	
	DoEnterPanel(WealthName);
}

void USSCRootWidget::DoEnterPanel(FName WealthName)
{
	//获取面板实例
	USSCPanelWidget* PanelWidget = *AllPanelGroup.Find(WealthName);
	//区分布局类型进行添加到界面
	if (PanelWidget->UINature.LayOutType == ELayOutType::Canvas)
	{
		//获取布局控件, 父控件
		UCanvasPanel* WorkLayout = NULL;

		//判断最底层的布局控件是否是Canvas
		if (RootCanvas->GetChildrenCount() > 0)
			WorkLayout = Cast<UCanvasPanel>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));

		if (!WorkLayout)
		{
			if (UnActiveCanvasArray.Num() == 0)
			{
				WorkLayout = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
				WorkLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
				WorkLayout = UnActiveCanvasArray.Pop();
			//添加布局控件到界面最顶层
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//添加到激活画布组
			ActiveCanvasArray.Push(WorkLayout);
		}

		switch (PanelWidget->UINature.PanelShowType)
		{
		case EPanelShowType::DoNothing:
			EnterPanelDoNothing(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::HideOther:
			EnterPanelHideOther(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::PopUps:
			EnterPanelPopsUp(WorkLayout, PanelWidget);
			break;
		}
	}
	else
	{
		UOverlay* WorkLayout = NULL;

		//如果存在布局控件, 试图把最后一个布局控件转换成Overlay
		if (RootCanvas->GetChildrenCount() > 0)
			WorkLayout = Cast<UOverlay>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));

		if (!WorkLayout)
		{
			if (UnActiveOverlayArray.Num() == 0)
			{
				WorkLayout = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
				WorkLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
				WorkLayout = UnActiveOverlayArray.Pop();
			//添加布局控件到界面最顶层
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//添加到激活画布组
			ActiveOverlayArray.Push(WorkLayout);
		}

		switch (PanelWidget->UINature.PanelShowType)
		{
		case EPanelShowType::DoNothing:
			EnterPanelDoNothing(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::HideOther:
			EnterPanelHideOther(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::PopUps:
			EnterPanelPopsUp(WorkLayout, PanelWidget);
			break;
		}
	}
	
}

void USSCRootWidget::DoDispalyPanel(FName WealthName)
{
	USSCPanelWidget* _PanelWidget = *AllPanelGroup.Find(WealthName);
	switch (_PanelWidget->UINature.PanelShowType)
	{
	case EPanelShowType::DoNothing:
		DispalyPanelDoNothing(_PanelWidget);
		break;
	case EPanelShowType::HideOther:
		DispalyPanelHideOther(_PanelWidget);
		break;
	case EPanelShowType::PopUps:
		DispalyPanelPopsUp(_PanelWidget);
		break;
	}
}

void USSCRootWidget::EnterPanelDoNothing(UCanvasPanel* ParentLayout, USSCPanelWidget* PanelWidget)
{
	UCanvasPanelSlot*  _Slot = ParentLayout->AddChildToCanvas(PanelWidget);
	_Slot->SetAnchors(PanelWidget->UINature.Anchors);
	_Slot->SetOffsets(PanelWidget->UINature.Margin);
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void USSCRootWidget::EnterPanelDoNothing(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget)
{
	UOverlaySlot*  _Slot = ParentLayout->AddChildToOverlay(PanelWidget);
	_Slot->SetPadding(PanelWidget->UINature.Margin);
	_Slot->SetVerticalAlignment(PanelWidget->UINature.VerticalAlignment);
	_Slot->SetHorizontalAlignment(PanelWidget->UINature.HorizontalAlignment);
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void USSCRootWidget::EnterPanelHideOther(UCanvasPanel* ParentLayout, USSCPanelWidget* PanelWidget)
{
	for (TMap<FName, USSCPanelWidget*>::TIterator it(ShowPanelGroup); it; ++it)
	{
		if (PanelWidget->UINature.LayOutLevel == ELayOutLevel::Level_ALL ||  it.Value()->UINature.LayOutLevel == PanelWidget->UINature.LayOutLevel)
		{
			it.Value()->PanelHidden();
		}
	}
	
	UCanvasPanelSlot* _Slot = ParentLayout->AddChildToCanvas(PanelWidget);
	_Slot->SetAnchors(PanelWidget->UINature.Anchors);
	_Slot->SetOffsets(PanelWidget->UINature.Margin);
	
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void USSCRootWidget::EnterPanelHideOther(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget)
{
	for (TMap<FName, USSCPanelWidget*>::TIterator it(ShowPanelGroup); it; ++it)
	{
		if (PanelWidget->UINature.LayOutLevel == ELayOutLevel::Level_ALL || it.Value()->UINature.LayOutLevel == PanelWidget->UINature.LayOutLevel)
		{
			it.Value()->PanelHidden();
		}
	}

	UOverlaySlot* _Slot = ParentLayout->AddChildToOverlay(PanelWidget);
	_Slot->SetPadding(PanelWidget->UINature.Margin);
	_Slot->SetHorizontalAlignment(PanelWidget->UINature.HorizontalAlignment);
	_Slot->SetVerticalAlignment(PanelWidget->UINature.VerticalAlignment);

	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void USSCRootWidget::EnterPanelPopsUp(UCanvasPanel* ParentLayout, USSCPanelWidget* PanelWidget)
{
	//冻结弹窗UI
	if (PopPanelGroup.Num() > 0)
	{
		TArray<USSCPanelWidget*> PopsUIArray;
		PopPanelGroup.GenerateValueArray(PopsUIArray);
		PopsUIArray[PopsUIArray.Num() - 1]->PanelFreeze();
	}
	//激活遮罩
	ActiveMask(ParentLayout, PanelWidget->UINature.TransparentType);

	UCanvasPanelSlot* _Slot = ParentLayout->AddChildToCanvas(PanelWidget);
	_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
	_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));

	PopPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();

}

void USSCRootWidget::EnterPanelPopsUp(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget)
{
	//冻结弹窗UI
	if (PopPanelGroup.Num() > 0)
	{
		TArray<USSCPanelWidget*> PopsUIArray;
		PopPanelGroup.GenerateValueArray(PopsUIArray);
		PopsUIArray[PopsUIArray.Num() - 1]->PanelFreeze();
	}
	//激活遮罩
	ActiveMask(ParentLayout, PanelWidget->UINature.TransparentType);

	UOverlaySlot* _Slot = ParentLayout->AddChildToOverlay(PanelWidget);
	_Slot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
	_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	PopPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void USSCRootWidget::DispalyPanelDoNothing(USSCPanelWidget* PanelWidget)
{
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelDisplay();
}

void USSCRootWidget::DispalyPanelHideOther(USSCPanelWidget* PanelWidget)
{
	for (TMap<FName, USSCPanelWidget*>::TIterator it(ShowPanelGroup); it; ++it)
	{
		if (PanelWidget->UINature.LayOutLevel == ELayOutLevel::Level_ALL || it.Value()->UINature.LayOutLevel == PanelWidget->UINature.LayOutLevel)
		{
			it.Value()->PanelHidden();
		}
	}

	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelDisplay();

}

void USSCRootWidget::DispalyPanelPopsUp(USSCPanelWidget* PanelWidget)
{
	if (PopPanelGroup.Num() > 0)
	{
		TArray<USSCPanelWidget*> PanelArray;
		PopPanelGroup.GenerateValueArray(PanelArray);
		PanelArray[PanelArray.Num() - 1]->PanelFreeze();
	}

	if (PanelWidget->UINature.LayOutType == ELayOutType::Canvas)
	{
		UCanvasPanel* ParentLayout = Cast<UCanvasPanel>(PanelWidget->GetParent());
		UCanvasPanelSlot* _Slot = Cast<UCanvasPanelSlot>(PanelWidget->Slot);
		FAnchors PreAnchors = _Slot->GetAnchors();
		FMargin PreOffset = _Slot->GetOffsets();

		PanelWidget->RemoveFromParent();
		if (ParentLayout->GetChildrenCount() == 0)
		{
			ParentLayout->RemoveFromParent();
			ActiveCanvasArray.Remove(ParentLayout);
			UnActiveCanvasArray.Push(ParentLayout);
		}

		UCanvasPanel* LayOut = nullptr;
		if (RootCanvas->GetChildrenCount() > 0)
		{
			LayOut = Cast<UCanvasPanel>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));
		}
			
		if (!LayOut)
		{
				if (UnActiveCanvasArray.Num() == 0)
				{
					LayOut = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
					LayOut->SetVisibility(ESlateVisibility::SelfHitTestInvisible);	
				}
				else
				{
					LayOut = UnActiveCanvasArray.Pop();
				}
				UCanvasPanelSlot* FrameCanvSlot = RootCanvas->AddChildToCanvas(LayOut);
				FrameCanvSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
				FrameCanvSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
				ActiveCanvasArray.Push(LayOut);
		}
		//激活mask
		ActiveMask(LayOut, PanelWidget->UINature.TransparentType);
		UCanvasPanelSlot* _Slot0 = LayOut->AddChildToCanvas(PanelWidget);
		_Slot0->SetAnchors(PreAnchors);
		_Slot0->SetOffsets(PreOffset);

	}
	else
	{
		UOverlay* PreWorkLayout = Cast<UOverlay>(PanelWidget->GetParent());
		UOverlaySlot* PrePanelSlot = Cast<UOverlaySlot>(PanelWidget->Slot);
		FMargin PrePadding = PrePanelSlot->Padding;
		TEnumAsByte<EHorizontalAlignment> PreHAlign = PrePanelSlot->HorizontalAlignment;
		TEnumAsByte<EVerticalAlignment> PreVAlign = PrePanelSlot->VerticalAlignment;

		//将PanelWidget从当前父控件移除
		PanelWidget->RemoveFromParent();
		//处理父控件
		if (PreWorkLayout->GetChildrenCount() == 0)
		{
			PreWorkLayout->RemoveFromParent();
			ActiveOverlayArray.Remove(PreWorkLayout);
			UnActiveOverlayArray.Push(PreWorkLayout);
		}

		UOverlay* WorkLayout = NULL;

		//如果存在布局控件, 试图把最后一个布局控件转换成Overlay
		if (RootCanvas->GetChildrenCount() > 0)
			WorkLayout = Cast<UOverlay>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));

		if (!WorkLayout)
		{
			if (UnActiveOverlayArray.Num() == 0)
			{
				WorkLayout = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
				WorkLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
				WorkLayout = UnActiveOverlayArray.Pop();
			//添加布局控件到界面最顶层
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//添加到激活画布组
			ActiveOverlayArray.Push(WorkLayout);
		}

		//激活遮罩到最顶层弹窗
		ActiveMask(WorkLayout, PanelWidget->UINature.TransparentType);

		//添加弹窗到获取到的最顶层的布局控件
		UOverlaySlot* PanelSlot = WorkLayout->AddChildToOverlay(PanelWidget);
		PanelSlot->SetPadding(PrePadding);
		PanelSlot->SetHorizontalAlignment(PreHAlign);
		PanelSlot->SetVerticalAlignment(PreVAlign);
		
	}
	//添加弹窗
	PopPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelDisplay();
}

void USSCRootWidget::HidePanelDoNothing(USSCPanelWidget* PanelWidget)
{
	ShowPanelGroup.Remove(PanelWidget->GetObjectName());
	PanelWidget->PanelHidden();
}

void USSCRootWidget::HidePanelHideOther(USSCPanelWidget* PanelWidget)
{
	ShowPanelGroup.Remove(PanelWidget->GetObjectName());
	//显示同一层级Panel
	for (TMap<FName, USSCPanelWidget*>::TIterator it(ShowPanelGroup); it; ++it)
	{
		if (PanelWidget->UINature.LayOutLevel == ELayOutLevel::Level_ALL || PanelWidget->UINature.LayOutLevel == it.Value()->UINature.LayOutLevel)
		{
			it.Value()->PanelDisplay();
		}
	}
	
	PanelWidget->PanelHidden();
}

void USSCRootWidget::HidePanelPopsUp(USSCPanelWidget* PanelWidget)
{
	TArray<USSCPanelWidget*> PopStack;
	PopPanelGroup.GenerateValueArray(PopStack);
	
	//只有最有一个才是激活状态需要隐藏
	if (PopStack[PopStack.Num() - 1] != PanelWidget) return;
	
	PopPanelGroup.Remove(PanelWidget->GetObjectName());
	PanelWidget->PanelHidden();
	//调整弹窗
	PopStack.Pop();
	if (PopStack.Num() > 0)
	{
		USSCPanelWidget* PrePanelWidget = PopStack[PopStack.Num() - 1];
		//转移
		TransferMask(PrePanelWidget);
		PrePanelWidget->PanelUnFreeze();
	}
	else
	{
		RemoveMask();
	}
	
	
}

void USSCRootWidget::ExitPanelDoNothing(USSCPanelWidget* PanelWidget)
{
	ShowPanelGroup.Remove(PanelWidget->GetObjectName());
	AllPanelGroup.Remove(PanelWidget->GetObjectName());
	LoadedPanelArray.Remove(PanelWidget->GetObjectName());

	//运行销毁生命周期
	PanelWidget->PanelExit();
}

void USSCRootWidget::ExitPanelHideOther(USSCPanelWidget* PanelWidget)
{
	ShowPanelGroup.Remove(PanelWidget->GetObjectName());
	AllPanelGroup.Remove(PanelWidget->GetObjectName());
	LoadedPanelArray.Remove(PanelWidget->GetObjectName());

	//显示同一层级下的其他UI面板, 如果该面板是Level_All层级, 显示所有显示组的面板
	for (TMap<FName, USSCPanelWidget*>::TIterator It(ShowPanelGroup); It; ++It)
		if (PanelWidget->UINature.LayOutLevel == ELayOutLevel::Level_ALL || PanelWidget->UINature.LayOutLevel == It.Value()->UINature.LayOutLevel)
			It.Value()->PanelDisplay();

	//运行销毁生命周期
	PanelWidget->PanelExit();
}

void USSCRootWidget::ExitPanelPopsUp(USSCPanelWidget* PanelWidget)
{

	//获取弹窗栈到数组
	TArray<USSCPanelWidget*> PopStack;
	PopPanelGroup.GenerateValueArray(PopStack);

	//如果不是最上层的弹窗, 直接返回
	if (PopStack[PopStack.Num() - 1] != PanelWidget)	
		return;
	
	PopPanelGroup.Remove(PanelWidget->GetObjectName());
	AllPanelGroup.Remove(PanelWidget->GetObjectName());
	LoadedPanelArray.Remove(PanelWidget->GetObjectName());
	//运行销毁生命周期函数
	PanelWidget->PanelExit();

	PopStack.Pop();
	if (PopStack.Num() > 0)
	{
		USSCPanelWidget* PrePanelWidget = PopStack[PopStack.Num() - 1];
		//转移遮罩到新的最顶层的弹窗的下一层
		TransferMask(PrePanelWidget);
		//回复被冻结的最顶层的弹窗
		PrePanelWidget->PanelUnFreeze();
	}
	else
		RemoveMask();
}

void USSCRootWidget::WaitShowPanel()
{
	TArray<FName> CompletedNames;
	for (int i = 0; i < WaitShowPanelArray.Num(); ++i)
	{
		if (AllPanelGroup.Contains(WaitShowPanelArray[i]))
		{
			DoEnterPanel(WaitShowPanelArray[i]);
			CompletedNames.Push(WaitShowPanelArray[i]);
		}
	}
	for (int i = 0; i < CompletedNames.Num(); ++i)
	{
		WaitShowPanelArray.Remove(CompletedNames[i]);
	}
	if (WaitShowPanelArray.Num() == 0)
	{
		StopInvoke(WaitShowPanelTaskName);
	}
}

void USSCRootWidget::BindPanelExit(ELayOutType LayoutType, UPanelWidget* InLayout)
{
	if (LayoutType == ELayOutType::Canvas)
	{
		UCanvasPanel* WorkLayout = Cast<UCanvasPanel>(InLayout);
		if (WorkLayout->GetChildrenCount() == 0)
		{
			WorkLayout->RemoveFromParent();
			ActiveCanvasArray.Remove(WorkLayout);
			UnActiveCanvasArray.Push(WorkLayout);
		}
	}
	else
	{
		UOverlay* WorkLayout = Cast<UOverlay>(InLayout);
		if (WorkLayout->GetChildrenCount() == 0)
		{
			WorkLayout->RemoveFromParent();
			ActiveOverlayArray.Remove(WorkLayout);
			UnActiveOverlayArray.Push(WorkLayout);
		}
	}
}

void USSCRootWidget::ActiveMask(UCanvasPanel* ParentLayout, EPanelTransparentType TransparentType)
{
	RemoveMask(ParentLayout);
	UCanvasPanelSlot* _Slot = ParentLayout->AddChildToCanvas(Mask);
	_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
	_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
	switch (TransparentType)
	{
	case EPanelTransparentType::FullTransparent:
		Mask->SetVisibility(ESlateVisibility::Visible);
		Mask->SetColorAndOpacity(FullTransparentColor);
		break;
	case EPanelTransparentType::Transparent:
		Mask->SetVisibility(ESlateVisibility::Visible);
		Mask->SetColorAndOpacity(TranslucenceColor);
		break;
	case EPanelTransparentType::LowTransparent:
		Mask->SetVisibility(ESlateVisibility::Visible);
		Mask->SetColorAndOpacity(LowTransparentColor);
		break;
	case EPanelTransparentType::FullTransparentClick:
		Mask->SetVisibility(ESlateVisibility::Hidden);
		Mask->SetColorAndOpacity(FullTransparentColor);
		break;
	
	}

	
}

void USSCRootWidget::ActiveMask(UOverlay* ParentLayout, EPanelTransparentType TransparentType)
{
	RemoveMask(ParentLayout);
	UOverlaySlot* _Slot = ParentLayout->AddChildToOverlay(Mask);
	_Slot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
	_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	switch (TransparentType)
	{
	case EPanelTransparentType::FullTransparent:
		Mask->SetVisibility(ESlateVisibility::Visible);
		Mask->SetColorAndOpacity(FullTransparentColor);
		break;
	case EPanelTransparentType::Transparent:
		Mask->SetVisibility(ESlateVisibility::Visible);
		Mask->SetColorAndOpacity(TranslucenceColor);
		break;
	case EPanelTransparentType::LowTransparent:
		Mask->SetVisibility(ESlateVisibility::Visible);
		Mask->SetColorAndOpacity(LowTransparentColor);
		break;
	case EPanelTransparentType::FullTransparentClick:
		Mask->SetVisibility(ESlateVisibility::Hidden);
		Mask->SetColorAndOpacity(FullTransparentColor);
		break;

	}
}

void USSCRootWidget::TransferMask(USSCPanelWidget* PanelWidget)
{
	TArray<USSCPanelWidget*> AbovePanelArray;
	TArray<FUINature> AboveNatureArray;
	
	if (PanelWidget->UINature.LayOutType == ELayOutType::Canvas)
	{
		UCanvasPanel* ParentLayout = Cast<UCanvasPanel>(PanelWidget->GetParent());
		int32 StartOrder = ParentLayout->GetChildIndex(PanelWidget);
		for (int32 i = StartOrder; i < ParentLayout->GetChildrenCount(); ++i)
		{
			USSCPanelWidget* TempPanel = Cast<USSCPanelWidget>(ParentLayout->GetChildAt(i));
			if (!TempPanel) continue;
			AbovePanelArray.Push(TempPanel);
			FUINature TempNature;
			UCanvasPanelSlot* _Slot = Cast<UCanvasPanelSlot>(TempPanel);
			TempNature.Anchors = _Slot->GetAnchors();
			TempNature.Margin = _Slot->GetOffsets();
			AboveNatureArray.Push(TempNature);
			
		}
		for (int i = 0; i < AbovePanelArray.Num(); ++i)
		{
			AbovePanelArray[i]->RemoveFromParent();
		}
		//添加遮罩
		UCanvasPanelSlot* _Slot = ParentLayout->AddChildToCanvas(Mask);
		_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
		switch (PanelWidget->UINature.TransparentType)
		{
		case EPanelTransparentType::FullTransparent:
			Mask->SetVisibility(ESlateVisibility::Visible);
			Mask->SetColorAndOpacity(FullTransparentColor);
			break;
		case EPanelTransparentType::Transparent:
			Mask->SetVisibility(ESlateVisibility::Visible);
			Mask->SetColorAndOpacity(TranslucenceColor);
			break;
		case EPanelTransparentType::LowTransparent:
			Mask->SetVisibility(ESlateVisibility::Visible);
			Mask->SetColorAndOpacity(LowTransparentColor);
			break;
		case EPanelTransparentType::FullTransparentClick:
			Mask->SetVisibility(ESlateVisibility::Hidden);
			Mask->SetColorAndOpacity(FullTransparentColor);
			break;

		}

		//重新添加
		for (int i = 0; i < AbovePanelArray.Num(); ++i)
		{
			UCanvasPanelSlot* _Slot = ParentLayout->AddChildToCanvas(AbovePanelArray[i]);
			_Slot->SetAnchors(AboveNatureArray[i].Anchors);
			_Slot->SetOffsets(AboveNatureArray[i].Margin);
		}

	}
	else
	{
		UOverlay* ParentLayout = Cast<UOverlay>(PanelWidget->GetParent());
		int32 StartOrder = ParentLayout->GetChildIndex(PanelWidget);
		for (int32 i = StartOrder; i < ParentLayout->GetChildrenCount(); ++i)
		{
			USSCPanelWidget* TempPanel = Cast<USSCPanelWidget>(ParentLayout->GetChildAt(i));
			if (!TempPanel) continue;
			AbovePanelArray.Push(TempPanel);
			FUINature TempNature;
			UOverlaySlot* _Slot = Cast<UOverlaySlot>(TempPanel);
			TempNature.Margin = _Slot->Padding;
			TempNature.VerticalAlignment = _Slot->VerticalAlignment;
			TempNature.HorizontalAlignment = _Slot->HorizontalAlignment;
			AboveNatureArray.Push(TempNature);

		}
		for (int i = 0; i < AbovePanelArray.Num(); ++i)
		{
			AbovePanelArray[i]->RemoveFromParent();
		}

		UOverlaySlot* _Slot = ParentLayout->AddChildToOverlay(Mask);
		_Slot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
		_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		switch (PanelWidget->UINature.TransparentType)
		{
		case EPanelTransparentType::FullTransparent:
			Mask->SetVisibility(ESlateVisibility::Visible);
			Mask->SetColorAndOpacity(FullTransparentColor);
			break;
		case EPanelTransparentType::Transparent:
			Mask->SetVisibility(ESlateVisibility::Visible);
			Mask->SetColorAndOpacity(TranslucenceColor);
			break;
		case EPanelTransparentType::LowTransparent:
			Mask->SetVisibility(ESlateVisibility::Visible);
			Mask->SetColorAndOpacity(LowTransparentColor);
			break;
		case EPanelTransparentType::FullTransparentClick:
			Mask->SetVisibility(ESlateVisibility::Hidden);
			Mask->SetColorAndOpacity(FullTransparentColor);
			break;

		}

		//重新添加
		for (int i = 0; i < AbovePanelArray.Num(); ++i)
		{
			UOverlaySlot* _Slot = ParentLayout->AddChildToOverlay(AbovePanelArray[i]);
			_Slot->SetPadding(AboveNatureArray[i].Margin);
			_Slot->SetVerticalAlignment(AboveNatureArray[i].VerticalAlignment);
			_Slot->SetHorizontalAlignment(AboveNatureArray[i].HorizontalAlignment);
		}
	}
}

void USSCRootWidget::RemoveMask(UPanelWidget* ParentLayout /*= NULL*/)
{
	
	//获取遮罩当前父控件
	UPanelWidget* MaskParent = Mask->GetParent();
	if (MaskParent)
	{
		//比较当前父控件与将要插入的父控件是否相同, 当前父控件的之控件为1
		if (MaskParent != ParentLayout && MaskParent->GetChildrenCount() == 1)
		{
			MaskParent->RemoveFromParent();
			UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(MaskParent);
			UOverlay* ParentOverlay = Cast<UOverlay>(MaskParent);
			if (ParentCanvas)
			{
				ActiveCanvasArray.Remove(ParentCanvas);
				UnActiveCanvasArray.Push(ParentCanvas);
			}
			else if (ParentOverlay)
			{
				ActiveOverlayArray.Remove(ParentOverlay);
				UnActiveOverlayArray.Push(ParentOverlay);
			}
		}
		//将遮罩从父级移除
		Mask->RemoveFromParent();
	}
	
}

