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
		//���и��ڵ� ��ʾ���ǵ�һ����ʾ
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
	//��ȡ���ʵ��
	USSCPanelWidget* PanelWidget = *AllPanelGroup.Find(WealthName);
	//���ֲ������ͽ�����ӵ�����
	if (PanelWidget->UINature.LayOutType == ELayOutType::Canvas)
	{
		//��ȡ���ֿؼ�, ���ؼ�
		UCanvasPanel* WorkLayout = NULL;

		//�ж���ײ�Ĳ��ֿؼ��Ƿ���Canvas
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
			//��Ӳ��ֿؼ����������
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//��ӵ��������
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

		//������ڲ��ֿؼ�, ��ͼ�����һ�����ֿؼ�ת����Overlay
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
			//��Ӳ��ֿؼ����������
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//��ӵ��������
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
	//���ᵯ��UI
	if (PopPanelGroup.Num() > 0)
	{
		TArray<USSCPanelWidget*> PopsUIArray;
		PopPanelGroup.GenerateValueArray(PopsUIArray);
		PopsUIArray[PopsUIArray.Num() - 1]->PanelFreeze();
	}
	//��������
	ActiveMask(ParentLayout, PanelWidget->UINature.TransparentType);

	UCanvasPanelSlot* _Slot = ParentLayout->AddChildToCanvas(PanelWidget);
	_Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
	_Slot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));

	PopPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();

}

void USSCRootWidget::EnterPanelPopsUp(UOverlay* ParentLayout, USSCPanelWidget* PanelWidget)
{
	//���ᵯ��UI
	if (PopPanelGroup.Num() > 0)
	{
		TArray<USSCPanelWidget*> PopsUIArray;
		PopPanelGroup.GenerateValueArray(PopsUIArray);
		PopsUIArray[PopsUIArray.Num() - 1]->PanelFreeze();
	}
	//��������
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
		//����mask
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

		//��PanelWidget�ӵ�ǰ���ؼ��Ƴ�
		PanelWidget->RemoveFromParent();
		//�����ؼ�
		if (PreWorkLayout->GetChildrenCount() == 0)
		{
			PreWorkLayout->RemoveFromParent();
			ActiveOverlayArray.Remove(PreWorkLayout);
			UnActiveOverlayArray.Push(PreWorkLayout);
		}

		UOverlay* WorkLayout = NULL;

		//������ڲ��ֿؼ�, ��ͼ�����һ�����ֿؼ�ת����Overlay
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
			//��Ӳ��ֿؼ����������
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//��ӵ��������
			ActiveOverlayArray.Push(WorkLayout);
		}

		//�������ֵ���㵯��
		ActiveMask(WorkLayout, PanelWidget->UINature.TransparentType);

		//��ӵ�������ȡ�������Ĳ��ֿؼ�
		UOverlaySlot* PanelSlot = WorkLayout->AddChildToOverlay(PanelWidget);
		PanelSlot->SetPadding(PrePadding);
		PanelSlot->SetHorizontalAlignment(PreHAlign);
		PanelSlot->SetVerticalAlignment(PreVAlign);
		
	}
	//��ӵ���
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
	//��ʾͬһ�㼶Panel
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
	
	//ֻ������һ�����Ǽ���״̬��Ҫ����
	if (PopStack[PopStack.Num() - 1] != PanelWidget) return;
	
	PopPanelGroup.Remove(PanelWidget->GetObjectName());
	PanelWidget->PanelHidden();
	//��������
	PopStack.Pop();
	if (PopStack.Num() > 0)
	{
		USSCPanelWidget* PrePanelWidget = PopStack[PopStack.Num() - 1];
		//ת��
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

	//����������������
	PanelWidget->PanelExit();
}

void USSCRootWidget::ExitPanelHideOther(USSCPanelWidget* PanelWidget)
{
	ShowPanelGroup.Remove(PanelWidget->GetObjectName());
	AllPanelGroup.Remove(PanelWidget->GetObjectName());
	LoadedPanelArray.Remove(PanelWidget->GetObjectName());

	//��ʾͬһ�㼶�µ�����UI���, ����������Level_All�㼶, ��ʾ������ʾ������
	for (TMap<FName, USSCPanelWidget*>::TIterator It(ShowPanelGroup); It; ++It)
		if (PanelWidget->UINature.LayOutLevel == ELayOutLevel::Level_ALL || PanelWidget->UINature.LayOutLevel == It.Value()->UINature.LayOutLevel)
			It.Value()->PanelDisplay();

	//����������������
	PanelWidget->PanelExit();
}

void USSCRootWidget::ExitPanelPopsUp(USSCPanelWidget* PanelWidget)
{

	//��ȡ����ջ������
	TArray<USSCPanelWidget*> PopStack;
	PopPanelGroup.GenerateValueArray(PopStack);

	//����������ϲ�ĵ���, ֱ�ӷ���
	if (PopStack[PopStack.Num() - 1] != PanelWidget)	
		return;
	
	PopPanelGroup.Remove(PanelWidget->GetObjectName());
	AllPanelGroup.Remove(PanelWidget->GetObjectName());
	LoadedPanelArray.Remove(PanelWidget->GetObjectName());
	//���������������ں���
	PanelWidget->PanelExit();

	PopStack.Pop();
	if (PopStack.Num() > 0)
	{
		USSCPanelWidget* PrePanelWidget = PopStack[PopStack.Num() - 1];
		//ת�����ֵ��µ����ĵ�������һ��
		TransferMask(PrePanelWidget);
		//�ظ�����������ĵ���
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
		//�������
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

		//�������
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

		//�������
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
	
	//��ȡ���ֵ�ǰ���ؼ�
	UPanelWidget* MaskParent = Mask->GetParent();
	if (MaskParent)
	{
		//�Ƚϵ�ǰ���ؼ��뽫Ҫ����ĸ��ؼ��Ƿ���ͬ, ��ǰ���ؼ���֮�ؼ�Ϊ1
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
		//�����ִӸ����Ƴ�
		Mask->RemoveFromParent();
	}
	
}

