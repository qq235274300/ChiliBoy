// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCWealth.h"
#include "SSCObjectInterface.h"
#include "Blueprint/UserWidget.h"


struct FSingleObjectEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	FWealthObjectEntry* WealthObjectEntry;
	FName ObjectName;
	FName FuncName;
	FSingleObjectEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle , FWealthObjectEntry* _WealthObjectEntry, FName _ObjectName,FName _FuncName)
	{
		LoaderHandle = _LoaderHandle;
		WealthObjectEntry = _WealthObjectEntry;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
	}
}; 

struct FKindObjectEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	TArray<FWealthObjectEntry*> LoadEntrys;
	TArray<FWealthObjectEntry*> UnLoadEntrys;
	FName ObjectName;
	FName FuncName;
	FKindObjectEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, TArray<FWealthObjectEntry*> _LoadEntrys,
	TArray<FWealthObjectEntry*> _UnLoadEntrys,FName _ObjectName, FName _FuncName)
	{
		LoaderHandle = _LoaderHandle;
		LoadEntrys = _LoadEntrys;
		UnLoadEntrys = _UnLoadEntrys;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
	}
};

struct FSingleClassEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	FWealthClassEntry* WealthClassEntry;
	FName ObjectName;
	FName FuncName;
	FTransform SpawnTransform;
	bool isLoadClass; //为true 表示只加载 false 加载完直接生成对象

	FSingleClassEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, FWealthClassEntry* _WealthClassEntry, FName _ObjectName, FName _FuncName)
	{
		LoaderHandle = _LoaderHandle;
		WealthClassEntry = _WealthClassEntry;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
		isLoadClass = true;
	}

	FSingleClassEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, FWealthClassEntry* _WealthClassEntry, FName _ObjectName, FName _FuncName,FTransform _SpawnTransform)
	{
		LoaderHandle = _LoaderHandle;
		WealthClassEntry = _WealthClassEntry;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
		SpawnTransform = _SpawnTransform;
		isLoadClass = false;
	}
};

struct FKindClassEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	TArray<FWealthClassEntry*> LoadEntrys;
	TArray<FWealthClassEntry*> UnLoadEntrys;
	FName ObjectName;
	FName FuncName;
	TArray<FTransform> SpawnTransforms;
	bool isLoadClass;
	TArray<FName> NameArray;
	TArray<UObject*> ObjectsArray;
	TArray<AActor*> ActorArray;
	TArray<UUserWidget*> WidgetArray;
	FKindClassEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, TArray<FWealthClassEntry*> _LoadEntrys,
		TArray<FWealthClassEntry*> _UnLoadEntrys, FName _ObjectName, FName _FuncName)
	{
		LoaderHandle = _LoaderHandle;
		LoadEntrys = _LoadEntrys;
		UnLoadEntrys = _UnLoadEntrys;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
		isLoadClass = true;
	}

	FKindClassEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, TArray<FWealthClassEntry*> _LoadEntrys,
		TArray<FWealthClassEntry*> _UnLoadEntrys, FName _ObjectName, FName _FuncName,TArray<FTransform>_SpawnTransform)
	{
		LoaderHandle = _LoaderHandle;
		LoadEntrys = _LoadEntrys;
		UnLoadEntrys = _UnLoadEntrys;
		ObjectName = _ObjectName;
		FuncName = _FuncName; 
		SpawnTransforms = _SpawnTransform;
		isLoadClass = false;
	}
};

struct FMultiClassEntryLoadNode
{
public:
	TSharedPtr<FStreamableHandle> LoaderHandle;
	FWealthClassEntry* WealthClassEntry;
	FName ObjectName;
	FName FuncName;
	int32 Amount;
	TArray<FTransform> SpawnTransforms;
	TArray<UObject*> ObjectsArray;
	TArray<AActor*> ActorArray;
	TArray<UUserWidget*> WidgetArray;
	

	FMultiClassEntryLoadNode(TSharedPtr<FStreamableHandle> _LoaderHandle, FWealthClassEntry* _WealthClassEntry, FName _ObjectName, FName _FuncName,int32 _Amount,
		TArray<FTransform> _SpawnTransforms)
	{
		LoaderHandle = _LoaderHandle;
		WealthClassEntry = _WealthClassEntry;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
		Amount = _Amount;
		SpawnTransforms = _SpawnTransforms;
	}

	FMultiClassEntryLoadNode( FWealthClassEntry* _WealthClassEntry, FName _ObjectName, FName _FuncName, int32 _Amount,
		TArray<FTransform> _SpawnTransforms)
	{
		WealthClassEntry = _WealthClassEntry;
		ObjectName = _ObjectName;
		FuncName = _FuncName;
		Amount = _Amount;
		SpawnTransforms = _SpawnTransforms;
		
	}


};



