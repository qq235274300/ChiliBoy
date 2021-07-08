// Fill out your copyright notice in the Description page of Project Settings.


#include "CoroActor.h"

ACoroActor::ACoroActor()
{
	bIsAllowTick = true;
}

void ACoroActor::ModelEnable()
{
	Super::ModelEnable();
	IsCoroPause = true;
	//StartInvokeRepeated("InvokeTest",5.f,1.f,this,&ACoroActor::TestInvoke);
	//StartCoroutine("CoroTestThree", CoroTestThree());
	//BindKey(EKeys::F, EInputEvent::IE_Pressed, this, &ACoroActor::TestInvoke);
	//BindKeys(this,&ACoroActor::TestInvoke,EKeys::F,EKeys::G);
	
	//CallAutoObjFunc(int32(ESSCGame::HUD), "AutoTestObj", "TestObj");
	//CallAutoObjFunc(int32(ESSCGame::HUD), "AutoTestActor", "TestActor");
	//CallAutoObjFunc(int32(ESSCGame::HUD), "AutoTestWidget", "TestWidget");
}

void ACoroActor::ModelTick(float DeltaSeconds)
{
	Super::ModelTick(DeltaSeconds);

	/*TArray<FCoroStack*> TempTask;

	for (int i = 0; i < CoroTaskGroup.Num(); ++i)
	{
		CoroTaskGroup[i]->Work(DeltaSeconds);
		if (CoroTaskGroup[i]->IsFinish())
			TempTask.Push(CoroTaskGroup[i]);
	}
	for (int i = 0; i < TempTask.Num(); ++i)
	{
		CoroTaskGroup.Remove(TempTask[i]);
		delete TempTask[i];
	}


	TimeCounter++;
	if (TimeCounter == 500)
		IsCoroPause = false;*/
	
}



FCoroStack* ACoroActor::CoroTestThree()
{
	SSCCORO_PARAM(ACoroActor);
	int32 i;
	int32 j;

#include SSCCORO_BEGIN()
	SSCHelper::Debug() << 0 << SSCHelper::Endl();



#include SSCYIELD_READY()
	SSCYIELD_RETURN_LAMB(D->PauseLambda(););
	SSCHelper::Debug() << 2 << SSCHelper::Endl();
//
//#include SSCYIELD_READY()
//	SSCYIELD_RETURN_FUNC(D, &ACoroActor::PauseFunPtr);
//	SSCHelper::Debug() << 3 << SSCHelper::Endl();


	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 5; j++)
		{
#include SSCYIELD_READY()
			SSCYIELD_RETURN_TICK(20);

			SSCHelper::Debug() << i << j << SSCHelper::Endl();

			if (i * 10 + j > 30)
			{
#include SSCYIELD_READY()
				SSCYIELD_RETURN_STOP();
			}

		}
	}
#include SSCYIELD_READY()
	SSCYIELD_RETURN_SECOND(5.f);

	SSCHelper::Debug() << 4 << SSCHelper::Endl();

#include SSCCORO_END()
}

bool ACoroActor::PauseLambda()
{
	static int32 LambdaTime = 0;
	LambdaTime++;
	if (LambdaTime == 10)
		return false;
	return true;
}

bool ACoroActor::PauseFunPtr()
{
	static int32 FunPtrTime = 0;
	FunPtrTime++;
	if (FunPtrTime == 300)
		return false;
	return true;
}

void ACoroActor::TestInvoke()
{
	SSCHelper::Debug() << "U Are Gay " << SSCHelper::Endl();
}

