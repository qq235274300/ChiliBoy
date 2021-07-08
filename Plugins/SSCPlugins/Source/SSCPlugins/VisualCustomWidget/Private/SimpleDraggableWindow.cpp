
#include "SimpleDraggableWindow.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "SSCCommon.h"

USimpleDraggableWindow::USimpleDraggableWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
	ResizeMinWidth = ReszieMinHeight = 0.f;
	ResizeMaxWidth = ResizeMaxHeight = 400.f;
	DragKey = FKey(FName("LeftMouseButton"));
	bEnableDrag = true;
	bEnableResize = false;
	bIsMouseButtonDown = bIsDragging = bIsResizing = bStartInCenterScreen = false;
	LastMousePos =  FVector2D::ZeroVector;

	CurrentZOrder = -1;
	bIsFocusable = true;

	
}

void USimpleDraggableWindow::NativeConstruct()
{
	ParentSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (ParentSlot == nullptr)
	{
		if (Slot)
		{
			SSCHelper::Debug() << "Parent is Not CanvelPanel" << SSCHelper::Endl();	
		}
		else
		{
			SSCHelper::Debug() << "Need Parent WidgetCom" << SSCHelper::Endl();
		}
	}
	else
	{
		bool ConstructSuccess = true;
		if (!bEnableResize)
		{
			ResizeBorder->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (bEnableResize)
		{
			ResizeBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		if (StartSize != FVector2D::ZeroVector)
		{
			ParentSlot->SetSize(StartSize);
		}
		if (bStartInCenterScreen)
		{
			CenterWindowToScreen();
		}
		//Bind 
		if (TitleBorder)
		{
			TitleBorder->OnMouseButtonUpEvent.BindUFunction(this,FName("OnTitleBorderMouseUpEvnt"));
			TitleBorder->OnMouseButtonDownEvent.BindUFunction(this, FName("OnTitleBorderMouseDownEvnt"));
		}
		else
		{
			SSCHelper::Debug() << "No TitleBorder Find" << SSCHelper::Endl();
			ConstructSuccess = false;
		}
		
		if (bEnableResize)
		{
			if (!ResizeBorder)
			{
				SSCHelper::Debug() << "No ResizeBorder Find" << SSCHelper::Endl();
				ConstructSuccess = false;
			}
			else
			{
				ResizeBorder->OnMouseButtonDownEvent.BindUFunction(this,FName("OnReszieBorderMouseDownEvnt"));
			}
		}

		if(!ConstructSuccess)
		{
			SSCHelper::Debug() << GetName() << "----->Widget----->" << "Construct Errors" << SSCHelper::Endl();
		}
	}

	Super::NativeConstruct();
}

FReply USimpleDraggableWindow::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	if (bIsMouseButtonDown && ParentSlot)
	{
		FVector2D OutPixelPos, OutViewPortPos;
		USlateBlueprintLibrary::AbsoluteToViewport(this, InMouseEvent.GetScreenSpacePosition(), OutPixelPos, OutViewPortPos);
		const FVector2D CurrentViewPortSize = UWidgetLayoutLibrary::GetViewportSize(this);
		const bool bIsMouseOffScreen = OutPixelPos.X<= Boundary.X || OutPixelPos.Y <= Boundary.Y || OutPixelPos.X>= (CurrentViewPortSize.X - Boundary.X) || OutPixelPos.Y >= (CurrentViewPortSize.Y - Boundary.Y);
		if (bIsMouseOffScreen)
		{
			OnMouseButtonUpEvnt();
			return FReply::Handled();
		}

		USlateBlueprintLibrary::AbsoluteToViewport(this, InMouseEvent.GetScreenSpacePosition(), OutPixelPos, OutViewPortPos);
		FVector2D MouseDelta = OutViewPortPos - LastMousePos;
		FEventReply EvntReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey);
		if (bIsDragging)
		{
			ParentSlot->SetPosition(ParentSlot->GetPosition() + MouseDelta);
		}
		else if (bIsResizing)
		{
			if (bIsAlignmentAccounted)
			{
				const FVector2D NewSize = DetermineNewSize(MouseDelta);
				ParentSlot->SetSize(NewSize);
			}
			else
			{
				ParentSlot->SetAlignment(FVector2D::ZeroVector);
				ParentSlot->SetPosition(ParentSlot->GetPosition() - PreResizeOffset);
				bIsAlignmentAccounted = true;
				return FReply::Handled();
			}
		}
		else
		{
			return UWidgetBlueprintLibrary::CaptureMouse(EvntReply, this).NativeReply;
		}
		
		USlateBlueprintLibrary::AbsoluteToViewport(this, InMouseEvent.GetScreenSpacePosition(), OutPixelPos, LastMousePos);
		return UWidgetBlueprintLibrary::CaptureMouse(EvntReply, this).NativeReply;
		
	}
	
	return FReply::Handled();
}