void USSCWealth::ModuleInit()
{

}

void USSCWealth::ModuleBeginPlay()
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		//Create Object
		for (int j = 0; j < AutoDataAssets[i]->AutoObjects.Num(); ++j)
		{
			UObject* NewObj = NewObject<UObject>(this, AutoDataAssets[i]->AutoObjects[j].ObjectClass);
			NewObj->AddToRoot();
			ISSCObjectInterface* ModuleObj = Cast<ISSCObjectInterface>(NewObj);
			if (ModuleObj)
			{
				ModuleObj->RegisterToModule
				(
					AutoDataAssets[i]->ModuleName.IsNone() ? Module->GetFName() : AutoDataAssets[i]->ModuleName,
					AutoDataAssets[i]->AutoObjects[j].ObjectName,
					AutoDataAssets[i]->AutoObjects[j].ClassName
				);
			}
		}
		//SpawnActor
		for (int j = 0; j < AutoDataAssets[i]->AutoActors.Num(); ++j)
		{
			AActor* NewActor = GetModuleWorld()->SpawnActor<AActor>(AutoDataAssets[i]->AutoActors[j].ActorClass, AutoDataAssets[i]->AutoActors[j].SpawnTransform);
			ISSCObjectInterface* ModuleActor = Cast<ISSCObjectInterface>(NewActor);
			if (ModuleActor)
			{
				ModuleActor->RegisterToModule
				(
					AutoDataAssets[i]->ModuleName.IsNone() ? Module->GetFName() : AutoDataAssets[i]->ModuleName,
					AutoDataAssets[i]->AutoActors[j].ObjectName,
					AutoDataAssets[i]->AutoActors[j].ClassName
				);
			}
		}
		//CreateWidget
		for (int j = 0; j < AutoDataAssets[i]->AutoWidgets.Num(); ++j)
		{
			UUserWidget* NewWidget = CreateWidget(GetModuleWorld(), AutoDataAssets[i]->AutoWidgets[j].WidgetClass);
			AutoCreateWidgetData.Push(NewWidget);
			ISSCObjectInterface* ModuleWidget = Cast<ISSCObjectInterface>(NewWidget);
			if (ModuleWidget)
			{
				ModuleWidget->RegisterToModule
				(
					AutoDataAssets[i]->ModuleName.IsNone() ? Module->GetFName() : AutoDataAssets[i]->ModuleName,
					AutoDataAssets[i]->AutoWidgets[j].ObjectName,
					AutoDataAssets[i]->AutoWidgets[j].ClassName
				);
			}
		}
#if WITH_EDITOR
		//保证编译器运行时异步加载

		for (int j = 0; j < AutoDataAssets[i]->WealthObjects.Num(); ++j)
		{
			AutoDataAssets[i]->WealthObjects[j].ObjInst = nullptr;
		}
		for (int j = 0; j < AutoDataAssets[i]->WealthClasses.Num(); ++j)
		{
			AutoDataAssets[i]->WealthClasses[j].ObjInst = nullptr;
		}
#endif

	}
}

void USSCWealth::ModuleTick(float DeltaSeconds)
{
	//Call01((int32)ESSCGame::Center,"TestActor01","RefCallFunc","balalalal");
	DealSingleObjectEntryLoadArray();
	DealKindObjectEntryLoadArray();
	DealSingleClassEntryLoadArray();
	DealKindClassEntryLoadArray();
	DealMultiClassEntryLoadNodeArray();
}

void USSCWealth::SetAutoDataAssets(TArray<UWealthDataAsset*>& InData)
{
	AutoDataAssets = InData;
}

FWealthURL* USSCWealth::GetWealthURL(FName _ObjName)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthURLs.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthURLs[j].ObjName.IsEqual(_ObjName))
				return &AutoDataAssets[i]->WealthURLs[j];
		}
	}
	return nullptr;
}

void USSCWealth::GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthURLs.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthURLs[j].KindName.IsEqual(_KindName))
				OutWealthURL.Push(&AutoDataAssets[i]->WealthURLs[j]);
		}
	}
}

FWealthObjectEntry* USSCWealth::GetWealthObjectSingleEntry(FName WealthName)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthObjects.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthObjects[j].ObjName.IsEqual(WealthName))
				return &AutoDataAssets[i]->WealthObjects[j];
		}
	}
	return nullptr;
}

TArray<FWealthObjectEntry*> USSCWealth::GetWealthObjectKindEntry(FName WealthKindName)
{
	TArray<FWealthObjectEntry*> ObjectEntrys;
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthObjects.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthObjects[j].KindName.IsEqual(WealthKindName))
				ObjectEntrys.Push(&AutoDataAssets[i]->WealthObjects[j]);
		}
	}
	return ObjectEntrys;
}

