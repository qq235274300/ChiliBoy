// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DynamicMesh3.h"
#include "DynamicMeshAABBTree3.h"
#include "Components/MeshComponent.h"
#include "RuntimeGeometryUtils/Public/DynamicMeshBaseActor.h"
#include <DynamicSDMCActor.h>
#include "InteractiveMeshSceneObject.generated.h"


/**
 * 
 */
UCLASS()
class INTERACTIVETOOLSKIT_API UInteractiveMeshSceneObject : public UObject
{
	GENERATED_BODY()

public:
	UInteractiveMeshSceneObject();
	void Initialize(UWorld* TargetWorld, const FMeshDescription* InitialMeshDescription);
	void Initialize(UWorld* TargetWorld, const FDynamicMesh3* InitialMesh);
	
	void SetTransform(FTransform Transform);
	ADynamicMeshBaseActor* GetActor();
	UMeshComponent* GetMeshComponent();

public:
	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneObject")
		void SetAllMaterials(UMaterialInterface* SetToMaterial);


	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneObject")
		void SetToHighlightMaterial(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneObject")
		void ClearHighlightMaterial();

	UFUNCTION(BlueprintCallable, Category = "InteractiveMeshSceneObject")
		bool IntersectRay(FVector RayOrigin, FVector RayDirection, FVector& WorldHitPoint, float& HitDistance, int& NearestTriangle, FVector& TriBaryCoords, float MaxDistance = 0);
protected:
	UPROPERTY()
		ADynamicSDMCActor* SimpleDynamicMeshActor = nullptr;

protected:
	TUniquePtr<FDynamicMesh3> SourceMesh;
	TUniquePtr<FDynamicMeshAABBTree3> MeshAABBTree;
	TArray<UMaterialInterface*> Materials;

protected:
	void OnExternalDynamicMeshComponentUpdate();
	void UpdateSourceMesh(const FMeshDescription* InMeshDescription);
	void UpdateComponentMaterials(bool bForceRefresh);
};
