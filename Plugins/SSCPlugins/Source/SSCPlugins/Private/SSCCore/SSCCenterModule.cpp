// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCCenterModule.h"
#include "SSCObjectInterface.h"

void USSCCenterModule::IterGetModuleChildren(USSCModule* _Module, FName ModuleName)
{
	if (!_Module) return;
	_Module->GetModuleIndex(ModuleName);
	for (int i = 0; i < _Module->GetAttachChildren().Num(); ++i)
	{
		USSCModule* tmp = Cast<USSCModule>(_Module->GetAttachChildren()[i]);
		if (tmp)
		{
			_Module->ChildrenModules.Push(tmp);
			IterGetModuleChildren(tmp, ModuleName);
		}
	}
}

void USSCCenterModule::IterCreateSubModule(USSCModule* _Module)
{
	_Module->CreateSubModule();
	for (int i = 0; i < _Module->ChildrenModules.Num(); ++i)
	{
		IterCreateSubModule(_Module->ChildrenModules[i]);
	}
}

void USSCCenterModule::IterModuleInit(USSCModule* _Module)
{
	_Module->ModuleInit();
	for (int i = 0; i < _Module->ChildrenModules.Num(); ++i)
	{	
		IterModuleInit(_Module->ChildrenModules[i]);
	}
}

void USSCCenterModule::IterModuleBeginPlay(USSCModule* _Module)
{
	_Module->ModuleBeginPlay();
	for (int i = 0; i < _Module->ChildrenModules.Num(); ++i)
	{	
		IterModuleBeginPlay(_Module->ChildrenModules[i]);
	}
}

void USSCCenterModule::IterModuleTick(USSCModule* _Module, float DeltaSeconds)
{
	_Module->ModuleTick(DeltaSeconds);
	for (int i = 0; i < _Module->ChildrenModules.Num(); ++i)
	{
		IterModuleTick(_Module->ChildrenModules[i], DeltaSeconds);
	}
}


void USSCCenterModule::GatherModule(FName ModuleType)
{
	if (ModuleType.IsNone()) return;
	TArray<USSCModule*> ModuleArray;
	IterGatherModule(this, ModuleArray);
	int32 ModuleNum =(int32)FindObject<UEnum>(ANY_PACKAGE,*ModuleType.ToString(), true)->GetMaxEnumValue();
	if (ModuleNum <= 0) return;
	
	for (int i = 0; i < ModuleNum; ++i)
		ModuleGroup.Push(NULL);
	for (int i = 0; i < ModuleArray.Num(); ++i)
	{
		ModuleGroup[ModuleArray[i]->ModuleIndex] = ModuleArray[i];
	}
	
}


void USSCCenterModule::IterGatherModule(USSCModule* Module, TArray<USSCModule*>& GatherGroup)
{
	GatherGroup.Push(Module);
	for (int i = 0; i < Module->ChildrenModules.Num(); ++i)
	{
		IterGatherModule(Module->ChildrenModules[i], GatherGroup);
	}
}


bool USSCCenterModule::RegisterObject(ISSCObjectInterface* InObject)
{
	if (InObject->GetModuleIndex() < ModuleGroup.Num() && ModuleGroup[InObject->GetModuleIndex()])
	{
		ModuleGroup[InObject->GetModuleIndex()]->RegisterObject(InObject);
		return true;
	}
	return false;
}


void USSCCenterModule::ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* _Param)
{
	if (Agrement.ModuleIndex < ModuleGroup.Num() && ModuleGroup[Agrement.ModuleIndex])
	{
		ModuleGroup[Agrement.ModuleIndex]->ProcessModuleReflectFuncEvnt(Agrement,_Param);
	}
}

void USSCCenterModule::ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* _Param)
{
	if (Agrement.ModuleIndex < ModuleGroup.Num() && ModuleGroup[Agrement.ModuleIndex])
	{
		ModuleGroup[Agrement.ModuleIndex]->ProcessObjectReflectFuncEvnt(Agrement, _Param);
	}
}
