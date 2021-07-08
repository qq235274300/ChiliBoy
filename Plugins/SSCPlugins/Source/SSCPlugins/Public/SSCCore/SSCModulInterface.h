// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSCPlugins/Public/SSCCommon/SSCTypes.h"

#include "SSCModulInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSCModulInterface : public UInterface
{
	GENERATED_BODY()
};

class USSCModule;
class ASSCDriver;
/**
 * 
 */
class SSCPLUGINS_API ISSCModulInterface
{
	GENERATED_BODY()

public:
	void SetBelongModule(USSCModule* _Module);
public:
	/*****************Reflect*****************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	/****************************************************/

	UWorld* GetModuleWorld();


public:
	USSCModule* Module;
	int32 _ModuleIndex;
private:

	
	ASSCDriver* Dirver;
	
};