FWealthClassEntry* USSCWealth::GetWealthClassSingleEntry(FName WealthName)
{
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthClasses.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthClasses[j].ObjName.IsEqual(WealthName))
			{
				return &AutoDataAssets[i]->WealthClasses[j];
			}
		}
	}
	return nullptr;
}

TArray<FWealthClassEntry*> USSCWealth::GetWealthClassKindEntry(FName WealthKindName)
{
	TArray<FWealthClassEntry*> ClassEntrys;
	for (int i = 0; i < AutoDataAssets.Num(); ++i)
	{
		for (int j = 0; j < AutoDataAssets[i]->WealthClasses.Num(); ++j)
		{
			if (AutoDataAssets[i]->WealthClasses[j].KindName.IsEqual(WealthKindName))
			{
				ClassEntrys.Push(&AutoDataAssets[i]->WealthClasses[j]);				
			}
		}
	}
	return ClassEntrys;
}

void USSCWealth::LoadObjectEntry(FName _WealthName, FName _ObjName, FName _FunName)
{
	FWealthObjectEntry*	 ObjectEntry = GetWealthObjectSingleEntry(_WealthName);
	if (!ObjectEntry)
	{
		SSCHelper::Debug() << _ObjName <<"--->"<< _WealthName<<"--->"<< "Object Asset is Empty" << SSCHelper::Endl();
		return;
	}
	if (!ObjectEntry->ObjectPath.IsValid())
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "Object Asset is Not Valid" << SSCHelper::Endl();
		return;
	}
	if (ObjectEntry->ObjInst)
	{
		//已经加载完成 
		BackWealthObjectSingle(_ModuleIndex, _ObjName, _FunName, _WealthName, ObjectEntry->ObjInst);
	}
	else
	{
		TSharedPtr<FStreamableHandle> LoaderHandle =  WealthLoader.RequestAsyncLoad(ObjectEntry->ObjectPath);
		SingleObjectEntryLoadArray.Push(new FSingleObjectEntryLoadNode(LoaderHandle, ObjectEntry, _ObjName, _FunName));
	}
}

void USSCWealth::LoadObjectKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName)
{

	TArray<FWealthObjectEntry*> WealthKindEntry = GetWealthObjectKindEntry(_WealthKindName);
	if (WealthKindEntry.Num() == 0)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "ObjectKind Asset is Empty" << SSCHelper::Endl();
		return;
	}
	for (int i = 0; i < WealthKindEntry.Num(); ++i)
	{
		if (!WealthKindEntry[i]->ObjectPath.IsValid())
		{
			SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "ObjectKind Asset is not Valid" << SSCHelper::Endl();
			return;
		}
	}

	TArray<FWealthObjectEntry*> UnLoadEntrys;
	TArray<FWealthObjectEntry*> LoadEntrys;
	
	for (int i = 0; i < WealthKindEntry.Num(); ++i)
	{
		if (WealthKindEntry[i]->ObjInst)
		{
			LoadEntrys.Push(WealthKindEntry[i]);
		}
		else
		{
			UnLoadEntrys.Push(WealthKindEntry[i]);
		}
	}

	if (UnLoadEntrys.Num() == 0)  //全部资源以加载
	{
		TArray<FName> WealthNames;
		TArray<UObject*> WealthObjects;
		for (int i = 0; i < LoadEntrys.Num(); ++i)
		{
			WealthNames.Push(LoadEntrys[i]->ObjName);
			WealthObjects.Push(LoadEntrys[i]->ObjInst);
		}
		
		BackWealthObjectKind(_ModuleIndex, _ObjName, _FunName, WealthNames, WealthObjects);
	}
	else
	{
		TArray<FSoftObjectPath> ObjectPaths;
		for (int i = 0; i < UnLoadEntrys.Num(); ++i)
		{
			ObjectPaths.Push(UnLoadEntrys[i]->ObjectPath);
		}
		TSharedPtr<FStreamableHandle> LoadHandle = WealthLoader.RequestAsyncLoad(ObjectPaths);
		KindObjectEntryLoadArray.Push(new FKindObjectEntryLoadNode(LoadHandle, LoadEntrys, UnLoadEntrys, _ObjName, _FunName));
		
		
	}

}

