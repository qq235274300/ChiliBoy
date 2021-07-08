// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCCore/SSCModule.h"
#include "SSCCenterModule.generated.h"

/**
 * 
 */
class ISSCObjectInterface;
UCLASS()
class SSCPLUGINS_API USSCCenterModule : public USSCModule
{
	GENERATED_BODY()
	
public:
	 void IterGetModuleChildren(USSCModule* _Module,FName ModuleName);
	 void IterCreateSubModule(USSCModule* _Module);
	 void IterModuleInit(USSCModule* _Module);
	 void IterModuleBeginPlay(USSCModule* _Module);
	 void IterModuleTick(USSCModule* _Module,float DeltaSeconds);
public:
	void GatherModule(FName ModuleType);
	void IterGatherModule(USSCModule* Module, TArray<USSCModule*>& GatherGroup);

public:
	bool RegisterObject(ISSCObjectInterface* InObject);

public:
	/**********************Reflect*******************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement,FRelfectFuncParam* _Param);
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* _Param);
	/**********************End**********************************/

	/**********************RegisterFunc*******************************/
	template<typename RetType, typename... VarTypes>
	FFuncHandle CenterRegisterFuncHandle(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InFunc);

	/**********************End**********************************/
private:
	UPROPERTY()
	TArray<USSCModule*> ModuleGroup;

};

template<typename RetType, typename...VarTypes>
FFuncHandle USSCCenterModule::CenterRegisterFuncHandle(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	if (ModuleGroup[ModuleID])
	{
		return ModuleGroup[ModuleID]->RegisterFuncHandle<RetType, VarTypes...>(CallName, InFunc);
	}
	return FFuncHandle();
}
