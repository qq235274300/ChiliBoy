#include "VisualTextBlockWithCountDown.h"
#include "TimerManager.h"

void UTextBlockWithCountDown::SetTime(FTimespan InTime)
{
	_Time = InTime;
	if (!CountDownHandle.IsValid() && _Time.GetTotalSeconds() > 1)
	{
		GetWorld()->GetTimerManager().SetTimer(CountDownHandle, this, &UTextBlockWithCountDown::CountDownTickFunc, 1, true);
	}
}

void UTextBlockWithCountDown::CountDownTickFunc()
{
	_Time -= FTimespan(ETimespan::TicksPerSecond);
	SetText(GetTimeText(_Time));
	
	if (_Time.GetTicks() <= 0)
	{
		CountDownDelegate.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(CountDownHandle);
	}
	
}

FText UTextBlockWithCountDown::GetTimeText(FTimespan InTime)
{
	FString TimeString = InTime.ToString(TEXT("%h:%m:%s"));
	TimeString.RemoveFromStart(L"+");
	return FText::FromString(TimeString);
}
