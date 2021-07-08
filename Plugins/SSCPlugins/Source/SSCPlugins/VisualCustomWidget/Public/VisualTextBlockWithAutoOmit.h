#pragma once

#include "Components/TextBlock.h"
#include "VisualTextBlockWithAutoOmit.generated.h"

UCLASS()
class SSCPLUGINS_API UTextBlockWithAutoOmit : public UTextBlock
{
	GENERATED_BODY()
public:
	virtual void SetText(FText InText)override;
public:
	UPROPERTY(EditAnywhere, Category = "VisualCustomData")
	int32 LimitedCharNum = 8;
	UPROPERTY(EditAnywhere,Category = "VisualCustomData")
	FString LimitedReplacedString = TEXT("...");
};