// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCModulInterface.h"
#include "SSCCommon.h"
#include "SSCDriver.h"
#include "SSCModule.h"

// Add default functionality here for any ISSCModulInterface functions that are not pure virtual.

void ISSCModulInterface::SetBelongModule(USSCModule* _Module)
{
	Module = _Module;
	_ModuleIndex = Module->ModuleIndex;
	Dirver = USSCCommon::Get()->GetDirver();
}

void ISSCModulInterface::ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Parm)
{
	if (Agrement.ModuleIndex == _ModuleIndex)
	{
		Module->ProcessModuleReflectFuncEvnt(Agrement, Parm);
	}
	else
	{
		Dirver->ProcessModuleReflectFuncEvnt(Agrement, Parm);
	}
}

void ISSCModulInterface::ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Parm)
{
	if (Agrement.ModuleIndex == _ModuleIndex)
	{
		Module->ProcessObjectReflectFuncEvnt(Agrement, Parm);
	}
	else
	{
		Dirver->ProcessObjectReflectFuncEvnt(Agrement, Parm);
	}
}

UWorld* ISSCModulInterface::GetModuleWorld()
{
	if (Dirver)
		return Dirver->GetWorld();

	return nullptr;
}