void USSCWealth::LoadClassEntry(FName _WealthName, FName _ObjName, FName _FunName)
{
	FWealthClassEntry* ClassEntry =	 GetWealthClassSingleEntry(_WealthName);
	if (!ClassEntry)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "UClass Asset is Empty" << SSCHelper::Endl();
		return;
	}
	if (!ClassEntry->ClassPtr.ToSoftObjectPath().IsValid())
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "UClass Path is Not Valid" << SSCHelper::Endl();
		return;
	}
	if (ClassEntry->ObjInst)
	{
		BackWealthClassSingle(_ModuleIndex, _ObjName, _FunName, _WealthName, ClassEntry->ObjInst);
	}
	else
	{
		TSharedPtr<FStreamableHandle> LoadHandler = WealthLoader.RequestAsyncLoad(ClassEntry->ClassPtr.ToSoftObjectPath());
		SingleClassEntryLoadArray.Push(new FSingleClassEntryLoadNode(LoadHandler,ClassEntry,_ObjName,_FunName));
	}
}

void USSCWealth::LoadClassKindEntry(FName _WealthKindName, FName _ObjName, FName _FunName)
{
	TArray<FWealthClassEntry*> ClassEntrys = GetWealthClassKindEntry(_WealthKindName);
	if (ClassEntrys.Num() == 0)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "UClass Asset is Empty" << SSCHelper::Endl();
		return;
	}
	for (int i = 0; i < ClassEntrys.Num(); ++i)
	{
		if (!ClassEntrys[i]->ClassPtr.ToSoftObjectPath().IsValid())
		{
			SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "UClass Path is Not Valid" << SSCHelper::Endl();
			return;
		}
	}
	TArray<FWealthClassEntry*> UnLoadClassEntrys;
	TArray<FWealthClassEntry*> LoadClassEntrys;

	for (int i = 0; i < ClassEntrys.Num(); ++i)
	{
		if (ClassEntrys[i]->ObjInst)
		{
			LoadClassEntrys.Push(ClassEntrys[i]);
		}
		else
		{
			UnLoadClassEntrys.Push(ClassEntrys[i]);
		}
	}
		

	if (UnLoadClassEntrys.Num() == 0)
	{
		TArray<FName> _WealthNames;
		TArray<UClass*> _WealthClasses;
		for (int i = 0; i < LoadClassEntrys.Num(); ++i)
		{
			_WealthNames.Push(LoadClassEntrys[i]->ObjName);
			_WealthClasses.Push(LoadClassEntrys[i]->ObjInst);
		}
		
		BackWealthClassKind(_ModuleIndex, _ObjName, _FunName, _WealthNames, _WealthClasses);
	}
	else
	{
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadClassEntrys.Num(); ++i)
		{
			WealthPaths.Push(UnLoadClassEntrys[i]->ClassPtr.ToSoftObjectPath());
		}
		TSharedPtr<FStreamableHandle> ClassHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
		KindClassEntryLoadArray.Push(new FKindClassEntryLoadNode(ClassHandle, LoadClassEntrys, UnLoadClassEntrys, _ObjName, _FunName));
	}
}

void USSCWealth::BuildSinglClassWealth(EWealthClassType Type, FName _WealthName, FName _ObjName, FName _FunName, FTransform _SpawnTransform)
{
	FWealthClassEntry* ClassEntry = GetWealthClassSingleEntry(_WealthName);
	if (!ClassEntry)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "UClass Asset is Empty" << SSCHelper::Endl();
		return;
	}
	if (!ClassEntry->ClassPtr.ToSoftObjectPath().IsValid())
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "UClass Path is Not Valid" << SSCHelper::Endl();
		return;
	}
	//判断资源类型
	if (Type != ClassEntry->ClassType)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "Wrong Type" << SSCHelper::Endl();
		return;
	}
	if (ClassEntry->ObjInst)
	{
		if (Type == EWealthClassType::Object)
		{
			UObject* Inst = NewObject<UObject>(this, ClassEntry->ObjInst);
			Inst->AddToRoot();
			BackObject(_ModuleIndex, _ObjName, _FunName, _WealthName, Inst);
		}
		else if(Type == EWealthClassType::Actor)
		{
			AActor* Inst = GetModuleWorld()->SpawnActor<AActor>(ClassEntry->ObjInst, _SpawnTransform);
			BackActor(_ModuleIndex, _ObjName, _FunName, _WealthName, Inst);
		}
		else if (Type == EWealthClassType::Widget)
		{
			UUserWidget* Inst = CreateWidget<UUserWidget>(GetModuleWorld(), ClassEntry->ObjInst);
			AutoCreateWidgetData.Push(Inst);
			BackWidget(_ModuleIndex, _ObjName, _FunName, _WealthName, Inst);
		}
	}
	else
	{
		TSharedPtr<FStreamableHandle> LoadHandle = WealthLoader.RequestAsyncLoad(ClassEntry->ClassPtr.ToSoftObjectPath());

		SingleClassEntryLoadArray.Push(new FSingleClassEntryLoadNode(LoadHandle,ClassEntry,_ObjName,_FunName,_SpawnTransform));
	}
}

