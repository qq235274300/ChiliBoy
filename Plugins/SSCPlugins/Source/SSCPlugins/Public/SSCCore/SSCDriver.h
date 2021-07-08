// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSCCommon/SSCCommon.h"
#include "SSCCenterModule.h"
#include "SSCDriver.generated.h"

class ISSCObjectInterface;


UCLASS()
class SSCPLUGINS_API ASSCDriver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSCDriver();

	//定义生命周期
	virtual void PostInitializeComponents()override;
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RegisterGamePlay();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)override;
#endif

public:
	bool RegisterObject(ISSCObjectInterface* Object);

public:
	/**********************Reflect*******************************/
	void ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* _Param);
	void ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* _Param);
	/**********************End**********************************/

	/**********************RegisterFunc*******************************/
	template<typename RetType, typename... VarTypes>
	FFuncHandle  RegisterFuncHandle(int32 ModuleId,FName CallName, TFunction<RetType(VarTypes...)> InFunc);
	/**********************End**********************************/
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "SSCDriver")
		FName ModuleType;
private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY()
	USSCCenterModule* Center;
	

private:
	bool bModuleHasBeginPlay = false;
};

template<typename RetType, typename... VarTypes>
FFuncHandle ASSCDriver::RegisterFuncHandle(int32 ModuleId, FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	return Center->CenterRegisterFuncHandle<RetType, VarTypes...>(ModuleId,CallName, InFunc);
}
