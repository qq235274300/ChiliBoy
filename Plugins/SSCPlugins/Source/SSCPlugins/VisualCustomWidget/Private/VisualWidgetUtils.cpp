#include "VisualWidgetUtils.h"

FString VisualWidgetUtils::GetLimitedTextBlockName(FString InOriginalName, int8 InLimitedCharNum, const FString & InReplaceStr)
{

	if (!InOriginalName.IsEmpty())
	{
		wchar_t* rawArray = GetData(InOriginalName);
		int32 count = 0;
		for (int32 i = 0; i < InOriginalName.Len(); ++i)
		{
			if (rawArray[i] > 0x80)
			{
				count += 2;
			}
			else
			{
				count++;
			}

			if (count > InLimitedCharNum)
			{
				FString newStr = InOriginalName;
				newStr.RemoveAt(i, newStr.Len() - i);
				newStr += InReplaceStr;
				return newStr;
			}
			
		}

		return InOriginalName;
	}

	return TEXT("");
}

float VisualWidgetUtils::GetApproxTextLength(FString InText, float CharPerLength /*= 5*/)
{
	if (!InText.IsEmpty())
	{
		TCHAR* RawArray = GetData(InText);
		int32 count = 0;
		for (int32 i = 0; i < InText.Len(); ++i)
		{
			if (RawArray[i] > 0x80)
			{
				count += 2;
			}
			else
			{
				count++;
			}
		}

		return count * CharPerLength;
	}
	return .0f;
}
