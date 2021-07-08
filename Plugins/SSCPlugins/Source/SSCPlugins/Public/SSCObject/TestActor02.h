// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCActor.h"
#include "TestActor02.generated.h"

/**
 * 
 */
/**************************************/
/*******Any Element Struct*************/
/**************************************/



UCLASS()
class SSCPLUGINS_API ATestActor02 : public ASSCActor
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


	/*************RegisterFunc*****************/
	FFuncHandle FuncHandle;
	UFUNCTION()
		int32 CallOneFunc(FString Info);

	/*************Test Register Func*****************/
	UFUNCTION()
		void AcceptCall(FString InfoStr);
	UFUNCTION()
		int32 WealthCall(int32 Counter,FString InfoStr, bool InFlag);
	
	

protected:
	TArray<FAnyFunc*> TFuncArray;



protected:
	int32 Timer = 0;
};



