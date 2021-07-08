// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SceneObjectSelectionInteraction.h"
#include <MeshScene/InteractiveMeshSceneObject.h>
#include <SubSystem/InteractiveMeshSceneSubsystem.h>

void USceneObjectSelectionInteraction::Initialize(TUniqueFunction<bool()> CanChangeSelectionCallbackIn)
{
	CanChangeSelectionCallback =MoveTemp(CanChangeSelectionCallbackIn);
	ClickBehavior = NewObject<USingleClickInputBehavior>();	
	ClickBehavior->Modifiers.RegisterModifier(AddToSelectionModifer, FInputDeviceState::IsShiftKeyDown);
	ClickBehavior->Modifiers.RegisterModifier(ToggleSelectionModifer, FInputDeviceState::IsCtrlKeyDown);
	ClickBehavior->Initialize(this);
	BehaviorSet = NewObject<UInputBehaviorSet>();
	BehaviorSet->Add(ClickBehavior, this);
}

FInputRayHit USceneObjectSelectionInteraction::IsHitByClick(const FInputDeviceRay& ClickPos)
{
	FInputRayHit RayHit;

	if (CanChangeSelectionCallback() == false)
	{
		return RayHit;
	}

	FVector HitPoint, BaryCoords;
	float HitDist;
	int32 HitTri;
	UInteractiveMeshSceneObject* HitObject = UInteractiveMeshSceneSubsystem::Get()->FindNearestHitObject(
		ClickPos.WorldRay.Origin, ClickPos.WorldRay.Direction, HitPoint, HitDist, HitTri, BaryCoords);

	if (HitObject != nullptr)
	{
		RayHit.bHit = true;
		RayHit.HitDepth = HitDist;
		//RayHit.HitNormal = ;			// todo - can compute from bary coords
		//RayHit.bHasHitNormal = ;		// todo - can compute from bary coords
		RayHit.HitIdentifier = HitTri;
		RayHit.HitOwner = HitObject;
	}
	else
	{
		RayHit.bHit = true;
		RayHit.HitDepth = TNumericLimits<float>::Max();
		RayHit.HitIdentifier = 0;
		RayHit.HitOwner = this;
	}
	return RayHit;
}

void USceneObjectSelectionInteraction::OnClicked(const FInputDeviceRay& ClickPos)
{
	FVector HitPoint, BaryCoords;
	float HitDist;
	int32 HitTri;
	UInteractiveMeshSceneObject* HitObject = UInteractiveMeshSceneSubsystem::Get()->FindNearestHitObject(
		ClickPos.WorldRay.Origin, ClickPos.WorldRay.Direction, HitPoint, HitDist, HitTri, BaryCoords);

	if (HitObject != nullptr)
	{
		if (bAddToSelectionEnable)
		{
			UInteractiveMeshSceneSubsystem::Get()->SetSelected(HitObject, false, false);
		}
		else if (bToggleSelectionEnable)
		{
			UInteractiveMeshSceneSubsystem::Get()->ToggleSelected(HitObject);
		}
		else
		{
			UInteractiveMeshSceneSubsystem::Get()->SetSelected(HitObject, false, true);
		}
	}
	else
	{
		UInteractiveMeshSceneSubsystem::Get()->ClearSelection();
	}
}

void USceneObjectSelectionInteraction::OnUpdateModifierState(int ModifierID, bool bIsOn)
{
	if (ModifierID == AddToSelectionModifer)
	{
		bAddToSelectionEnable = bIsOn;
	}
	else if (ModifierID == ToggleSelectionModifer)
	{
		bToggleSelectionEnable = bIsOn;
	}
}
