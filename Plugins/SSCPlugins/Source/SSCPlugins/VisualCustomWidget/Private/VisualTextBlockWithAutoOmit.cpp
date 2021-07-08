#include "VisualTextBlockWithAutoOmit.h"
#include "VisualWidgetUtils.h"

void UTextBlockWithAutoOmit::SetText(FText InText)
{
	FText displayText = FText::FromString(VisualWidgetUtils::GetLimitedTextBlockName(InText.ToString(), LimitedCharNum, LimitedReplacedString));
	Super::SetText(displayText);
	SetToolTipText(InText);
}