FReply USimpleDraggableWindow::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	OnMouseButtonUpEvnt();
	FEventReply EvntReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey);
	return UWidgetBlueprintLibrary::ReleaseMouseCapture(EvntReply).NativeReply;
}



USimpleDraggableWindow* USimpleDraggableWindow::CreateDraggleWindow(const UObject* WorldContextObject, 
	TSubclassOf<USimpleDraggableWindow> DraggableWigetClass, TSubclassOf<UUserWidget> ChildWidgetClass, const FVector2D StartSize /*= FVector2D(800.f,600.f)*/, const bool canDrag /*= true*/, const bool canReszie /*= true*/, const bool CenterToScreen /*= true*/, int32 PlayerIndex /*= 0*/)
{
	if (DraggableWigetClass)
	{
		APlayerController* CurrentController = UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex);
		
		USimpleDraggableWindow* DraggableWindow = Cast<USimpleDraggableWindow>(CreateWidget(CurrentController, DraggableWigetClass));
		if (DraggableWindow)
		{
			DraggableWindow->StartSize = StartSize;
			DraggableWindow->bEnableDrag = canDrag;
			DraggableWindow->bEnableResize = canReszie;
			DraggableWindow->bStartInCenterScreen = CenterToScreen;

			return DraggableWindow;
		}
		else
		{
			SSCHelper::Debug() << "-->  Specify Wrong DraggleWidgetClass" << SSCHelper::Endl();
			return nullptr;
		}
	}
	else
	{
		SSCHelper::Debug() << "--> No Specify DraggleWidgetClass" << SSCHelper::Endl();
		return nullptr;
	}

	return nullptr;
}

void USimpleDraggableWindow::CenterWindowToScreen()
{
	ParentSlot->SetAnchors(FAnchors(0.5));
	ParentSlot->SetAlignment(FVector2D(0.5));
	ParentSlot->SetPosition(FVector2D::ZeroVector);
}

void USimpleDraggableWindow::AddContentWidgetClass(TSubclassOf<UUserWidget> CreateWidgetClass, const bool bClearPrevious /*= true*/)
{
	if (CreateWidgetClass)
	{
		APlayerController* CurrentController = UGameplayStatics::GetPlayerController(this, 0);
		UUserWidget* TmpWidget = CreateWidget(CurrentController, CreateWidgetClass);
		AddContentWidget(TmpWidget, bClearPrevious);
	}
	else
	{
		SSCHelper::Debug() << "No Widget Class Specify" << SSCHelper::Endl();
	}
}

void USimpleDraggableWindow::AddContentWidget(UUserWidget* CreateWidget, const bool bClearPrevious /*= true*/)
{
	if (bClearPrevious)
	{
		ChildPanel->ClearChildren();
	}	
	ChildPanel->AddChildToCanvas(CreateWidget);
		
	OnAddContentWidgetEvnt(CreateWidget);
}

