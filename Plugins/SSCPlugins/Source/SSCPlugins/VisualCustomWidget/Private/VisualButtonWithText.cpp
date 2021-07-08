#include "VisualButtonWithText.h"
#include "VisualWidgetUtils.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


//ÉùÒô 

bool UButtonWithTextWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	return true;
}

void UButtonWithTextWidget::BeginDestroy()
{
	OnClickButtonTextWithInt32Delegate.Clear();
	OnClickButtonTextWithStrDelegate.Clear();
	Super::BeginDestroy();
}

void UButtonWithTextWidget::Show()
{
	
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UButtonWithTextWidget::Hide()
{
	OnClickButtonTextWithInt32Delegate.Clear();
	OnClickButtonTextWithStrDelegate.Clear();
}

bool UButtonWithTextWidget::IsShowing()
{
	return GetVisibility() != ESlateVisibility::Collapsed && GetVisibility() != ESlateVisibility::Hidden;
	
}

void UButtonWithTextWidget::Init()
{
	if (!HasInit)
	{
		btn->OnClicked.AddDynamic(this, &UButtonWithTextWidget::OnClick_Bt);
		
		HasInit = true;
	}
	if (bLimitedCharNum)
	{
		btn->SetToolTipText(FText::FromString(Data.str));
		text->SetText(FText::FromString(VisualWidgetUtils::GetLimitedTextBlockName(Data.str, LimitedNameCharNum, LimitedNameReplacedString)));
	}
	else
	{
		text->SetText(FText::FromString(Data.str));
	}
	if (bIsColorStyle)
	{
		ChangeTextColor(BtnState);
	}
	else
	{
		ChangeBtnStyle(BtnState);
	}
}

void UButtonWithTextWidget::OnClick_Bt()
{
	if (!BtnState)
	{
		OnClickButtonTextWithInt32Delegate.Broadcast(Data.num);
		OnClickButtonTextWithStrDelegate.Broadcast(Data.str);
		if (bIsColorStyle)
		{
			ChangeTextColor(true);
		}
		else
		{
			ChangeBtnStyle(true);
		}
		BtnState = true;
	}

}

void UButtonWithTextWidget::Reset()
{
	BtnState = false;
	if (bIsColorStyle)
	{
		ChangeTextColor(false);
	}
	else
	{
		ChangeBtnStyle(false);
	}
	
	
}

void UButtonWithTextWidget::ForceToChangeState(bool _isChecked, bool _executeEvent /*= false*/)
{
	if (bIsColorStyle)
	{
		ChangeTextColor(_isChecked);

	}
	else
	{
		ChangeBtnStyle(_isChecked);
	}

	if (_executeEvent)
	{
		OnClickButtonTextWithInt32Delegate.Broadcast(Data.num);
		OnClickButtonTextWithStrDelegate.Broadcast(Data.str);
	}
}

void UButtonWithTextWidget::SetCheckedTextColor(FVector4 _color)
{
	CheckedTextColor = FSlateColor(FLinearColor(_color.X, _color.Y, _color.Z, _color.W));
}

void UButtonWithTextWidget::SetUncheckedTextColor(FVector4 _color)
{
	UnCheckedTextColor = FSlateColor(FLinearColor(_color.X, _color.Y, _color.Z, _color.W));
}

void UButtonWithTextWidget::SetBtnCheckedStyle()
{
	btn->SetStyle(BtnCheckedStyle);
}

void UButtonWithTextWidget::SetBtnUnCheckedStyle()
{
	btn->SetStyle(BtnUnCheckedStyle);
}


void UButtonWithTextWidget::ChangeTextColor(bool _isChecked)
{
	text->SetColorAndOpacity(_isChecked ? CheckedTextColor : UnCheckedTextColor);
}

void UButtonWithTextWidget::ChangeBtnStyle(bool _isChecked)
{
	btn->SetStyle(_isChecked? BtnCheckedStyle : BtnUnCheckedStyle);
	
}
