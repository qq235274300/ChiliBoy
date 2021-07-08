// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCActor.h"
#include "TestActor01.generated.h"

/**
 * 
 */
/**************************************/
/*******Any Element Struct*************/
/**************************************/



UCLASS()
class SSCPLUGINS_API ATestActor01 : public ASSCActor
{
	GENERATED_BODY()
public:
	virtual void ModelInit()override;
	virtual void ModelLoading()override;
	virtual void ModelRegsiter()override;
	virtual void ModelEnable()override;

	virtual void ModelTick(float DeltaSeconds)override;

	virtual void ModelDisable()override;
	virtual void ModelUnRegister()override;
	virtual void ModelUnLoading()override;
	virtual void ModelRelease()override;
	 
public:
	/*************Test*****************/
	UFUNCTION()
		void RefCallFunc(FString Info);

	
	FFuncCallHandle<int32,FString> CallHandle;

	/*************Test Register Func*****************/
	UFUNCTION()
		void AcceptCall(FString InfoStr);
	UFUNCTION()
		int32 WealthCall(int32 Counter,FString InfoStr, bool InFlag);
	
	template<typename RetType,typename... VarTypes>
	void RegisterTFunc(TFunction<RetType(VarTypes...)> InFunc);

protected:
	TArray<FAnyFunc*> TFuncArray;



protected:
	int32 Timer = 0;
};

template<typename RetType, typename... VarTypes>
void ATestActor01::RegisterTFunc(TFunction<RetType(VarTypes...)> InFunc)
{
	TFuncArray.Push(new FAnyFunc(InFunc));
}


