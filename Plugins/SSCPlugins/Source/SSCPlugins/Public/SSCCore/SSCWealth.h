// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCModulInterface.h"
#include "Engine/StreamableManager.h"
#include "SSCDefine.h"
#include "SSCWealth.generated.h"

/**
 * 
 */

struct FSingleObjectEntryLoadNode;
struct FKindObjectEntryLoadNode;
struct FSingleClassEntryLoadNode;
struct FKindClassEntryLoadNode;
struct FMultiClassEntryLoadNode;


UCLASS()
class SSCPLUGINS_API USSCWealth : public UObject, public ISSCModulInterface
{
	GENERATED_BODY()
public:
	virtual void ModuleInit();
	virtual void ModuleBeginPlay();
	virtual void ModuleTick(float DeltaSeconds);
public:
	void SetAutoDataAssets(TArray<UWealthDataAsset*>& InData);

public:
	/******************加载资源*******************/
	FWealthURL* GetWealthURL(FName _ObjName);
	void GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL);

	FWealthObjectEntry* GetWealthObjectSingleEntry(FName WealthName);
	TArray<FWealthObjectEntry*> GetWealthObjectKindEntry(FName WealthKindName);
	FWealthClassEntry* GetWealthClassSingleEntry(FName WealthName);
	TArray<FWealthClassEntry*> GetWealthClassKindEntry(FName WealthKindName);

	void LoadObjectEntry(FName _WealthName, FName _ObjName, FName _FunName); // 后面两个参数调用反射 将加载完成的Object 传给对象方法
	void LoadObjectKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName); 
	void LoadClassEntry(FName _WealthName, FName _ObjName, FName _FunName); 
	void LoadClassKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName);

	void BuildSinglClassWealth(EWealthClassType Type,FName _WealthName, FName _ObjName,FName _FunName,FTransform _SpawnTransform);
	void BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _ObjName, FName _FunName, TArray<FTransform> _SpawnTransforms);
	void BuildMultiClassWealth(EWealthClassType Type, FName _WealthName,int32 _Amount, FName _ObjName, FName _FunName, TArray<FTransform> _SpawnTransforms);
	/********************************************/

protected:
	/******************处理加载资源*******************/
	void DealSingleObjectEntryLoadArray();
	void DealKindObjectEntryLoadArray();
	void DealSingleClassEntryLoadArray();
	void DealKindClassEntryLoadArray();
	void DealMultiClassEntryLoadNodeArray();
private:
	//加载器
	FStreamableManager WealthLoader;
	TArray<FSingleObjectEntryLoadNode*> SingleObjectEntryLoadArray;
	TArray<FKindObjectEntryLoadNode*> KindObjectEntryLoadArray;
	TArray<FSingleClassEntryLoadNode*> SingleClassEntryLoadArray;
	TArray<FKindClassEntryLoadNode*> KindClassEntryLoadArray;
	TArray<FMultiClassEntryLoadNode*> MultiClassEntryLoadNodeArray;

	TArray<UWealthDataAsset*> AutoDataAssets;

	UPROPERTY()
		TArray<UUserWidget*> AutoCreateWidgetData;




protected:
	float Timer = 0.f;
	REFOBJFUNC_TWO(BackWealthObjectSingle, FName, WealthName, UObject*, WealthObject);
	REFOBJFUNC_TWO(BackWealthObjectKind, TArray<FName>, WealthNameArray, TArray <UObject*>, WealthObjectArray);
	REFOBJFUNC_TWO(BackWealthClassSingle, FName, WealthName, UClass*, WealthObject);
	REFOBJFUNC_TWO(BackWealthClassKind, TArray<FName>, WealthNameArray, TArray <UClass*>, WealthClassArray);

	REFOBJFUNC_TWO(BackObject, FName, WealthName, UObject*, WealthObject);
	REFOBJFUNC_TWO(BackObjectKind, TArray<FName>, WealthNames, TArray <UObject*>, WealthObjects);
	REFOBJFUNC_TWO(BackObjectMulti, FName, WealthName, TArray <UObject*>, WealthObjects);

	REFOBJFUNC_TWO(BackActor, FName, WealthName, AActor*, WealthActor);
	REFOBJFUNC_TWO(BackActorKind, TArray<FName>, WealthNames, TArray <AActor*>, WealthActors);
	REFOBJFUNC_TWO(BackActorMulti, FName, WealthName, TArray <AActor*>, WealthActors);

	REFOBJFUNC_TWO(BackWidget, FName, WealthName, UUserWidget*, WealthWidget);
	REFOBJFUNC_TWO(BackWidgetKind, TArray<FName>, WealthNames, TArray <UUserWidget*>, WealthWidgets);
	REFOBJFUNC_TWO(BackWidgetMulti, FName, WealthName, TArray <UUserWidget*>, WealthWidgets);
	//REFOBJFUNC_ONE(Call01,FString,Info);
};