void USimpleDraggableWindow::SetTitleEvnt()
{	
	if (Title_Text)
	{
		Title_Text->SetText(FText::FromString(Title));
	}
	
}

void USimpleDraggableWindow::OnCloseEvnt_Implementation()
{
	RemoveFromParent();

}

void USimpleDraggableWindow::OnMouseButtonUpEvnt()
{
	if (bIsResizing && ParentSlot && bIsAlignmentAccounted)
	{
		const FVector2D SizeDiff = ParentSlot->GetSize() - PreDragSize;
		const FVector2D NewPos = (ParentSlot->GetPosition()) +(SizeDiff* PreResizeAlignment) + PreResizeOffset;
		ParentSlot->SetPosition(NewPos);
		ParentSlot->SetAlignment(PreResizeAlignment);
	}

	bIsAlignmentAccounted = false;
	bIsMouseButtonDown = false;
	bIsDragging = false;
	bIsResizing = false;
}

const FVector2D USimpleDraggableWindow::DetermineNewSize(const FVector2D& Delta) const
{
	if (ParentSlot)
	{
		const FVector2D CurSize = ParentSlot->GetSize();
		const float Size_X = CurSize.X;
		const float Size_Y = CurSize.Y;
		const float Delta_X = Delta.X;
		const float Delta_Y = Delta.Y;

		float tmpWidth = 0.f;
		float tmpHeight = 0.f;

		if (ResizeMaxWidth > 0.f)
		{
			const float CurWidth = Size_X + Delta_X;
			tmpWidth = FMath::Clamp(CurWidth, ResizeMinWidth, ResizeMaxWidth);
		}
		else
		{
			tmpWidth = FMath::Max<float>((Size_X + Delta_X), ResizeMinWidth);
		}

		if (ResizeMaxHeight > 0.f)
		{
			const float CurHeight = Size_Y + Delta_Y;
			tmpHeight = FMath::Clamp(CurHeight, ReszieMinHeight, ResizeMaxHeight);
		}
		else
		{
			tmpHeight = FMath::Max<float>((Size_Y + Delta_Y), ReszieMinHeight);
		}

		return FVector2D(tmpWidth, tmpHeight);

	}

	return FVector2D::ZeroVector;
}

FEventReply USimpleDraggableWindow::OnTitleBorderMouseUpEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply EvntReply = FEventReply();
	EvntReply.NativeReply = NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	return EvntReply;
}

FEventReply USimpleDraggableWindow::OnTitleBorderMouseDownEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bEnableDrag)
	{
		OnTitleBorderMouseUpEvnt(InGeometry, InMouseEvent);
		bIsMouseButtonDown = true;
		bIsDragging = true;

		FVector2D OutPixelPos;
		USlateBlueprintLibrary::AbsoluteToViewport(this, InMouseEvent.GetScreenSpacePosition(), OutPixelPos, LastMousePos);
		FEventReply EvntReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey);
		OnDragStart(InMouseEvent);
		return UWidgetBlueprintLibrary::CaptureMouse(EvntReply, this);
		
	}
	return FEventReply();
}

FEventReply USimpleDraggableWindow::OnReszieBorderMouseDownEvnt(FGeometry InGeometry, const FPointerEvent& InMouseEvent)
{
	bIsMouseButtonDown = true;
	bIsResizing = true;
	FEventReply EvntReply = FEventReply();
	if (ParentSlot)
	{
		FVector2D OutPixelPos;
		USlateBlueprintLibrary::AbsoluteToViewport(this, InMouseEvent.GetScreenSpacePosition(), OutPixelPos, LastMousePos);
		PreResizeAlignment = ParentSlot->GetAlignment();
		PreDragSize = ParentSlot->GetSize();
		PreResizeOffset = PreDragSize * PreResizeAlignment;
		
		EvntReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey);
		OnResizeStart(InMouseEvent);
	}

	return UWidgetBlueprintLibrary::CaptureMouse(EvntReply, this);
}
