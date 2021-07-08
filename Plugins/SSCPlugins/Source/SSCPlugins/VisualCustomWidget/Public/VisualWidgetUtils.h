#pragma once
#include "Containers/UnrealString.h"


class VisualWidgetUtils 
{
public:
	//
	static FString GetLimitedTextBlockName(FString InOriginalName, int8 InLimitedCharNum, const FString& InReplaceStr = TEXT("..."));
	static float GetApproxTextLength(FString InText, float CharPerLength = 5);
	
	

};