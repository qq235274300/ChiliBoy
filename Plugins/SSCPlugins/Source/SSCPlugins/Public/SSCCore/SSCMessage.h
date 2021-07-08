// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCModulInterface.h"
#include "GameFramework/PlayerController.h"
#include "SSCMessage.generated.h"

/**
 * 
 */

#pragma region InputBinder

DECLARE_DELEGATE(FInputBinderDelegate)
UCLASS()
class SSCPLUGINS_API UBinderEvent : public UObject
{
	GENERATED_BODY()
public:
	UBinderEvent();
	template<class UserClass>
	void InitBinder(UserClass* ObjClass,typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod,int8 TotalKeyNum);
	void PressEvnt();
	void ReleasedEvnt();
public:
	FInputBinderDelegate InputBinderDel;
	int8 InputCount;
	int8 TotoalCount;
	bool  bExecuteWhenPaused;
};

template<class UserClass>
void UBinderEvent::InitBinder(UserClass* ObjClass, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod, int8 TotalKeyNum)
{
	InputBinderDel.BindUObject(ObjClass, InMethod);
	TotoalCount = TotalKeyNum;
}

#pragma endregion

UCLASS()
class SSCPLUGINS_API USSCMessage : public UObject, public ISSCModulInterface
{
	GENERATED_BODY()

public:
	USSCMessage();

public:
	virtual void ModuleInit();
	virtual void ModuleBeginPlay();
	virtual void ModuleTick(float DeltaSeconds);


public:
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... >  RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(FName CallName,TFunction<RetType(VarTypes...)> InFunc);

public:
	/************************携程************************************/
	//true 开启成功，flase 有同名携程存在
	bool StartCoroutine(FName ObjName,FName CoroName, FCoroStack* CoroTask);
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
	FInputAxisBinding& BindAxis(const FName AxisName,UserClass* ClassObj, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputActionBinding& BindAction(const FName ActionName,const EInputEvent KeyEvent,UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputTouchBinding& BindTouch(const EInputEvent KeyEvent,UserClass* ClassObj,typename FInputTouchHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	FInputKeyBinding& BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod);
	template<class UserClass>
	UBinderEvent& BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod, TArray<FKey>& Keys,FName ObjName);
	void UnBindKeys(FName ObjName);
	
	/***************************************************************/
protected:
	APlayerController* PlayerController;

	FFuncQuene* FuncQuene;

	TMap<FName, TMap<FName, FCoroStack*>> CoroGroup;
	TMap<FName, TMap<FName, FInvokeTask*>> InvokeGroup;
	TMap<FName, TArray<UBinderEvent*>> InputBinderGroup;
};

template<typename RetType, typename...VarTypes>
FFuncCallHandle<RetType, VarTypes... > USSCMessage::RegisterCallHandle(FName CallName)
{
	return FuncQuene->RegisterCallHandle<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename...VarTypes>
FFuncHandle USSCMessage::RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	return FuncQuene->RegisterFuncHandle<RetType, VarTypes...>(CallName, InFunc);
}

template<class UserClass>
FInputAxisBinding& USSCMessage::BindAxis(const FName AxisName,UserClass* ClassObj, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return PlayerController->InputComponent->BindAxis(AxisName, ClassObj, InMethod);
}

template<class UserClass>
FInputActionBinding& USSCMessage::BindAction(const FName ActionName, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return PlayerController->InputComponent->BindAction(ActionName,KeyEvent,ClassObj, InMethod);
}

template<class UserClass>
FInputTouchBinding& USSCMessage::BindTouch(const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputTouchHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	return PlayerController->InputComponent->BindTouch(KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
FInputKeyBinding& USSCMessage::BindKey(const FKey Key, const EInputEvent KeyEvent, UserClass* ClassObj, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)
{
	
		return PlayerController->InputComponent->BindKey(Key,KeyEvent, ClassObj, InMethod);
}

template<class UserClass>
UBinderEvent& USSCMessage::BindKeys(UserClass* ClassObj, typename FInputBinderDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod,  TArray<FKey>& Keys, FName ObjName)
{
	UBinderEvent* BinderEventPtr = NewObject<UBinderEvent>();
	BinderEventPtr->AddToRoot();
	BinderEventPtr->InitBinder(ClassObj, InMethod, Keys.Num());
	for (int i = 0; i < Keys.Num(); ++i)
	{
		PlayerController->InputComponent->BindKey(Keys[i], IE_Pressed, BinderEventPtr, &UBinderEvent::PressEvnt).bExecuteWhenPaused =true;
		PlayerController->InputComponent->BindKey(Keys[i], IE_Released, BinderEventPtr, &UBinderEvent::ReleasedEvnt).bExecuteWhenPaused = true;
	}

	if (!InputBinderGroup.Contains(ObjName))
	{
		TArray<UBinderEvent*> Binders;
		InputBinderGroup.Add(ObjName, Binders);
		
	}
	InputBinderGroup.Find(ObjName)->Push(BinderEventPtr);
	return *BinderEventPtr;
}

