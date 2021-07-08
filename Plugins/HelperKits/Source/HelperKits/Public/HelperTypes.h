// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#pragma region DebugHelper

class HELPERKITS_API DebugRecord
{
private:
	static TSharedPtr<DebugRecord> RecordInst;
public:
	inline DebugRecord() {};
	~DebugRecord() {};
	static TSharedPtr<DebugRecord> Get();
public:
	void InitParam(float _showTime, FColor _showColor);
	void SetShowPattern(int32 _showPattern);
	inline void OutPut()
	{
		switch (showPattern)
		{
		case 0:
		{
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, showTime, showColor, showInfo);
			}
		}
		break;
		case 1:
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *showInfo);
		}
		break;
		case 2:
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *showInfo);
		}
		break;
		case 3:
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *showInfo);
		}
		break;
		}
		showInfo.Empty();
	}
	inline DebugRecord& operator<<(FString Info) { showInfo.Append(Info); return *this; }
	inline DebugRecord& operator<<(FName Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FText Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(const char* Info) { showInfo += Info; return *this; }
	inline DebugRecord& operator<<(const char Info) { showInfo.AppendChar(Info); return *this; }
	inline DebugRecord& operator<<(int32 Info) { showInfo.Append(FString::FromInt(Info)); return *this; }
	inline DebugRecord& operator<<(float Info) { showInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline DebugRecord& operator<<(double Info) { showInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline DebugRecord& operator<<(bool Info) { showInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline DebugRecord& operator<<(FVector2D Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FVector Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FRotator Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FQuat Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FTransform Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FMatrix Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FColor Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FLinearColor Info) { showInfo.Append(Info.ToString()); return *this; }
	inline DebugRecord& operator<<(FMargin Info) { showInfo.Append((FString::SanitizeFloat(Info.Left) + FString(" , ") + FString::SanitizeFloat(Info.Top) + FString(" , ") + FString::SanitizeFloat(Info.Right) + FString(" , ") + FString::SanitizeFloat(Info.Bottom))); return *this; }
	inline DebugRecord& operator<<(DebugRecord& _RecordInst) { _RecordInst.OutPut(); return *this; }
private:
	FString showInfo;
	float showTime = 0.f;
	FColor showColor = FColor::Yellow;
	uint8 showPattern = 0;  // 0 Debug 1 Log 2 Warning 3 Error
};

#pragma endregion