void USSCWealth::BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _ObjName, FName _FunName, TArray<FTransform> _SpawnTransforms)
{
	TArray<FWealthClassEntry*> ClassEntrys = GetWealthClassKindEntry(_WealthKindName);
	if (ClassEntrys.Num() == 0)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "UClass Asset is Empty" << SSCHelper::Endl();
		return;
	}
	for (int i = 0; i < ClassEntrys.Num(); ++i)
	{
		if (!ClassEntrys[i]->ClassPtr.ToSoftObjectPath().IsValid())
		{
			SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "UClass Path is Not Valid" << SSCHelper::Endl();
			return;
		}

		if (ClassEntrys[i]->ClassType!= Type)
		{
			SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "Wrong Type" << SSCHelper::Endl();
			return;
		}

	}
	if (Type == EWealthClassType::Actor && _SpawnTransforms.Num() != 1 && _SpawnTransforms.Num() != ClassEntrys.Num())
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthKindName << "--->" << "Wrong Spawn Number" << SSCHelper::Endl();
		return;
	}


	TArray<FWealthClassEntry*> UnLoadClassEntrys;
	TArray<FWealthClassEntry*> LoadClassEntrys;

	for (int i = 0; i < ClassEntrys.Num(); ++i)
	{
		if (ClassEntrys[i]->ObjInst)
		{
			LoadClassEntrys.Push(ClassEntrys[i]);
		}
		else
		{
			UnLoadClassEntrys.Push(ClassEntrys[i]);
		}
	}
	TSharedPtr<FStreamableHandle> LoadHandle;
	if (UnLoadClassEntrys.Num()>0)
	{
		TArray<FSoftObjectPath> ClassPaths;
		for (int i = 0; i < UnLoadClassEntrys.Num(); ++i)
		{
			ClassPaths.Push(UnLoadClassEntrys[i]->ClassPtr.ToSoftObjectPath());
			
		}
		LoadHandle = WealthLoader.RequestAsyncLoad(ClassPaths);
	}
	
	KindClassEntryLoadArray.Push(new FKindClassEntryLoadNode(LoadHandle, LoadClassEntrys, UnLoadClassEntrys, _ObjName, _FunName, _SpawnTransforms));
}

void USSCWealth::BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount, FName _ObjName, FName _FunName, TArray<FTransform> _SpawnTransforms)
{
	FWealthClassEntry* ClassEntry = GetWealthClassSingleEntry(_WealthName);
	if (!ClassEntry)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "UClass Asset is Empty" << SSCHelper::Endl();
		return;
	}
	if (!ClassEntry->ClassPtr.ToSoftObjectPath().IsValid())
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "UClass Path is Not Valid" << SSCHelper::Endl();
		return;
	}
	//判断资源类型
	if (Type != ClassEntry->ClassType)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "Wrong Type" << SSCHelper::Endl();
		return;
	}
	if ((ClassEntry->ClassType == EWealthClassType::Actor && _SpawnTransforms.Num() != 1 && _SpawnTransforms.Num() != _Amount) || _Amount ==0)
	{
		SSCHelper::Debug() << _ObjName << "--->" << _WealthName << "--->" << "Wrong Spawn Number" << SSCHelper::Endl();
		return;
	}
	if (ClassEntry->ObjInst)
	{
		MultiClassEntryLoadNodeArray.Push(new FMultiClassEntryLoadNode(ClassEntry, _ObjName, _FunName, _Amount, _SpawnTransforms));
	}
	else
	{
		TSharedPtr<FStreamableHandle> LoadHandle = WealthLoader.RequestAsyncLoad(ClassEntry->ClassPtr.ToSoftObjectPath());

		
		MultiClassEntryLoadNodeArray.Push(new FMultiClassEntryLoadNode(LoadHandle,ClassEntry, _ObjName, _FunName, _Amount, _SpawnTransforms));
	}
}

void USSCWealth::DealSingleObjectEntryLoadArray()
{
	TArray<FSingleObjectEntryLoadNode*> CompletedNodeArray;
	for (int i = 0; i < SingleObjectEntryLoadArray.Num(); ++i)
	{
		if (SingleObjectEntryLoadArray[i]->LoaderHandle->HasLoadCompleted())
		{
			SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjInst = SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjectPath.ResolveObject();
			BackWealthObjectSingle(_ModuleIndex, SingleObjectEntryLoadArray[i]->ObjectName, SingleObjectEntryLoadArray[i]->FuncName
				, SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjName, SingleObjectEntryLoadArray[i]->WealthObjectEntry->ObjInst);
			CompletedNodeArray.Push(SingleObjectEntryLoadArray[i]);
		}
	}

	for (int i = 0; i < CompletedNodeArray.Num(); ++i)
	{
		SingleObjectEntryLoadArray.Remove(CompletedNodeArray[i]);
		delete CompletedNodeArray[i];
	}
}

