// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor01.h"

void ATestActor01::ModelInit()
{
	Super::ModelInit();
//	SSCHelper::Debug() << "Init" << SSCHelper::Endl();
	bIsAllowTick = true;
}

void ATestActor01::ModelLoading()
{
	Super::ModelLoading();
	//SSCHelper::Debug() << "Loading" << SSCHelper::Endl();
}

void ATestActor01::ModelRegsiter()
{
	Super::ModelRegsiter();
	//SSCHelper::Debug() << "Register" << SSCHelper::Endl();


	CallHandle = RegisterCallHandle<int32,FString>("CallOne");
}

void ATestActor01::ModelEnable()
{
	Super::ModelEnable();
	
	//SSCHelper::Debug() << "Enable" << SSCHelper::Endl();	
	RegisterTFunc<void, FString>([this](FString InfoStr) {AcceptCall(InfoStr); });
	TFuncArray[0]->Execute<void, FString>(FString("Happy New Year"));
}

void ATestActor01::ModelTick(float DeltaSeconds)
{
	Super::ModelTick(DeltaSeconds);
	Timer++;
	CallHandle.Execute(FString::FromInt(Timer));

	if (Timer >= 490)
	{
		CallHandle.UnRegister();
	}
	/*if (Timer < 3)
	{

	}
	if (Timer == 3)
	{
		DestroySelf();
	}*/


	
}

void ATestActor01::ModelDisable()
{
	Super::ModelDisable();
	//SSCHelper::Debug() << "ModelDisable" << SSCHelper::Endl();
}

void ATestActor01::ModelUnRegister()
{
	Super::ModelUnRegister();
	//SSCHelper::Debug() << "ModelUnRegister" << SSCHelper::Endl();
}

void ATestActor01::ModelUnLoading()
{
	Super::ModelUnLoading();
	//SSCHelper::Debug() << "ModelUnLoading" << SSCHelper::Endl();
}

void ATestActor01::ModelRelease()
{
	Super::ModelRelease();
	//SSCHelper::Debug() << "ModelRelease" << SSCHelper::Endl();
}

void ATestActor01::RefCallFunc(FString Info)
{
	SSCHelper::Debug() << GetObjectName() << "--->" << Info <<SSCHelper::Endl();
}

void ATestActor01::AcceptCall(FString InfoStr)
{
	SSCHelper::Debug() << InfoStr << SSCHelper::Endl();
}

int32 ATestActor01::WealthCall(int32 Counter, FString InfoStr, bool InFlag)
{
	return 66666;
}


