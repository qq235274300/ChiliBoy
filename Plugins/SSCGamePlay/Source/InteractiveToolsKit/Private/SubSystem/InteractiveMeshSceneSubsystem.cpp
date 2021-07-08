// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/InteractiveMeshSceneSubsystem.h"
#include "Materials/Material.h"

#define LOCTEXT_NAMESPACE "UInteractiveMeshSceneSubsystem"

UInteractiveMeshSceneSubsystem* UInteractiveMeshSceneSubsystem::InteractiveMeshSceneSubsystem = nullptr;

void UInteractiveMeshSceneSubsystem::InitSubSysytem(UInteractiveMeshSceneSubsystem* InInteractiveMeshSceneSubSystem)
{
	check(InInteractiveMeshSceneSubSystem);
	InteractiveMeshSceneSubsystem = InInteractiveMeshSceneSubSystem;

	UMaterial* DefaultObjectMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/RuntimeToolsFrameworkMaterials/DefaultObjectMaterial"));
	InteractiveMeshSceneSubsystem->StandardMaterial = (DefaultObjectMaterial) ? DefaultObjectMaterial : UMaterial::GetDefaultMaterial(MD_Surface);

	UMaterial* SelectionMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/RuntimeToolsFrameworkMaterials/SelectedMaterial"));
	InteractiveMeshSceneSubsystem->SelectedMaterial = (SelectionMaterial) ? SelectionMaterial : UMaterial::GetDefaultMaterial(MD_Surface);

	UMaterial* WireframeMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/RuntimeToolsFrameworkMaterials/WireframeMaterial"));
	WireframeMaterial = (WireframeMaterial) ? WireframeMaterial : UMaterial::GetDefaultMaterial(MD_Surface);
	InteractiveMeshSceneSubsystem->WireframeMaterial = WireframeMaterial;
	GEngine->WireframeMaterial = WireframeMaterial;
}

UInteractiveMeshSceneSubsystem* UInteractiveMeshSceneSubsystem::Get()
{
	check(InteractiveMeshSceneSubsystem);
	return InteractiveMeshSceneSubsystem;
}

void UInteractiveMeshSceneSubsystem::Deinitialize()
{
	InteractiveMeshSceneSubsystem = nullptr;
}

void UInteractiveMeshSceneSubsystem::SetTransactionAPI(IToolsContextTransactionsAPI* IntransactionAPI)
{
	check(IntransactionAPI);
	transactionAPI = IntransactionAPI;
}


bool UInteractiveMeshSceneSubsystem::DeleteSelectedSceneObjects()
{
	return DeleteSelectedSceneObjects(nullptr);
}

bool UInteractiveMeshSceneSubsystem::DeleteSelectedSceneObjects(AActor* SkipActor)
{
	if (SelectedSceneObjects.Num() == 0) return false;

	if (transactionAPI)
	{
		transactionAPI->BeginUndoTransaction(LOCTEXT("DeleteSelectedObjectsChange", "Delete Objects"));
	}

	TArray<UInteractiveMeshSceneObject*> DeleteObjects = SelectedSceneObjects;

	BeginSelectionChange();
	SelectedSceneObjects.Reset();
	EndSelectionChange();

	for (UInteractiveMeshSceneObject* SceneObject : DeleteObjects)
	{
		if (SceneObject->GetActor() == SkipActor)
		{
			continue;
		}

		RemoveSceneObjectInternal(SceneObject, true);

		if (transactionAPI)
		{
			TUniquePtr<FAddRemoveSceneObjectChange> RemoveChange = MakeUnique<FAddRemoveSceneObjectChange>();
			RemoveChange->SceneObject = SceneObject;
			RemoveChange->bAdded = false;
			// use SceneObject as target so that transaction will keep it from being GC'd
			transactionAPI->AppendChange(SceneObject, MoveTemp(RemoveChange), LOCTEXT("RemoveObjectChange", "Delete SceneObject"));
		}
	}

	if (transactionAPI)
	{
		transactionAPI->EndUndoTransaction();
	}

	MeshSceneSelectionChangeEvnt.Broadcast(this);
	return true;
}

TArray<UInteractiveMeshSceneObject*> UInteractiveMeshSceneSubsystem::GetInteractiveMeshSceneObjects() const
{
	return InteractiveMeshSceneObjects;
}

void UInteractiveMeshSceneSubsystem::ClearSelection()
{
	if (SelectedSceneObjects.Num() > 0)
	{
		BeginSelectionChange();

		for (UInteractiveMeshSceneObject* SO : SelectedSceneObjects)
		{
			SO->ClearHighlightMaterial();
		}
		SelectedSceneObjects.Reset();

		EndSelectionChange();
		MeshSceneSelectionChangeEvnt.Broadcast(this);
	}
}

