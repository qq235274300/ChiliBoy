// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCModel.h"
#include "SSCObjectInterface.h"

void USSCModel::ModuleInit()
{

}

void USSCModel::ModuleBeginPlay()
{
}

void USSCModel::ModuleTick(float DeltaSeconds)
{
	for (int i = 0; i < ObjectTickArray.Num(); ++i)
	{
		ObjectTickArray[i]->ModelTick(DeltaSeconds);
	}
	TArray<ISSCObjectInterface*> ObjectArray;
	
	for (int i = 0; i < ObjectActiveArray.Num(); ++i)
	{
		if (ObjectActiveArray[i]->ActiveLife())
		{
			ObjectArray.Push(ObjectActiveArray[i]);
		}
	}
	for (int i = 0; i < ObjectArray.Num(); ++i)
	{
		ObjectActiveArray.Remove(ObjectArray[i]);
		if (ObjectArray[i]->bIsAllowTick)
		{
			ObjectTickArray.Push(ObjectArray[i]);
		}
	}

	/*******************************************/

	for (int i = 0; i < ObjectReleaseArray.Num(); ++i)
	{
		ObjectReleaseArray[i]->ModelRelease();
	}
	ObjectReleaseArray.Empty();

	/*******************************************/

	ObjectArray.Empty();
	for (int i = 0; i < ObjectDestroyArray.Num(); ++i)
	{
		if (ObjectDestroyArray[i]->DestroyLife())
		{
			ObjectReleaseArray.Push(ObjectDestroyArray[i]);
			ObjectArray.Push(ObjectDestroyArray[i]);
			FName objName = ObjectDestroyArray[i]->GetObjectName();
			FName objClsName = ObjectDestroyArray[i]->GetClassName();
			if (ObjectGroup.Contains(objName))
			{
				ObjectGroup.Remove(objName);
			}
			if (ObjectClassGroup.Find(objClsName)->Contains(ObjectDestroyArray[i]))
			{
				ObjectClassGroup.Find(objClsName)->Remove(ObjectDestroyArray[i]);
				if (ObjectClassGroup.Find(objClsName)->Num() == 0)
				{
					ObjectClassGroup.Remove(objClsName);
				}
			}
		}
	}

	for (int i = 0; i < ObjectArray.Num(); ++i)
	{
		ObjectDestroyArray.Remove(ObjectArray[i]);
	}
	/*******************************************/
	ObjectArray.Empty();
	for (int i = 0; i < ObjectPreDestroyArray.Num(); ++i)
	{
		if (ObjectPreDestroyArray[i]->RunState == EBaseObjectState::Stable)
		{
			ObjectArray.Push(ObjectPreDestroyArray[i]);
		}
	}

	for (int i = 0; i < ObjectArray.Num(); ++i)
	{
		ObjectPreDestroyArray.Remove(ObjectArray[i]);
		ObjectDestroyArray.Push(ObjectArray[i]);
		ObjectTickArray.Remove(ObjectArray[i]);
	}
	/*******************************************/
	
}

void USSCModel::RegisterObject(ISSCObjectInterface* InObject)
{
	FName objName = InObject->GetObjectName();
	FName objClassName = InObject->GetClassName();
	if (ObjectGroup.Contains(objName))
	{
		SSCHelper::Debug() << "Object Repeated Register -->" << objName << SSCHelper::Endl();
	}
	else
	{
		ObjectGroup.Add(objName, InObject);
		if (ObjectClassGroup.Contains(objClassName)) 
		{
			ObjectClassGroup.Find(objClassName)->Push(InObject);
		}
		else
		{
			TArray<ISSCObjectInterface*> ObjArray;
			ObjectClassGroup.Add(objClassName, ObjArray);
			ObjectClassGroup.Find(objClassName)->Push(InObject);
			
		}

		ObjectActiveArray.Push(InObject);
	}
}

void USSCModel::DestroyObject(FName InObjectName)
{
	ISSCObjectInterface* tempObject;
	if (ObjectGroup.Contains(InObjectName))
	{
		tempObject = *ObjectGroup.Find(InObjectName);

		if (!ObjectPreDestroyArray.Contains(tempObject) && !ObjectDestroyArray.Contains(tempObject))
		{
			switch (tempObject->RunState)
			{
			case  EBaseObjectState::Active:
				ObjectPreDestroyArray.Push(tempObject);
				break;
			case  EBaseObjectState::Stable:
				ObjectDestroyArray.Push(tempObject);
				ObjectTickArray.Remove(tempObject);
				break;
			}
		}
	}


}

void USSCModel::DestroyObject(EAgreementType Type, TArray<FName> TargetObjectNameArray)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	GetObjectByAgreement(Type, TargetObjectNameArray, tmpObjectArray);
	
	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		if (!ObjectPreDestroyArray.Contains(tmpObjectArray[i]) &&  !ObjectDestroyArray.Contains(tmpObjectArray[i]))
		{
			switch (tmpObjectArray[i]->RunState)
			{
			case EBaseObjectState::Active :
				ObjectPreDestroyArray.Push(tmpObjectArray[i]);
				break;
			case EBaseObjectState::Stable :
				ObjectDestroyArray.Push(tmpObjectArray[i]);
				ObjectTickArray.Remove(tmpObjectArray[i]);
				break;
			}
		}
	}
}

