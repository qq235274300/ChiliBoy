// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCTypes.h"



TSharedPtr<SSCRecord> SSCRecord::RecordInst = nullptr;

TSharedPtr<SSCRecord> SSCRecord::Get()
{
	if (!RecordInst.IsValid())
		RecordInst = MakeShareable(new SSCRecord());

	return RecordInst;
}

void SSCRecord::InitParam(float _showTime, FColor _showColor)
{
	showTime = _showTime;
	showColor = _showColor;
}

void SSCRecord::SetShowPattern(int32 _showPattern)
{
	showPattern = _showPattern;
}