void USSCWealth::DealKindObjectEntryLoadArray()
{
	TArray<FKindObjectEntryLoadNode*> CompleteNodes;
	for (int i = 0; i < KindObjectEntryLoadArray.Num(); ++i)
	{
		if (KindObjectEntryLoadArray[i]->LoaderHandle->HasLoadCompleted())
		{
			TArray<FName> Names;
			TArray<UObject*> Objects;

			for (int j = 0; j < KindObjectEntryLoadArray[i]->LoadEntrys.Num(); ++j)
			{
				Names.Push(KindObjectEntryLoadArray[i]->LoadEntrys[j]->ObjName);
				Objects.Push(KindObjectEntryLoadArray[i]->LoadEntrys[j]->ObjInst);
			}

			for (int j = 0; j < KindObjectEntryLoadArray[i]->UnLoadEntrys.Num(); ++j)
			{
				KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjInst = KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjectPath.ResolveObject();
				Names.Push(KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjName);
				Objects.Push(KindObjectEntryLoadArray[i]->UnLoadEntrys[j]->ObjInst);
			}

			BackWealthObjectKind(_ModuleIndex, KindObjectEntryLoadArray[i]->ObjectName, KindObjectEntryLoadArray[i]->FuncName, Names, Objects);
			CompleteNodes.Push(KindObjectEntryLoadArray[i]);
		}
	}

	for (int i = 0; i < CompleteNodes.Num(); ++i)
	{
		KindObjectEntryLoadArray.Remove(CompleteNodes[i]);
		delete  CompleteNodes[i];
	}
}

void USSCWealth::DealSingleClassEntryLoadArray()
{
	TArray<FSingleClassEntryLoadNode*> CompeletedNodes;
	for (int i = 0; i < SingleClassEntryLoadArray.Num(); ++i)
	{
		if (SingleClassEntryLoadArray[i]->LoaderHandle->HasLoadCompleted())
		{
			SingleClassEntryLoadArray[i]->WealthClassEntry->ObjInst = Cast<UClass>(SingleClassEntryLoadArray[i]->WealthClassEntry->ClassPtr.ToSoftObjectPath().ResolveObject());
			if (SingleClassEntryLoadArray[i]->isLoadClass)
			{
				//返回UCLASS 给请求对象
				BackWealthClassSingle(_ModuleIndex, SingleClassEntryLoadArray[i]->ObjectName, SingleClassEntryLoadArray[i]->FuncName,
					SingleClassEntryLoadArray[i]->WealthClassEntry->ObjName, SingleClassEntryLoadArray[i]->WealthClassEntry->ObjInst);
			}
			else
			{
				//根据UCLASS 直接创建实列
				if (SingleClassEntryLoadArray[i]->WealthClassEntry->ClassType == EWealthClassType::Object)
				{
					UObject* Inst = NewObject<UObject>(this, SingleClassEntryLoadArray[i]->WealthClassEntry->ObjInst);
					Inst->AddToRoot();
					BackObject(_ModuleIndex, SingleClassEntryLoadArray[i]->ObjectName, SingleClassEntryLoadArray[i]->FuncName, 
						SingleClassEntryLoadArray[i]->WealthClassEntry->ObjName, Inst);
				}
				else if (SingleClassEntryLoadArray[i]->WealthClassEntry->ClassType == EWealthClassType::Actor)
				{
					AActor* Inst = GetModuleWorld()->SpawnActor<AActor>(SingleClassEntryLoadArray[i]->WealthClassEntry->ObjInst, SingleClassEntryLoadArray[i]->SpawnTransform);
						BackActor(_ModuleIndex, SingleClassEntryLoadArray[i]->ObjectName, SingleClassEntryLoadArray[i]->FuncName,
							SingleClassEntryLoadArray[i]->WealthClassEntry->ObjName, Inst);
				}
				else if (SingleClassEntryLoadArray[i]->WealthClassEntry->ClassType == EWealthClassType::Widget)
				{
					UUserWidget* Inst = CreateWidget<UUserWidget>(GetModuleWorld(), SingleClassEntryLoadArray[i]->WealthClassEntry->ObjInst);
					AutoCreateWidgetData.Push(Inst);
					BackWidget(_ModuleIndex, SingleClassEntryLoadArray[i]->ObjectName, SingleClassEntryLoadArray[i]->FuncName,
						SingleClassEntryLoadArray[i]->WealthClassEntry->ObjName, Inst);
				}
			}
		
			
			
			CompeletedNodes.Push(SingleClassEntryLoadArray[i]);
		}
	}
	for (int i = 0; i < CompeletedNodes.Num(); ++i)
	{
		SingleClassEntryLoadArray.Remove(CompeletedNodes[i]);
		delete CompeletedNodes[i];
	}
}

