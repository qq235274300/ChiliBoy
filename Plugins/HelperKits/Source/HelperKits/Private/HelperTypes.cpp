// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperTypes.h"

TSharedPtr<DebugRecord> DebugRecord::RecordInst = nullptr;

TSharedPtr<DebugRecord> DebugRecord::Get()
{
	if (!RecordInst.IsValid())
	{
		RecordInst = MakeShareable(new DebugRecord());
	}
	return RecordInst;
}

void DebugRecord::InitParam(float _showTime, FColor _showColor)
{
	showTime = _showTime;
	showColor = _showColor;
}

void DebugRecord::SetShowPattern(int32 _showPattern)
{
	showPattern = _showPattern;
}
