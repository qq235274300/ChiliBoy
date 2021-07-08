// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSCPlugins/Public/SSCCore/SSCDriver.h"
#include "SSCPlugins/Public/SSCCore/SSCModule.h"
#include "SSCObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSCObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/********************************************/
/*     �˽ӿ��ṩ����ע�� �� �������ڷ���	*/
/********************************************/
/**
 * 
 */
class SSCPLUGINS_API ISSCObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UWorld* GetCurrentWorld()const;
public:
	void RegisterToModule(FName ModuleName,FName ObjName = FName() , FName ClsName = FName());
	void RegisterToModule(int32 _ModuleIndex, FName ObjName = FName(), FName ClsName = FName());
	/***********************************************/
	FName GetObjectName();
	FName GetClassName();
	int32 GetModuleIndex()const;
	UObject* GetBody()const;
	void SetModuel(USSCModule* InModuel);

public:
	virtual void ModelInit();
	virtual void ModelLoading();
	virtual void ModelRegsiter();
	virtual void ModelEnable();

	virtual void ModelTick(float DeltaSeconds);

	virtual void ModelDisable();
	virtual void ModelUnRegister();
	virtual void ModelUnLoading();
	virtual void ModelRelease();

	bool ActiveLife();
	bool DestroyLife();
	
	virtual void OnEnable();
	virtual void OnDisable();

	void DestroySelf();

public:
	/*****************Reflect*****************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Parm);
	/****************************************************/

protected:
	/*****************RegisterFunc*****************************/
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... >  RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InFunc);
	/****************************************************/
protected:
	/************************Я��************************************/
	//true �����ɹ���flase ��ͬ��Я�̴���
	bool StartCoroutine( FName CoroName, FCoroStack* CoroTask);
	bool StopCoroutine(FName CoroName);
	//ֹͣһ�������µ�����Я��
	void StopAllCoroutine();

	/**********************�ӳٽڵ�************************************/
	template<class UserClass>
	bool StartInvokeDelay(FName InvokeName,float DelayTime, UserClass* Obj,typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr);
	template<class UserClass>
	bool StartInvokeRepeated(FName InvokeName, float DelayTime,float RepeatedTime, UserClass* Obj, typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr);
	bool StopInvoke(FName InvokeName);
	//ֹͣһ�������µ�����Я��
	void StopAllInvoke();

	/*********************�󶨰���**********************************/
	template<class UserClass>
	FInputAxisBinding& BindAxis(const FName AxisName, UserClass* ClassObj, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputActionBinding& BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputTouchBinding& BindTouch(const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputTouchHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputKeyBinding& BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	UBinderEvent& BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod, FKey Key_I, FKey Key_II);
	template<class UserClass>
	UBinderEvent& BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod, FKey Key_I, FKey Key_II,FKey Key_III);
	void UnBindKeys();

	/*********************������Դ*********************************/
	FWealthURL* GetWealthURL(FName _ObjName);
	void GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL);

	FWealthObjectEntry* GetWealthObjectSingleEntry(FName WealthName);
	TArray<FWealthObjectEntry*> GetWealthObjectKindEntry(FName WealthKindName);
	FWealthClassEntry* GetWealthClassSingleEntry(FName WealthName);
	TArray<FWealthClassEntry*> GetWealthClassKindEntry(FName WealthKindName);
	//����UObject��Դ
	void LoadObjectEntry(FName _WealthName, FName _FunName);
	void LoadObjectKindEntry(FName _WealthKindName, FName _FunName);
	//����UClass��Դ
	void LoadClassEntry(FName _WealthName,FName _FunName);
	void LoadClassKindEntry(FName _WealthKindName,FName _FunName);
	//��������ʵ��
	void BuildSinglClassWealth(EWealthClassType Type, FName _WealthName, FName _FunName);
	void BuildSinglClassWealth(EWealthClassType Type, FName _WealthName, FName _FunName, FTransform _SpawnTransform);

	void BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName,  FName _FunName);
	void BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _FunName, FTransform _SpawnTransforms);
	void BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _FunName, TArray<FTransform> _SpawnTransforms);

	void BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount,  FName _FunName);
	void BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount,FName _FunName, FTransform _SpawnTransforms);
	void BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount,  FName _FunName, TArray<FTransform> _SpawnTransforms);
	/***************************************************************/

protected:

	UObject* Body;
	USSCModule* Module;
	ASSCDriver* Dirver;
	int32 ModuleIndex;
	FName ObjectName;
	FName ClassName;

public:
	bool bIsAllowTick = false;
	EBaseObjectLife LifeState;
	EBaseObjectState RunState;
};

template<typename RetType, typename... VarTypes>
FFuncCallHandle<RetType, VarTypes... >
ISSCObjectInterface::RegisterCallHandle(FName CallName)
{
	return Module->RegisterCallHandle<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename...VarTypes>
FFuncHandle ISSCObjectInterface::RegisterFuncHandle(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	if (ModuleIndex == ModuleID)
	{
		return	Module->RegisterFuncHandle<RetType, VarTypes...>(CallName, InFunc);
	}
	
	return Dirver->RegisterFuncHandle<RetType, VarTypes...>(ModuleID,CallName,InFunc);
}

template<class UserClass>
bool ISSCObjectInterface::StartInvokeDelay(FName InvokeName, float DelayTime, UserClass* Obj, typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr)
{
	FInvokeTask* Task = new FInvokeTask(DelayTime, false, 0.f);
	Task->FInvokeDel.BindUObject(Obj, InMothodPtr);
	return Module->StartInvoke(GetObjectName(), InvokeName, Task);
}

template<class UserClass>
bool ISSCObjectInterface::StartInvokeRepeated(FName InvokeName, float DelayTime, float RepeatedTime, UserClass* Obj, typename FInvokeDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMothodPtr)
{
	FInvokeTask* Task = new FInvokeTask(DelayTime, true, RepeatedTime);
	Task->FInvokeDel.BindUObject(Obj, InMothodPtr);
	return Module->StartInvoke(GetObjectName(), InvokeName, Task);
}

template<class UserClass>
FInputAxisBinding& ISSCObjectInterface::BindAxis(const FName AxisName, UserClass* ClassObj, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Module->BindAxis(AxisName, ClassObj, InMethod);
}

template<class UserClass>
FInputActionBinding& ISSCObjectInterface::BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Module->BindAction(ActionName, KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
FInputTouchBinding& ISSCObjectInterface::BindTouch(const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputTouchHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Module->BindTouch( KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
FInputKeyBinding& ISSCObjectInterface::BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return Module->BindKey(Key , KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
UBinderEvent& ISSCObjectInterface::BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod, FKey Key_I, FKey Key_II)
{
	TArray<FKey> Keys;
	Keys.Push(Key_I);
	Keys.Push(Key_II);
	
	return Module->BindKeys(ClassObj, InMethod, Keys,GetObjectName());
}

template<class UserClass>
UBinderEvent& ISSCObjectInterface::BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod, FKey Key_I, FKey Key_II, FKey Key_III)
{
	TArray<FKey> Keys;
	Keys.Push(Key_I);
	Keys.Push(Key_II);
	Keys.Push(Key_III);
	return Module->BindKeys(ClassObj, InMethod, Keys, GetObjectName());
}