void USSCWealth::DealKindClassEntryLoadArray()
{
	TArray<FKindClassEntryLoadNode*> CompleteNodes;
	for (int i = 0; i < KindClassEntryLoadArray.Num(); ++i)
	{
		if (KindClassEntryLoadArray[i]->LoaderHandle.IsValid() && KindClassEntryLoadArray[i]->LoaderHandle->HasLoadCompleted() && KindClassEntryLoadArray[i]->UnLoadEntrys.Num() > 0)
		{
			for (int j = 0; j < KindClassEntryLoadArray[i]->UnLoadEntrys.Num(); ++j)
			{
				KindClassEntryLoadArray[i]->UnLoadEntrys[j]->ObjInst = Cast<UClass>(KindClassEntryLoadArray[i]->UnLoadEntrys[j]->ClassPtr.ToSoftObjectPath().ResolveObject());
			}
			KindClassEntryLoadArray[i]->LoadEntrys.Append(KindClassEntryLoadArray[i]->UnLoadEntrys);
			KindClassEntryLoadArray[i]->UnLoadEntrys.Empty();
		}
		if (KindClassEntryLoadArray[i]->UnLoadEntrys.Num() == 0)
			{
				//加载Uclass 或者 生成资源
				if (KindClassEntryLoadArray[i]->isLoadClass)
				{
					TArray<FName> _Names;
					TArray<UClass*> _Classes;

					for (int j = 0; j < KindClassEntryLoadArray[i]->LoadEntrys.Num(); ++j)
					{
						_Names.Push(KindClassEntryLoadArray[i]->LoadEntrys[j]->ObjName);
						_Classes.Push(KindClassEntryLoadArray[i]->LoadEntrys[j]->ObjInst);
					}

					BackWealthClassKind(_ModuleIndex, KindClassEntryLoadArray[i]->ObjectName, KindClassEntryLoadArray[i]->FuncName, _Names, _Classes);
					CompleteNodes.Push(KindClassEntryLoadArray[i]);
				}
				else  //直接生成实例  从已加载资源取出
				{
					//每帧取出第一个 直到没有
					FWealthClassEntry* _WealthEntry = KindClassEntryLoadArray[i]->LoadEntrys[0];
					//移除
					KindClassEntryLoadArray[i]->LoadEntrys.RemoveAt(0);
					if (_WealthEntry->ClassType == EWealthClassType::Object)
					{
						UObject* Inst = NewObject<UObject>(this, _WealthEntry->ObjInst);
						Inst->AddToRoot();
						KindClassEntryLoadArray[i]->NameArray.Push(_WealthEntry->ObjName);
						KindClassEntryLoadArray[i]->ObjectsArray.Push(Inst);
						if (KindClassEntryLoadArray[i]->LoadEntrys.Num() == 0) //取完
						{
							BackObjectKind(_ModuleIndex, KindClassEntryLoadArray[i]->ObjectName, KindClassEntryLoadArray[i]->FuncName, KindClassEntryLoadArray[i]->NameArray
								, KindClassEntryLoadArray[i]->ObjectsArray);
							CompleteNodes.Push(KindClassEntryLoadArray[i]);
						}
					}
					else if (_WealthEntry->ClassType == EWealthClassType::Actor)
					{
						FTransform SpawnTransform = KindClassEntryLoadArray[i]->SpawnTransforms.Num() == 1 ? KindClassEntryLoadArray[i]->SpawnTransforms[0] :
							KindClassEntryLoadArray[i]->SpawnTransforms[KindClassEntryLoadArray[i]->ActorArray.Num()];

						AActor* Inst = GetModuleWorld()->SpawnActor<AActor>(_WealthEntry->ObjInst, SpawnTransform);
					
						KindClassEntryLoadArray[i]->NameArray.Push(_WealthEntry->ObjName);
						KindClassEntryLoadArray[i]->ActorArray.Push(Inst);
						if (KindClassEntryLoadArray[i]->LoadEntrys.Num() == 0) //取完
						{
							BackActorKind(_ModuleIndex, KindClassEntryLoadArray[i]->ObjectName, KindClassEntryLoadArray[i]->FuncName, KindClassEntryLoadArray[i]->NameArray
								, KindClassEntryLoadArray[i]->ActorArray);
							CompleteNodes.Push(KindClassEntryLoadArray[i]);
						}
					}
					else if (_WealthEntry->ClassType == EWealthClassType::Widget)
					{

						UUserWidget* Inst = CreateWidget<UUserWidget>(GetModuleWorld(), _WealthEntry->ObjInst);
						AutoCreateWidgetData.Push(Inst);
						KindClassEntryLoadArray[i]->NameArray.Push(_WealthEntry->ObjName);
						KindClassEntryLoadArray[i]->WidgetArray.Push(Inst);
						if (KindClassEntryLoadArray[i]->LoadEntrys.Num() == 0) //取完
						{
							BackWidgetKind(_ModuleIndex, KindClassEntryLoadArray[i]->ObjectName, KindClassEntryLoadArray[i]->FuncName, KindClassEntryLoadArray[i]->NameArray
								, KindClassEntryLoadArray[i]->WidgetArray);
							CompleteNodes.Push(KindClassEntryLoadArray[i]);
						}
					}
				}
				
			}	
		
	}

	for (int i = 0; i < CompleteNodes.Num(); ++i)
	{
		KindClassEntryLoadArray.Remove(CompleteNodes[i]);
		delete  CompleteNodes[i];
	}
}

