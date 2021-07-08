// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SubSystem/InteractiveToolsSubsystem.h"
#include "InteractiveToolsContext.h"
#include "InteractiveMeshSceneSubsystem.generated.h"

/**
 * 
 */
class FMeshSceneSelectionChange;
class FAddRemoveSceneObjectChange;

UCLASS()
class INTERACTIVETOOLSKIT_API UInteractiveMeshSceneSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static void InitSubSysytem(UInteractiveMeshSceneSubsystem* InInteractiveMeshSceneSubSystem);
	static UInteractiveMeshSceneSubsystem* Get();
	virtual void Deinitialize()override;
private:
	static UInteractiveMeshSceneSubsystem* InteractiveMeshSceneSubsystem;

public:
	void SetTransactionAPI(IToolsContextTransactionsAPI* IntransactionAPI);
private:
	IToolsContextTransactionsAPI* transactionAPI;
public:
	UPROPERTY()
		UMaterialInterface* StandardMaterial;
	UPROPERTY()
		UMaterialInterface* SelectedMaterial;
	UPROPERTY()
		UMaterialInterface* WireframeMaterial;	
public:
	

	UFUNCTION(BlueprintCallable)
		UInteractiveMeshSceneObject* CreateNewSceneObject();
	UFUNCTION(BlueprintCallable)
		UInteractiveMeshSceneObject* FindSceneObjectByActor(AActor* Actor);
	UFUNCTION(BlueprintCallable)
		bool DeleteSceneObject(UInteractiveMeshSceneObject* SceneObject);
	UFUNCTION(BlueprintCallable)
		bool DeleteSelectedSceneObjects();
	bool DeleteSelectedSceneObjects(AActor* SkipActor);
public:
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneSubsystem")
		TArray<UInteractiveMeshSceneObject*> GetInteractiveMeshSceneObjects()const;
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneSubsystem")
		void ClearSelection();
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneSubsystem")
		void SetSelected(UInteractiveMeshSceneObject* SceneObject, bool bDeSelect = false, bool bDeSelectOthers = true);
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneSubsystem")
		void ToggleSelected(UInteractiveMeshSceneObject* SceneObject);
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneSubsystem")
		void SetSelection(const TArray<UInteractiveMeshSceneObject*>& SceneObjects);
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FMeshSceneSelectionChangeEvent, UInteractiveMeshSceneSubsystem*);
	FMeshSceneSelectionChangeEvent MeshSceneSelectionChangeEvnt;
public:
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneSubsystem")
		UInteractiveMeshSceneObject* FindNearestHitObject(FVector RayOrigin, FVector RayDirection, FVector& WorldHitPoint, float& HitDistance, int& NearestTriangle, FVector& TriBaryCoords, float MaxDistance = 0);
public:
	void AddSceneObjectInternal(UInteractiveMeshSceneObject* Object,bool bIsUndoRedo );
	void RemoveSceneObjectInternal(UInteractiveMeshSceneObject* Object, bool bIsUndoRedo);
	void SetSelectionInternal(const TArray<UInteractiveMeshSceneObject*>& SceneObjects);
	void BeginSelectionChange();
	void EndSelectionChange();
private:
	UPROPERTY()
	TArray<UInteractiveMeshSceneObject*> InteractiveMeshSceneObjects;
	UPROPERTY()
		TArray<UInteractiveMeshSceneObject*> SelectedSceneObjects;

	TUniquePtr<FMeshSceneSelectionChange> ActiveSelectionChange;

	friend class FMeshSceneSelectionChange;
	friend class FAddRemoveSceneObjectChange;
};

class INTERACTIVETOOLSKIT_API FMeshSceneSelectionChange : public FToolCommandChange
{
public:
	TArray<UInteractiveMeshSceneObject*> OldSelection;
	TArray<UInteractiveMeshSceneObject*> NewSelection;

	virtual void Apply(UObject* Object) override;
	virtual void Revert(UObject* Object) override;
	virtual FString ToString() const override { return TEXT("FMeshSceneSelectionChange"); }
};



class INTERACTIVETOOLSKIT_API FAddRemoveSceneObjectChange : public FToolCommandChange
{
public:
	UInteractiveMeshSceneObject* SceneObject;
	bool bAdded = true;
public:
	virtual void Apply(UObject* Object)override;
	virtual void Revert(UObject* Object)override;
	virtual FString ToString()const override { return  TEXT("FAddRemoveSceneObjectChange"); }


};