void UInteractiveMeshSceneSubsystem::SetSelected(UInteractiveMeshSceneObject* SceneObject, bool bDeSelect /*= false*/, bool bDeSelectOthers /*= true*/)
{
	if (bDeSelect)
	{
		if (SelectedSceneObjects.Contains(SceneObject))
		{
			BeginSelectionChange();
			SelectedSceneObjects.Remove(SceneObject);
			SceneObject->ClearHighlightMaterial();
			EndSelectionChange();
			MeshSceneSelectionChangeEvnt.Broadcast(this);
		}
	}
	else
	{
		BeginSelectionChange();

		bool bIsSelected = SelectedSceneObjects.Contains(SceneObject);
		if (bDeSelectOthers)
		{
			for (UInteractiveMeshSceneObject* SO : SelectedSceneObjects)
			{
				if (SO != SceneObject)
				{
					SO->ClearHighlightMaterial();
				}
			}
			SelectedSceneObjects.Reset();
		}
		if (bIsSelected == false)
		{
			SceneObject->SetToHighlightMaterial(this->SelectedMaterial);
		}
		SelectedSceneObjects.Add(SceneObject);

		EndSelectionChange();
		MeshSceneSelectionChangeEvnt.Broadcast(this);
	}
}

void UInteractiveMeshSceneSubsystem::ToggleSelected(UInteractiveMeshSceneObject* SceneObject)
{
	BeginSelectionChange();

	if (SelectedSceneObjects.Contains(SceneObject))
	{
		SelectedSceneObjects.Remove(SceneObject);
		SceneObject->ClearHighlightMaterial();
	}
	else
	{
		SelectedSceneObjects.Add(SceneObject);
		SceneObject->SetToHighlightMaterial(this->SelectedMaterial);
	}

	EndSelectionChange();
	MeshSceneSelectionChangeEvnt.Broadcast(this);
}

void UInteractiveMeshSceneSubsystem::SetSelection(const TArray<UInteractiveMeshSceneObject*>& SceneObjects)
{
	BeginSelectionChange();
	SetSelectionInternal(SceneObjects);
	EndSelectionChange();
}

UInteractiveMeshSceneObject* UInteractiveMeshSceneSubsystem::FindNearestHitObject(FVector RayOrigin, FVector RayDirection, FVector& WorldHitPoint, float& HitDistance, int& NearestTriangle, FVector& TriBaryCoords, float MaxDistance /*= 0*/)
{
	UInteractiveMeshSceneObject* FoundHit = nullptr;
	float MinHitDistance = TNumericLimits<float>::Max();

	for (UInteractiveMeshSceneObject* SO : InteractiveMeshSceneObjects)
	{
		FVector HitPoint, BaryCoords;
		float HitDist;
		int32 NearestTri;
		if (SO->IntersectRay(RayOrigin, RayDirection, HitPoint, HitDist, NearestTri, BaryCoords, MaxDistance))
		{
			if (HitDist < MinHitDistance)
			{
				MinHitDistance = HitDist;
				WorldHitPoint = HitPoint;
				HitDistance = HitDist;
				NearestTriangle = NearestTri;
				TriBaryCoords = BaryCoords;
				FoundHit = SO;
			}
		}
	}
	return FoundHit;
}

void UInteractiveMeshSceneSubsystem::AddSceneObjectInternal(UInteractiveMeshSceneObject* Object, bool bIsUndoRedo)
{
	InteractiveMeshSceneObjects.Add(Object);
	if (bIsUndoRedo)
	{
		Object->GetActor()->RegisterAllComponents();
	}
}

void UInteractiveMeshSceneSubsystem::RemoveSceneObjectInternal(UInteractiveMeshSceneObject* Object, bool bIsUndoRedo)
{
	check(InteractiveMeshSceneObjects.Contains(Object));
	InteractiveMeshSceneObjects.Remove(Object);
	Object->GetActor()->UnregisterAllComponents(true);
}

