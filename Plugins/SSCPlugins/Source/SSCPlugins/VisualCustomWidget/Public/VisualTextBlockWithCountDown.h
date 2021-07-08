#pragma once
#include "Components/TextBlock.h"
#include "VisualTextBlockWithCountDown.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCountDownFinshDelegate);

UCLASS()
class SSCPLUGINS_API UTextBlockWithCountDown : public UTextBlock
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Widget", meta = (DisplayName = "SetTime (Timer)"))
	void SetTime(FTimespan InTime);

	template<class UserClass>
	FORCEINLINE void AddFinishDelegate(UserClass* InObj, TFunction<void(void)>&& CallBack)
	{
		CountDownDelegate.AddDynamic(InObj, CallBack);
	}


	FORCEINLINE void ClearCountDelegate()
	{	
		CountDownDelegate.Clear();
	}
private:
	void CountDownTickFunc();
	FText GetTimeText(FTimespan InTime);
	

private:
	FTimerHandle CountDownHandle;
	UPROPERTY(BlueprintAssignable,Category = "VisualCustomData")
	FCountDownFinshDelegate CountDownDelegate;
	FTimespan _Time;

};