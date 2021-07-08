// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCMessage.h"
#include "SSCCommon.h"

UBinderEvent::UBinderEvent()
{
	bExecuteWhenPaused = false;
	InputCount = 0;
}

void UBinderEvent::PressEvnt()
{
	InputCount++;
	if (InputCount == TotoalCount)
	{
		if (!bExecuteWhenPaused)
			InputBinderDel.ExecuteIfBound();
		if(bExecuteWhenPaused && !USSCCommon::Get()->IsGamePause())
			InputBinderDel.ExecuteIfBound();
	}
}

void UBinderEvent::ReleasedEvnt()
{
	InputCount--;
}


USSCMessage::USSCMessage()
{
	FuncQuene = new FFuncQuene();
}

void USSCMessage::ModuleInit()
{
	
}

void USSCMessage::ModuleBeginPlay()
{
	PlayerController = USSCCommon::Get()->GetPlayerController();
}

void USSCMessage::ModuleTick(float DeltaSeconds)
{
	TArray<FName> ObjNameArray;
	for (TMap<FName, TMap<FName, FCoroStack*>>::TIterator It(CoroGroup); It; ++It)
	{
		TArray<FName> CoroNameArray;
		for (TMap<FName, FCoroStack*>::TIterator it(It->Value); it; ++it)
		{
			it->Value->Work(DeltaSeconds);
			if (it->Value->IsFinish() || it->Value->isDestroy)
			{
				delete it->Value;
				CoroNameArray.Push(it->Key);
			}
		}
		for (int i = 0; i < CoroNameArray.Num(); ++i)
		{
			It->Value.Remove(CoroNameArray[i]);
			if (It->Value.Num() == 0)
			{
				ObjNameArray.Push(It->Key);
			}
		}
	}
	for (int i = 0; i < ObjNameArray.Num(); ++i)
	{
		CoroGroup.Remove(ObjNameArray[i]);
	}


	//处理延迟节点
	ObjNameArray.Empty();
	for (TMap<FName, TMap<FName, FInvokeTask*>>::TIterator It(InvokeGroup); It; ++It)
	{
		TArray<FName> InvokeNameArray;
		for (TMap<FName, FInvokeTask*>::TIterator it(It->Value); it; ++it)
		{
			if (it->Value->UpdateOperate(DeltaSeconds) || it->Value->isDestroy)
			{
				delete it->Value;
				InvokeNameArray.Push(it->Key);
			}
		}

		for (int i = 0; i < InvokeNameArray.Num(); ++i)
		{
			It->Value.Remove(InvokeNameArray[i]);
		}
		if (It->Value.Num() == 0)
		{
			ObjNameArray.Push(It->Key);
		}
	}

	for (int i = 0; i < ObjNameArray.Num(); ++i)
	{
		InvokeGroup.Remove(ObjNameArray[i]);
	}
}


bool USSCMessage::StartCoroutine(FName ObjName, FName CoroName, FCoroStack* CoroTask)
{
	if (!CoroGroup.Contains(ObjName))
	{
		TMap<FName, FCoroStack*> Corotask;
		CoroGroup.Add(ObjName, Corotask);
		
	}
	if (!CoroGroup.Find(ObjName)->Contains(CoroName))
	{
		CoroGroup.Find(ObjName)->Add(CoroName, CoroTask);
		return true;
	}
	delete CoroTask;
	return false;
}


bool USSCMessage::StopCoroutine(FName ObjName, FName CoroName)
{
	if (CoroGroup.Contains(ObjName) && CoroGroup.Find(ObjName)->Contains(CoroName))
	{
		 (*(CoroGroup.Find(ObjName)->Find(CoroName)))->isDestroy = true;
		return true;
	}
	return false;
}

void USSCMessage::StopAllCoroutine(FName ObjName)
{
	if (CoroGroup.Contains(ObjName))
	{
		for (TMap<FName, FCoroStack*>::TIterator it(*CoroGroup.Find(ObjName)); it; ++it)
		{
			  it->Value->isDestroy = true;
		}
		
	}
}

bool USSCMessage::StartInvoke(FName ObjName, FName InvokeName, FInvokeTask* InvokeTask)
{
	if (!InvokeGroup.Contains(ObjName))
	{
		TMap<FName, FInvokeTask*>Invoketask;
		InvokeGroup.Add(ObjName, Invoketask);

	}
	if (!InvokeGroup.Find(ObjName)->Contains(InvokeName))
	{
		InvokeGroup.Find(ObjName)->Add(InvokeName, InvokeTask);
		return true;
	}
	delete InvokeTask;
	return false;
}

bool USSCMessage::StopInvoke(FName ObjName, FName InvokeName)
{
	if (InvokeGroup.Contains(ObjName) && InvokeGroup.Find(ObjName)->Contains(InvokeName))
	{

		(*(InvokeGroup.Find(ObjName)->Find(InvokeName)))->isDestroy = true;
		return true;
	}
	return false;
}

void USSCMessage::StopAllInvoke(FName ObjName)
{
	if (InvokeGroup.Contains(ObjName))
	{
		for (TMap<FName, FInvokeTask*>::TIterator it(*InvokeGroup.Find(ObjName)); it; ++it)
		{
			 it->Value->isDestroy = true;
			
		}
		
	}

}
void USSCMessage::UnBindKeys(FName ObjName)
{
	if (InputBinderGroup.Contains(ObjName))
	{
		TArray<UBinderEvent*> Binders = *InputBinderGroup.Find(ObjName);
		for (int i = 0; i < Binders.Num(); ++i)
		{
			Binders[i]->RemoveFromRoot();
			Binders[i]->ConditionalBeginDestroy();
		}
		InputBinderGroup.Remove(ObjName);
	}
}
