// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCActor.h"
#include "CoroActor.generated.h"


//struct FDelayNode
//{
//public:
//	bool IsActived;
//	float TimeReming;
//
//	FDelayNode() : IsActived(false),TimeReming(0.f) {}
//	bool Update(float DeltaSeconds, float DelayTime)
//	{
//		if (!IsActived)
//		{
//			TimeReming = DelayTime;
//			IsActived = true;
//			return false;
//		}
//		if (IsActived)
//		{
//			TimeReming -= DeltaSeconds;
//			if (TimeReming <= 0)
//			{
//				IsActived = false;
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		return false;
//	}
//};
//
//struct FCoroTask
//{
//	TArray<FDelayNode*> DelayNodeArray;
//	
//	FCoroTask(int32 TaskNum)
//	{
//		for (int32 i = 0; i <= TaskNum; ++i)
//		{
//			DelayNodeArray.Push(new FDelayNode());
//		}
//	}
//
//	virtual ~FCoroTask()
//	{
//		for (int32 i = 0; i < DelayNodeArray.Num(); ++i)
//		{
//			delete DelayNodeArray[i];
//		}
//	}
//
//	virtual void Work(float DeltaSeconds) {};
//	bool IsFinished()const 
//	{
//		bool flag = true;
//		for (int32 i = 0; i < DelayNodeArray.Num(); ++i)
//		{
//			
//			if (DelayNodeArray[i]->IsActived)
//			{
//				flag = false;
//				break;
//			}
//			
//		}
//		return flag;
//	}
//};



UCLASS()
class SSCPLUGINS_API ACoroActor : public ASSCActor
{
	GENERATED_BODY()
	
public:
	ACoroActor();
	
	virtual void ModelEnable()override;
	virtual void ModelTick(float DeltaSeconds)override;

	//REFOBJFUNC(CallAutoObjFunc);

protected:
	
	FCoroStack* CoroTestThree();
	bool PauseLambda();
	bool PauseFunPtr();
	void TestInvoke();
	
protected:
	TArray<FCoroStack*> CoroTaskGroup;

	bool IsCoroPause;
	int32 TimeCounter;
};