void USSCWealth::DealMultiClassEntryLoadNodeArray()
{
	TArray<FMultiClassEntryLoadNode*> CompeletedNodes;
	for (int i = 0; i < MultiClassEntryLoadNodeArray.Num(); ++i)
	{
		if (!MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjInst)
		{
			if (MultiClassEntryLoadNodeArray[i]->LoaderHandle->HasLoadCompleted())
			{
				MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjInst = Cast<UClass>(MultiClassEntryLoadNodeArray[i]->LoaderHandle->GetLoadedAsset());
				
			}
				
		}
		if (MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjInst)
		{
			//类型
			if (MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ClassType == EWealthClassType::Object)
			{
				UObject* Inst = NewObject<UObject>(this, MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjInst);
				Inst->AddToRoot();
				MultiClassEntryLoadNodeArray[i]->ObjectsArray.Push(Inst);
				if (MultiClassEntryLoadNodeArray[i]->ObjectsArray.Num() == MultiClassEntryLoadNodeArray[i]->Amount)
				{
					//全部生成
					BackObjectMulti(_ModuleIndex, MultiClassEntryLoadNodeArray[i]->ObjectName, MultiClassEntryLoadNodeArray[i]->FuncName,
						MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjName, MultiClassEntryLoadNodeArray[i]->ObjectsArray);
					CompeletedNodes.Push(MultiClassEntryLoadNodeArray[i]);
				}
			}
			else if (MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ClassType == EWealthClassType::Actor)
			{
				FTransform SpawnTransform = MultiClassEntryLoadNodeArray[i]->SpawnTransforms.Num() == 1 ? MultiClassEntryLoadNodeArray[i]->SpawnTransforms[0] :
					MultiClassEntryLoadNodeArray[i]->SpawnTransforms[MultiClassEntryLoadNodeArray[i]->ActorArray.Num()];

				AActor* Inst = GetModuleWorld()->SpawnActor<AActor>(MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjInst, SpawnTransform);
				MultiClassEntryLoadNodeArray[i]->ActorArray.Push(Inst);
				if (MultiClassEntryLoadNodeArray[i]->ActorArray.Num() == MultiClassEntryLoadNodeArray[i]->Amount)
				{
					//全部生成
					BackActorMulti(_ModuleIndex, MultiClassEntryLoadNodeArray[i]->ObjectName, MultiClassEntryLoadNodeArray[i]->FuncName,
						MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjName, MultiClassEntryLoadNodeArray[i]->ActorArray);
					CompeletedNodes.Push(MultiClassEntryLoadNodeArray[i]);
				}
			}
			else if (MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ClassType == EWealthClassType::Widget)
			{
				UUserWidget* Inst = CreateWidget<UUserWidget>(GetModuleWorld(), MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjInst);
				AutoCreateWidgetData.Push(Inst);
			
				MultiClassEntryLoadNodeArray[i]->WidgetArray.Push(Inst);
				if (MultiClassEntryLoadNodeArray[i]->WidgetArray.Num() == MultiClassEntryLoadNodeArray[i]->Amount) //取完
				{
					BackWidgetMulti(_ModuleIndex, MultiClassEntryLoadNodeArray[i]->ObjectName, MultiClassEntryLoadNodeArray[i]->FuncName, MultiClassEntryLoadNodeArray[i]->WealthClassEntry->ObjName
						, MultiClassEntryLoadNodeArray[i]->WidgetArray);
					CompeletedNodes.Push(MultiClassEntryLoadNodeArray[i]);
				}
			}

		}
		
	}
	for (int i = 0; i < CompeletedNodes.Num(); ++i)
	{
		MultiClassEntryLoadNodeArray.Remove(CompeletedNodes[i]);
		delete CompeletedNodes[i];
	}
}
