// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCObjectInterface.h"


UWorld* ISSCObjectInterface::GetCurrentWorld() const
{
	if (Dirver) return Dirver->GetWorld();
	return nullptr;
}

// Add default functionality here for any ISSCObjectInterface functions that are not pure virtual.

void ISSCObjectInterface::RegisterToModule(FName ModuleName, FName ObjName /*= FName() */, FName ClsName /*= FName()*/)
{
	if (Dirver && Module) return;
	if (ModuleName.IsNone()) return;
	if (!ObjName.IsNone()) ObjectName = ObjName;
	if (!ClsName.IsNone()) ClassName = ClsName;
	
	Body = Cast<UObject>(this);
	Dirver = USSCCommon::Get()->GetDirver();
	if (Dirver)
	{
		ModuleIndex = SSCHelper::GetEnumIndexFromName(Dirver->ModuleType.ToString(),ModuleName);
		if (ModuleIndex < 0)
		{
			SSCHelper::Debug() << GetObjectName()<< "Cant Find Module-->" << ModuleName << SSCHelper::Endl();
		}
		if (!Dirver->RegisterObject(this))
		{
			SSCHelper::Debug() << GetObjectName()<< "Register to Module Failed" <<  SSCHelper::Endl();
		}
	}
	else
	{
		SSCHelper::Debug() << GetObjectName()<< "Cant Dirver Failed" <<  SSCHelper::Endl();
	}
}

void ISSCObjectInterface::RegisterToModule(int32 _ModuleIndex, FName ObjName /*= FName()*/, FName ClsName /*= FName()*/)
{
	if (Dirver && Module) return;
	if (!ObjName.IsNone()) ObjectName = ObjName;
	if (!ClsName.IsNone()) ClassName = ClsName;

	Body = Cast<UObject>(this);
	Dirver = USSCCommon::Get()->GetDirver();
	if (Dirver)
	{
		ModuleIndex = _ModuleIndex;
		if (ModuleIndex < 0)
		{
			SSCHelper::Debug() << GetObjectName() << "Cant Find Module-->" << ModuleIndex << SSCHelper::Endl();
		}
		if (!Dirver->RegisterObject(this))
		{
			SSCHelper::Debug() << GetObjectName() << "Register to Module Failed" << SSCHelper::Endl();
		}
	}
	else
	{
		SSCHelper::Debug() << GetObjectName() << "Cant Dirver Failed" << SSCHelper::Endl();
	}
}

FName ISSCObjectInterface::GetObjectName()
{
	if (!ObjectName.IsNone())
	{
		return ObjectName;
	}
	else
	{
		ObjectName = Body->GetFName();
		return ObjectName;
	}
}

FName ISSCObjectInterface::GetClassName()
{
	if (!ClassName.IsNone())
	{
		return ClassName;
	}
	else
	{
		ClassName = Body->GetClass()->GetFName();
		return ClassName;
	}
}

int32 ISSCObjectInterface::GetModuleIndex() const
{
	return ModuleIndex;
}

UObject* ISSCObjectInterface::GetBody() const
{
	return Body;
}

void ISSCObjectInterface::SetModuel(USSCModule* InModuel)
{
	Module = InModuel;
}

void ISSCObjectInterface::ModelInit()
{

}

void ISSCObjectInterface::ModelLoading()
{

}

void ISSCObjectInterface::ModelRegsiter()
{

}

void ISSCObjectInterface::ModelEnable()
{

}

void ISSCObjectInterface::ModelTick(float DeltaSeconds)
{

}

void ISSCObjectInterface::ModelDisable()
{

}

void ISSCObjectInterface::ModelUnRegister()
{

}

void ISSCObjectInterface::ModelUnLoading()
{

}

void ISSCObjectInterface::ModelRelease()
{
	StopAllCoroutine();
	StopAllInvoke();
	UnBindKeys();
}

bool ISSCObjectInterface::ActiveLife()
{
	switch (LifeState)
	{
	case EBaseObjectLife::None:
		ModelInit();
		LifeState = EBaseObjectLife::Init;
		break;
	case EBaseObjectLife::Init:
		ModelLoading();
		LifeState = EBaseObjectLife::Loading;
		break;
	case EBaseObjectLife::Loading:
		ModelRegsiter();
		LifeState = EBaseObjectLife::Register;
		break;
	case EBaseObjectLife::Register:
		ModelEnable();
		LifeState = EBaseObjectLife::Enable;
		RunState = EBaseObjectState::Stable;
		return true;
	
	}

	return false;
}

bool ISSCObjectInterface::DestroyLife()
{
	switch (LifeState)
	{
	case EBaseObjectLife::Enable:
		ModelDisable();
		LifeState = EBaseObjectLife::Disable;
		RunState = EBaseObjectState::Destroy;
		break;
	case EBaseObjectLife::Disable:
		ModelUnRegister();
		LifeState = EBaseObjectLife::UnRegister;
		RunState = EBaseObjectState::Destroy;
		break;
	case EBaseObjectLife::UnRegister:
		ModelUnLoading();
		LifeState = EBaseObjectLife::UnLoading;
		return true;

	}

	return false;
}

void ISSCObjectInterface::OnEnable()
{
	LifeState = EBaseObjectLife::Enable;
}

void ISSCObjectInterface::OnDisable()
{
	LifeState = EBaseObjectLife::Disable;
}

void ISSCObjectInterface::DestroySelf()
{
	Module->DestroyObject(GetObjectName());
}

