// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor02.h"

void ATestActor02::ModelInit()
{
	Super::ModelInit();
//	SSCHelper::Debug() << "Init" << SSCHelper::Endl();
	bIsAllowTick = true;
}

void ATestActor02::ModelLoading()
{
	Super::ModelLoading();
	//SSCHelper::Debug() << "Loading" << SSCHelper::Endl();
}

void ATestActor02::ModelRegsiter()
{
	Super::ModelRegsiter();
	//SSCHelper::Debug() << "Register" << SSCHelper::Endl();

	FuncHandle = RegisterFuncHandle<int32, FString>((int32)ESSCGame::HUD, "CallOne", [this](FString Info)
	{
		return CallOneFunc(Info);
	});
}

void ATestActor02::ModelEnable()
{
	Super::ModelEnable();
	
	//SSCHelper::Debug() << "Enable" << SSCHelper::Endl();	

}

void ATestActor02::ModelTick(float DeltaSeconds)
{
	Super::ModelTick(DeltaSeconds);
	Timer++;
	
	if (Timer == 300)
	{
		//FuncHandle.UnRegister();
	}


	
}

void ATestActor02::ModelDisable()
{
	Super::ModelDisable();
	//SSCHelper::Debug() << "ModelDisable" << SSCHelper::Endl();
}

void ATestActor02::ModelUnRegister()
{
	Super::ModelUnRegister();
	//SSCHelper::Debug() << "ModelUnRegister" << SSCHelper::Endl();
}

void ATestActor02::ModelUnLoading()
{
	Super::ModelUnLoading();
	//SSCHelper::Debug() << "ModelUnLoading" << SSCHelper::Endl();
}

void ATestActor02::ModelRelease()
{
	Super::ModelRelease();
	//SSCHelper::Debug() << "ModelRelease" << SSCHelper::Endl();
}

void ATestActor02::RefCallFunc(FString Info)
{
	SSCHelper::Debug() << GetObjectName() << "--->" << Info <<SSCHelper::Endl();
}

int32 ATestActor02::CallOneFunc(FString Info)
{
	SSCHelper::Debug() << Info << SSCHelper::Endl();
	return 69;
}

void ATestActor02::AcceptCall(FString InfoStr)
{
	SSCHelper::Debug() << InfoStr << SSCHelper::Endl();
}

int32 ATestActor02::WealthCall(int32 Counter, FString InfoStr, bool InFlag)
{
	return 66666;
}