void USSCModel::EnableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	GetObjectByAgreement(Type, TargetObjectNameArray, tmpObjectArray);

	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		if (tmpObjectArray[i]->RunState == EBaseObjectState::Stable && tmpObjectArray[i]->LifeState == EBaseObjectLife::Disable)
		{
			tmpObjectArray[i]->OnEnable();
		}
	}
}

void USSCModel::DisableObject(EAgreementType Type, TArray<FName> TargetObjectNameArray)
{
	TArray<ISSCObjectInterface*> tmpObjectArray;
	GetObjectByAgreement(Type, TargetObjectNameArray, tmpObjectArray);

	for (int i = 0; i < tmpObjectArray.Num(); ++i)
	{
		if (tmpObjectArray[i]->RunState == EBaseObjectState::Stable && tmpObjectArray[i]->LifeState == EBaseObjectLife::Enable)
		{
			tmpObjectArray[i]->OnDisable();
		}
	}

}

void USSCModel::GetSelfObject(TArray<FName> TargetObjectNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	for (int i = 0; i < TargetObjectNameArray.Num(); ++i)
	{
		if (ObjectGroup.Contains(TargetObjectNameArray[i]))
		{
			TargetObjectArray.Push(*ObjectGroup.Find(TargetObjectNameArray[i]));
		}
	}
}

int32 USSCModel::GetOtherObject(TArray<FName> TargetObjectNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	for (TMap<FName, ISSCObjectInterface*>::TIterator it(ObjectGroup); it; ++it)
	{
		bool bFind = false;
		for (int i = 0; i < TargetObjectNameArray.Num(); ++i)
		{
			if (TargetObjectNameArray[i].IsEqual(it->Key))
			{
				bFind = true;
				break;
			}		
		}
		if (!bFind)
		{
			TargetObjectArray.Push(it->Value);
		}
	}
	return ObjectGroup.Num();
}

int32 USSCModel::GetClassOtherObject(TArray<FName> TargetObjectNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	if (TargetObjectNameArray.Num() <= 0) return 0;
	FName tmpClassName = (*ObjectGroup.Find(TargetObjectNameArray[0]))->GetClassName();
	int32 tmpwClassObjectNum = (*ObjectClassGroup.Find(tmpClassName)).Num();
	for (TArray<ISSCObjectInterface*>::TIterator it(*ObjectClassGroup.Find(tmpClassName)); it; ++it)
	{
		FName tmpObjectName = (*it)->GetObjectName();
		bool bFind = false;
		for (int i = 0; i < TargetObjectNameArray.Num(); ++i)
		{
			if (TargetObjectNameArray[i].IsEqual(tmpObjectName))
			{
				bFind = true;
				break;
			}
		}

		if (!bFind)
		{
			TargetObjectArray.Push(*it);
		}
	}
	return tmpwClassObjectNum;	
}

void USSCModel::GetSelfClass(TArray<FName> TargetClassNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	for (int i = 0; i < TargetClassNameArray.Num(); ++i)
	{
		if (!ObjectClassGroup.Contains(TargetClassNameArray[i]))
		{
			continue;
		}
		else
		{
			TargetObjectArray.Append(*ObjectClassGroup.Find(TargetClassNameArray[i]));
		}
	}
}

void USSCModel::GetOtherClass(TArray<FName> TargetClassNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	for (TMap<FName,TArray<ISSCObjectInterface*>>::TIterator it(ObjectClassGroup); it; ++it)
	{
		if (!TargetClassNameArray.Contains((*it).Key))
		{
			TargetObjectArray.Append((*it).Value);
		}
		
	}
		
}

void USSCModel::GetAllObject(TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	ObjectGroup.GenerateValueArray(TargetObjectArray);
}

void USSCModel::GetObjectByAgreement(EAgreementType _Agreement, TArray<FName> TargetNameArray, TArray<ISSCObjectInterface*>& TargetObjectArray)
{
	switch (_Agreement)
	{
	case EAgreementType::SelfObject:
		GetSelfObject(TargetNameArray, TargetObjectArray);
		break;
	case EAgreementType::OtherObject:
		GetOtherObject(TargetNameArray, TargetObjectArray);
		break;
	case EAgreementType::ClassOtherObject:
		GetClassOtherObject(TargetNameArray, TargetObjectArray);
		break;
	case EAgreementType::SelfClass:
		GetSelfClass(TargetNameArray, TargetObjectArray);
		break;
	case EAgreementType::OtherClass:
		GetOtherClass(TargetNameArray, TargetObjectArray);
		break;
	case EAgreementType::ALL:
		GetAllObject(TargetObjectArray);
		break;
	
	}
}