void ISSCObjectInterface::ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* Parm)
{
	if (Agrement.ModuleIndex == ModuleIndex)
	{
		Module->ProcessModuleReflectFuncEvnt(Agrement, Parm);
	}
	else
	{
		Dirver->ProcessModuleReflectFuncEvnt(Agrement, Parm);
	}
}

void ISSCObjectInterface::ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* Parm)
{
	if (Agrement.ModuleIndex == ModuleIndex)
	{
		Module->ProcessObjectReflectFuncEvnt(Agrement, Parm);
	}
	else
	{
		Dirver->ProcessObjectReflectFuncEvnt(Agrement, Parm);
	}
}

bool ISSCObjectInterface::StartCoroutine(FName CoroName, FCoroStack* CoroTask)
{
	return Module->StartCoroutine(GetObjectName(), CoroName, CoroTask);
}

bool ISSCObjectInterface::StopCoroutine(FName CoroName)
{
	return Module->StopCoroutine(GetObjectName(), CoroName);
}

void ISSCObjectInterface::StopAllCoroutine()
{
	Module->StopAllCoroutine(GetObjectName());
}

bool ISSCObjectInterface::StopInvoke(FName InvokeName)
{
	return Module->StopInvoke(GetObjectName(), InvokeName);
}

void ISSCObjectInterface::StopAllInvoke()
{
	Module->StopAllInvoke(GetObjectName());
}

void ISSCObjectInterface::UnBindKeys()
{
	Module->UnBindKeys(GetObjectName());
}

FWealthURL* ISSCObjectInterface::GetWealthURL(FName _ObjName)
{
	return Module->GetWealthURL(_ObjName);
}

void ISSCObjectInterface::GetWealthURL(FName _KindName, TArray<FWealthURL*>& OutWealthURL)
{
	Module->GetWealthURL(_KindName, OutWealthURL);
}

FWealthObjectEntry* ISSCObjectInterface::GetWealthObjectSingleEntry(FName WealthName)
{
	return Module->GetWealthObjectSingleEntry(WealthName);
}

TArray<FWealthObjectEntry*> ISSCObjectInterface::GetWealthObjectKindEntry(FName WealthKindName)
{
	return Module->GetWealthObjectKindEntry(WealthKindName);
}

FWealthClassEntry* ISSCObjectInterface::GetWealthClassSingleEntry(FName WealthName)
{
	return Module->GetWealthClassSingleEntry(WealthName);
}

TArray<FWealthClassEntry*> ISSCObjectInterface::GetWealthClassKindEntry(FName WealthKindName)
{
	return Module->GetWealthClassKindEntry(WealthKindName);
}

void ISSCObjectInterface::LoadObjectEntry(FName _WealthName, FName _FunName)
{
	Module->LoadObjectEntry(_WealthName, GetObjectName(), _FunName);
}

void ISSCObjectInterface::LoadObjectKindEntry(FName _WealthKindName, FName _FunName)
{
	Module->LoadObjectKindEntry(_WealthKindName, GetObjectName(), _FunName);
}

void ISSCObjectInterface::LoadClassEntry(FName _WealthName, FName _FunName)
{
	Module->LoadClassEntry(_WealthName, GetObjectName(), _FunName);
}

void ISSCObjectInterface::LoadClassKindEntry(FName _WealthKindName, FName _FunName)
{
	Module->LoadClassKindEntry(_WealthKindName, GetObjectName(), _FunName);
}

void ISSCObjectInterface::BuildSinglClassWealth(EWealthClassType Type, FName _WealthName, FName _FunName)
{
	Module->BuildSinglClassWealth(Type, _WealthName, GetObjectName(), _FunName, FTransform::Identity);
}

void ISSCObjectInterface::BuildSinglClassWealth(EWealthClassType Type, FName _WealthName, FName _FunName, FTransform _SpawnTransform)
{
	Module->BuildSinglClassWealth(Type, _WealthName, GetObjectName(), _FunName, _SpawnTransform);
}

void ISSCObjectInterface::BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _FunName)
{
	Module->BuildKindClassWealth(Type, _WealthKindName, GetObjectName(), _FunName, TArray<FTransform>{FTransform::Identity });
}

void ISSCObjectInterface::BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _FunName, FTransform _SpawnTransforms)
{
	Module->BuildKindClassWealth(Type, _WealthKindName, GetObjectName(), _FunName, TArray<FTransform>{_SpawnTransforms });
}

void ISSCObjectInterface::BuildKindClassWealth(EWealthClassType Type, FName _WealthKindName, FName _FunName, TArray<FTransform> _SpawnTransforms)
{
	Module->BuildKindClassWealth(Type, _WealthKindName, GetObjectName(), _FunName, _SpawnTransforms);
}

void ISSCObjectInterface::BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount, FName _FunName)
{
	Module->BuildMultiClassWealth(Type, _WealthName, _Amount, GetObjectName(), _FunName, TArray<FTransform>{FTransform::Identity});
}

void ISSCObjectInterface::BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount, FName _FunName, FTransform _SpawnTransforms)
{
	Module->BuildMultiClassWealth(Type, _WealthName, _Amount, GetObjectName(), _FunName, TArray<FTransform>{_SpawnTransforms});
}

void ISSCObjectInterface::BuildMultiClassWealth(EWealthClassType Type, FName _WealthName, int32 _Amount, FName _FunName, TArray<FTransform> _SpawnTransforms)
{
	Module->BuildMultiClassWealth(Type, _WealthName, _Amount, GetObjectName(), _FunName, _SpawnTransforms);
}
