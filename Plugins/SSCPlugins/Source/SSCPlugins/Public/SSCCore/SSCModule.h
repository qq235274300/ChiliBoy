// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SSCMessage.h"
#include "SSCModule.generated.h"

class USSCModel;
class USSCWealth;
class ISSCObjectInterface;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SSCPLUGINS_API USSCModule : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCModule();

public:
	void GetModuleIndex(FName ModuleType);
	 void CreateSubModule();
	 virtual void ModuleInit();
	 virtual void ModuleBeginPlay();
	 virtual void ModuleTick(float DeltaSeconds);

public:
	void RegisterObject(ISSCObjectInterface* InObject);
	void DestroyObject(FName _ObjectName);

	/******Batch****************/
	UFUNCTION()
	void DestroyObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	UFUNCTION()
	void EnableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	UFUNCTION()
	void DisableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	
public:
	/****************************ModuleReflect******************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Param);
	/****************************ObjectReflect******************************/
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);

	void ProcessSelfObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessOtherObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessClassOtherReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessSelfClassReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessOtherClassReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);
	void ProcessAllObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Param);

	/****************************RegisterFuncHandle******************************/
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... >  RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc);


public:
	/************************携程************************************/
	//true 开启成功，flase 有同名携程存在
	bool StartCoroutine(FName ObjName, FName CoroName, FCoroStack* CoroTask);
	bool StopCoroutine(FName ObjName, FName CoroName);
	//停止一个对象下的所有携程
	void StopAllCoroutine(FName ObjName);
	/***************************************************************/

	/*********************延迟节点*********************************/
	//true 开启成功，flase 有同名携程存在
	bool StartInvoke(FName ObjName, FName InvokeName, FInvokeTask* InvokeTask);
	bool StopInvoke(FName ObjName, FName InvokeName);
	//停止一个对象下的所有携程
	void StopAllInvoke(FName ObjName);
	/***************************************************************/



	/*********************绑定按键**********************************/
	template<class UserClass>
	FInputAxisBinding& BindAxis(const FName AxisName, UserClass* ClassObj, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputActionBinding& BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputTouchBinding& BindTouch(const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputTouchHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputKeyBinding& BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	UBinderEvent& BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod,  TArray<FKey>& Keys, FName ObjName);
	void UnBindKeys(FName ObjName);


	/***************************************************************/



	/*********************加载资源*********************************/
	FWealthURL* GetWealthURL(FName _ObjName);
	void GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL);

	FWealthObjectEntry* GetWealthObjectSingleEntry(FName WealthName);
	TArray<FWealthObjectEntry*> GetWealthObjectKindEntry(FName WealthKindName);
	FWealthClassEntry* GetWealthClassSingleEntry(FName WealthName);
	TArray<FWealthClassEntry*> GetWealthClassKindEntry(FName WealthKindName);

	void LoadObjectEntry(FName _WealthName, FName _ObjName, FName _FunName);
	void LoadObjectKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName);
	void LoadClassEntry(FName _WealthName, FName _ObjName, FName _FunName);
	void LoadClassKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName);

	void BuildSinglClassWealth(EWealthClassType Type, FName _WealthName, FName _ObjName, FName _FunName, FTransform _SpawnTransform);
	void BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _ObjName, FName _FunName, TArray<FTransform> _SpawnTransforms);
	void BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount, FName _ObjName, FName _FunName, TArray<FTransform> _SpawnTransforms);
	/***************************************************************/


	/****************************Test******************************/
	
	/***************************End***********************************/
 public:
	TArray<USSCModule*> ChildrenModules;
	int32 ModuleIndex;
private:
	USSCModel* Model;
	USSCMessage* Message;
	USSCWealth* Wealth;
public:
	UPROPERTY(EditAnywhere)
	TArray<UWealthDataAsset*> AutoDataAssets;
};

template<typename RetType, typename...VarTypes>
FFuncCallHandle<RetType, VarTypes... > USSCModule::RegisterCallHandle(FName CallName)
{
	return Message->RegisterCallHandle<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename...VarTypes>
FFuncHandle USSCModule::RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	return Message->RegisterFuncHandle<RetType, VarTypes... >(CallName, InFunc);
}

template<class UserClass>
FInputAxisBinding& USSCModule::BindAxis(const FName AxisName, UserClass* ClassObj, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Message->BindAxis(AxisName, ClassObj, InMethod);
}

template<class UserClass>
FInputActionBinding& USSCModule::BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Message->BindAction(ActionName, KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
FInputTouchBinding& USSCModule::BindTouch(const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputTouchHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Message->BindTouch( KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
FInputKeyBinding& USSCModule::BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Message->BindKey(Key,KeyEvent,ClassObj,InMethod);
}

template<class UserClass>
UBinderEvent& USSCModule::BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod,  TArray<FKey>& Keys, FName ObjName)
{
	return Message->BindKeys(ClassObj, InMethod, Keys, ObjName);
}
