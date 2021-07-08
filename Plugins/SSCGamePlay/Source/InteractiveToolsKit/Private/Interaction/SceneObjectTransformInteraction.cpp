// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SceneObjectTransformInteraction.h"
#include <SubSystem/InteractiveToolsSubsystem.h>
#include <MeshScene/InteractiveMeshSceneObject.h>
#include <BaseGizmos/TransformProxy.h>
#include "BaseGizmos/TransformGizmo.h"

void USceneObjectTransformInteraction::Initialize(TUniqueFunction<bool()> GizmoEnableCallbackCallbackin)
{
	GizmoEnableCallback = MoveTemp(GizmoEnableCallbackCallbackin);
	SelectionChangedEventHandle = UInteractiveMeshSceneSubsystem::Get()->MeshSceneSelectionChangeEvnt.AddLambda([this](UInteractiveMeshSceneSubsystem* SceneSubsystem)
	{
		UpdateGizmoTargets(SceneSubsystem->GetInteractiveMeshSceneObjects());
	});
}

void USceneObjectTransformInteraction::Shutdown()
{
	if (SelectionChangedEventHandle.IsValid())
	{
		if (UInteractiveMeshSceneSubsystem::Get())
		{
			UInteractiveMeshSceneSubsystem::Get()->MeshSceneSelectionChangeEvnt.Remove(SelectionChangedEventHandle);
		}
		SelectionChangedEventHandle = FDelegateHandle();
	}

	TArray<UInteractiveMeshSceneObject*> EmptySelection;
	UpdateGizmoTargets(EmptySelection);
}

void USceneObjectTransformInteraction::SetEnableScaling(bool bEnable)
{
	if (bEnable != bEnableScaling)
	{
		bEnableScaling = bEnable;
		ForceUpdateGizmoState();
	}
}

void USceneObjectTransformInteraction::SetEnableNonUniformScaling(bool bEnable)
{
	if (bEnable != bEnableNonUniformScaling)
	{
		bEnableNonUniformScaling = bEnable;
		ForceUpdateGizmoState();
	}
}

void USceneObjectTransformInteraction::ForceUpdateGizmoState()
{
	if (UInteractiveMeshSceneSubsystem::Get())
	{
		UpdateGizmoTargets(UInteractiveMeshSceneSubsystem::Get()->GetInteractiveMeshSceneObjects());
	}
}

void USceneObjectTransformInteraction::UpdateGizmoTargets(const TArray<UInteractiveMeshSceneObject*>& Selections)
{
	UInteractiveGizmoManager* GizmoManager = UInteractiveToolsSubsystem::Get()->GetToolContext()->GizmoManager;

	// destroy existing gizmos if we have any
	if (TransformGizmo != nullptr)
	{
		GizmoManager->DestroyAllGizmosByOwner(this);
		TransformGizmo = nullptr;
		TransformProxy = nullptr;
	}

	// if no selection, no gizmo
	if (Selections.Num() == 0 || GizmoEnableCallback() == false)
	{
		return;
	}

	TransformProxy = NewObject<UTransformProxy>(this);
	for (UInteractiveMeshSceneObject* SO : Selections)
	{
		// would be nice if this worked on Actors...
		TransformProxy->AddComponent(SO->GetMeshComponent());
	}

	ETransformGizmoSubElements GizmoElements = ETransformGizmoSubElements::FullTranslateRotateScale;
	if (bEnableScaling == false)
	{
		GizmoElements = ETransformGizmoSubElements::StandardTranslateRotate;
	}
	else if (bEnableNonUniformScaling == false || Selections.Num() > 1)		// cannot nonuniform-scale multiple objects
	{
		GizmoElements = ETransformGizmoSubElements::TranslateRotateUniformScale;
	}

	TransformGizmo = GizmoManager->CreateCustomTransformGizmo(GizmoElements, this);
	TransformGizmo->SetActiveTarget(TransformProxy);
}
