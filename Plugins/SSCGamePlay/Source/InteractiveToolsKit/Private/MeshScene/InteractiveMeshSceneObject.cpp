// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshScene/InteractiveMeshSceneObject.h"
#include "MeshDescriptionToDynamicMesh.h"
#include "DynamicMeshToMeshDescription.h"

UInteractiveMeshSceneObject::UInteractiveMeshSceneObject()
{
	if (!SourceMesh)
	{
		SourceMesh = MakeUnique<FDynamicMesh3>();
	}
	if (!MeshAABBTree)
	{
		MeshAABBTree = MakeUnique<FDynamicMeshAABBTree3>();
	}

	UMaterialInterface* DefaultMaterial = UMaterial::GetDefaultMaterial(MD_Surface);
	Materials.Add(DefaultMaterial);
}

void UInteractiveMeshSceneObject::Initialize(UWorld* TargetWorld, const FMeshDescription* InitialMeshDescription)
{
	check(TargetWorld);
	FActorSpawnParameters SpawnInfo;
	SimpleDynamicMeshActor = TargetWorld->SpawnActor<ADynamicSDMCActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	SimpleDynamicMeshActor->MeshComponent->OnMeshChanged.AddLambda(
		[this]() { OnExternalDynamicMeshComponentUpdate(); }
	);
	
	GetActor()->SourceType = EDynamicMeshActorSourceType::ExternallyGenerated;
	GetActor()->CollisionMode = EDynamicMeshActorCollisionMode::ComplexAsSimpleAsync;
	
	UpdateSourceMesh(InitialMeshDescription);
	GetActor()->EditMesh
	(
		[&](FDynamicMesh3& MeshToEdit) { MeshToEdit = *SourceMesh; }
	);
	UpdateComponentMaterials(false);
}

void UInteractiveMeshSceneObject::Initialize(UWorld* TargetWorld, const FDynamicMesh3* InitialMesh)
{
	check(TargetWorld);
	FActorSpawnParameters SpawnInfo;
	SimpleDynamicMeshActor = TargetWorld->SpawnActor<ADynamicSDMCActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	SimpleDynamicMeshActor->MeshComponent->OnMeshChanged.AddLambda(
		[this]() { OnExternalDynamicMeshComponentUpdate(); }
	);
	GetActor()->SourceType = EDynamicMeshActorSourceType::ExternallyGenerated;
	GetActor()->CollisionMode = EDynamicMeshActorCollisionMode::ComplexAsSimpleAsync;
	
	*SourceMesh = *InitialMesh;
	MeshAABBTree->SetMesh(SourceMesh.Get(), true);
	GetActor()->EditMesh
	(
		[&](FDynamicMesh3& MeshToEdit) { MeshToEdit = *SourceMesh; }
	);
	UpdateComponentMaterials(false);
}

void UInteractiveMeshSceneObject::SetTransform(FTransform Transform)
{
	GetActor()->SetActorTransform(Transform);
}

ADynamicMeshBaseActor* UInteractiveMeshSceneObject::GetActor()
{
	return SimpleDynamicMeshActor;
}

UMeshComponent* UInteractiveMeshSceneObject::GetMeshComponent()
{
	return SimpleDynamicMeshActor ? SimpleDynamicMeshActor->MeshComponent : nullptr;
}

void UInteractiveMeshSceneObject::SetAllMaterials(UMaterialInterface* SetToMaterial)
{

}

void UInteractiveMeshSceneObject::SetToHighlightMaterial(UMaterialInterface* Material)
{
	UMeshComponent* Component = GetMeshComponent();
	int32 NumMaterials = FMath::Max(1, Component->GetNumMaterials());
	for (int32 k = 0; k < NumMaterials; ++k)
	{
		Component->SetMaterial(k, Material);
	}

	// HACK TO FORCE MATERIAL UPDATE IN SDMC
	SimpleDynamicMeshActor->MeshComponent->NotifyMeshUpdated();
}

void UInteractiveMeshSceneObject::ClearHighlightMaterial()
{
	UpdateComponentMaterials(true);
}

bool UInteractiveMeshSceneObject::IntersectRay(FVector RayOrigin, FVector RayDirection, FVector& WorldHitPoint, float& HitDistance, int& NearestTriangle, FVector& TriBaryCoords, float MaxDistance /*= 0*/)
{
	if (!ensure(SourceMesh)) return false;

	FTransform3d ActorToWorld(GetActor()->GetActorTransform());
	FVector3d WorldDirection(RayDirection); WorldDirection.Normalize();
	FRay3d LocalRay(ActorToWorld.InverseTransformPosition((FVector3d)RayOrigin),
		ActorToWorld.InverseTransformNormal(WorldDirection));
	IMeshSpatial::FQueryOptions QueryOptions;
	if (MaxDistance > 0)
	{
		QueryOptions.MaxDistance = MaxDistance;
	}
	NearestTriangle = MeshAABBTree->FindNearestHitTriangle(LocalRay, QueryOptions);
	if (SourceMesh->IsTriangle(NearestTriangle))
	{
		FIntrRay3Triangle3d IntrQuery = TMeshQueries<FDynamicMesh3>::TriangleIntersection(*SourceMesh, NearestTriangle, LocalRay);
		if (IntrQuery.IntersectionType == EIntersectionType::Point)
		{
			HitDistance = IntrQuery.RayParameter;
			WorldHitPoint = (FVector)ActorToWorld.TransformPosition(LocalRay.PointAt(IntrQuery.RayParameter));
			TriBaryCoords = (FVector)IntrQuery.TriangleBaryCoords;
			return true;
		}
	}
	return false;
}

void UInteractiveMeshSceneObject::OnExternalDynamicMeshComponentUpdate()
{
	const FDynamicMesh3* Mesh = SimpleDynamicMeshActor->MeshComponent->GetMesh();
	*SourceMesh = *Mesh;
	MeshAABBTree->SetMesh(SourceMesh.Get(), true);
}

void UInteractiveMeshSceneObject::UpdateSourceMesh(const FMeshDescription* InMeshDescription)
{
	FMeshDescriptionToDynamicMesh Converter;
	FDynamicMesh3 TempMesh;
	Converter.Convert(InMeshDescription, TempMesh);
	*SourceMesh = MoveTemp(TempMesh);
	MeshAABBTree->SetMesh(SourceMesh.Get(), true);
}

void UInteractiveMeshSceneObject::UpdateComponentMaterials(bool bForceRefresh)
{
	UMaterialInterface* DefaultMaterial = UMaterial::GetDefaultMaterial(MD_Surface);
	UMeshComponent* Component = GetMeshComponent();
	if (!Component) return;
	
	int32 NumMaterials = FMath::Max(1, Component->GetNumMaterials());
	for (int32 k = 0; k < NumMaterials; ++k)
	{
		UMaterialInterface* SetMaterial = (k < Materials.Num()) ? Materials[k] : DefaultMaterial;
		Component->SetMaterial(k, SetMaterial);
	}
	if (bForceRefresh)
	{
		SimpleDynamicMeshActor->MeshComponent->NotifyMeshUpdated();
	}
}