void UInteractiveMeshSceneSubsystem::SetSelectionInternal(const TArray<UInteractiveMeshSceneObject*>& SceneObjects)
{
	if (SelectedSceneObjects.Num() > 0)
	{
		for (UInteractiveMeshSceneObject* SO : SelectedSceneObjects)
		{
			SO->ClearHighlightMaterial();
		}
		SelectedSceneObjects.Reset();
	}

	for (UInteractiveMeshSceneObject* SO : SceneObjects)
	{
		if (SceneObjects.Contains(SO))
		{
			if (SelectedSceneObjects.Contains(SO) == false)
			{
				SelectedSceneObjects.Add(SO);
				SO->SetToHighlightMaterial(this->SelectedMaterial);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[URuntimeMeshSceneSubsystem::SetSelectionInternal] Tried to select non-existant SceneObject"));
		}
	}

	MeshSceneSelectionChangeEvnt.Broadcast(this);
}

void UInteractiveMeshSceneSubsystem::BeginSelectionChange()
{
	check(!ActiveSelectionChange);

	ActiveSelectionChange = MakeUnique<FMeshSceneSelectionChange>();
	ActiveSelectionChange->OldSelection = SelectedSceneObjects;
}

void UInteractiveMeshSceneSubsystem::EndSelectionChange()
{
	check(ActiveSelectionChange);
	if (SelectedSceneObjects != ActiveSelectionChange->OldSelection)
	{
		ActiveSelectionChange->NewSelection = SelectedSceneObjects;

		if (transactionAPI)
		{
			transactionAPI->AppendChange(this, MoveTemp(ActiveSelectionChange), LOCTEXT("SelectionChange", "Selection Change"));
		}
	}

	ActiveSelectionChange = nullptr;
}

UInteractiveMeshSceneObject* UInteractiveMeshSceneSubsystem::CreateNewSceneObject()
{
	UInteractiveMeshSceneObject* MeshSceneObject = NewObject<UInteractiveMeshSceneObject>(this);
	AddSceneObjectInternal(MeshSceneObject, false);

	if (transactionAPI)
	{
		TUniquePtr<FAddRemoveSceneObjectChange> AddChange = MakeUnique<FAddRemoveSceneObjectChange>();
		AddChange->SceneObject = MeshSceneObject;
		AddChange->bAdded = true;
		transactionAPI->AppendChange(MeshSceneObject, MoveTemp(AddChange), LOCTEXT("AddObjectChange", "Add SceneObject"));

	}
	
	MeshSceneObject->SetAllMaterials(StandardMaterial);

	return MeshSceneObject;
}

UInteractiveMeshSceneObject* UInteractiveMeshSceneSubsystem::FindSceneObjectByActor(AActor* Actor)
{
	for (UInteractiveMeshSceneObject* SceneObject : InteractiveMeshSceneObjects)
	{
		if (SceneObject->GetActor() == Actor)
		{
			return SceneObject;
		}
	}
	return nullptr;
}

bool UInteractiveMeshSceneSubsystem::DeleteSceneObject(UInteractiveMeshSceneObject* SceneObject)
{
	if (InteractiveMeshSceneObjects.Contains(SceneObject))
	{
		if (SelectedSceneObjects.Contains(SceneObject))
		{
			BeginSelectionChange();
			SelectedSceneObjects.Remove(SceneObject);
			EndSelectionChange();
			MeshSceneSelectionChangeEvnt.Broadcast(this);
		}

		RemoveSceneObjectInternal(SceneObject, true);

		if (transactionAPI)
		{
			TUniquePtr<FAddRemoveSceneObjectChange> RemoveChange = MakeUnique<FAddRemoveSceneObjectChange>();
			RemoveChange->SceneObject = SceneObject;
			RemoveChange->bAdded = false;
			// use SceneObject as target so that transaction will keep it from being GC'd
			transactionAPI->AppendChange(SceneObject, MoveTemp(RemoveChange), LOCTEXT("RemoveObjectChange", "Delete SceneObject"));
		}

		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[UInteractiveMeshSceneSubsystem::DeleteSceneObject] Tried to delete non-existant SceneObject"));
		return false;
	}
}



void FMeshSceneSelectionChange::Apply(UObject * Object)
{
	if (UInteractiveMeshSceneSubsystem* Subsystem = Cast<UInteractiveMeshSceneSubsystem>(Object))
	{
		Subsystem->SetSelectionInternal(NewSelection);
	}
}

void FMeshSceneSelectionChange::Revert(UObject * Object)
{
	if (UInteractiveMeshSceneSubsystem* Subsystem = Cast<UInteractiveMeshSceneSubsystem>(Object))
	{
		Subsystem->SetSelectionInternal(OldSelection);
	}
}



void FAddRemoveSceneObjectChange::Apply(UObject* Object)
{
	if (bAdded)
	{
		UInteractiveMeshSceneSubsystem::Get()->AddSceneObjectInternal(SceneObject, true);
	}
	else
	{
		UInteractiveMeshSceneSubsystem::Get()->RemoveSceneObjectInternal(SceneObject, true);
	}
}

void FAddRemoveSceneObjectChange::Revert(UObject* Object)
{
	if (bAdded)
	{
		UInteractiveMeshSceneSubsystem::Get()->RemoveSceneObjectInternal(SceneObject, true);
	}
	else
	{
		UInteractiveMeshSceneSubsystem::Get()->AddSceneObjectInternal(SceneObject, true);
	}
}


#undef LOCTEXT_NAMESPACE

