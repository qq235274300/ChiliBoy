// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCModulInterface.h"
#include "SSCModel.generated.h"

/**
 * 
 */
class ISSCObjectInterface;
UCLASS()
class SSCPLUGINS_API USSCModel : public UObject , public ISSCModulInterface
{
	GENERATED_BODY()

public:
	virtual void ModuleInit();
	virtual void ModuleBeginPlay();
	virtual void ModuleTick(float DeltaSeconds);

public:
	void RegisterObject(ISSCObjectInterface* InObject);
	void DestroyObject(FName InObjectName);

	/****************************/
	//Batch
	void DestroyObject(EAgreementType Type,TArray<FName> TargetObjectNameArray);
	void EnableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);
	void DisableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray);

	/****************************/
	void GetSelfObject(TArray<FName> TargetObjectNameArray,TArray<ISSCObjectInterface*>& TargetObjectArray);
	int32 GetOtherObject(TArray<FName> TargetObjectNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray);
	//ObjectName must have same class Name
	int32 GetClassOtherObject(TArray<FName> TargetObjectNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray);
	//
	void GetSelfClass(TArray<FName> TargetClassNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray);
	void GetOtherClass(TArray<FName> TargetClassNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray);
	void GetAllObject(TArray<ISSCObjectInterface*>& TargetObjectArray);

	/****************************/
	void GetObjectByAgreement(EAgreementType _Agreement, TArray<FName> TargetNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray);

protected:
	TMap<FName, ISSCObjectInterface*> ObjectGroup;
	TMap<FName, TArray<ISSCObjectInterface*>> ObjectClassGroup;
	TArray<ISSCObjectInterface*> ObjectActiveArray;
	TArray<ISSCObjectInterface*> ObjectTickArray;
	
	TArray<ISSCObjectInterface*> ObjectPreDestroyArray;
	TArray<ISSCObjectInterface*> ObjectDestroyArray;
	TArray<ISSCObjectInterface*> ObjectReleaseArray;
};
