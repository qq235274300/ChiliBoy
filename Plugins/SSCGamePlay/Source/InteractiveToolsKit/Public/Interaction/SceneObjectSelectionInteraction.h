// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseBehaviors/SingleClickBehavior.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"
#include "InputBehaviorSet.h"
#include "SceneObjectSelectionInteraction.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIVETOOLSKIT_API USceneObjectSelectionInteraction : public UObject, public IInputBehaviorSource, public IClickBehaviorTarget
{
	GENERATED_BODY()
public:
	
	void Initialize(TUniqueFunction<bool()> CanChangeSelectionCallbackIn);
	
public:
	UPROPERTY()
	USingleClickInputBehavior* ClickBehavior;
	UPROPERTY()
	UInputBehaviorSet* BehaviorSet; // IInputBehaviorSource has Behaviorset pass to UInputRouter
	

/**
 *   
 */
public:
	virtual const UInputBehaviorSet* GetInputBehaviors()const override
	{
		return BehaviorSet;
	}

	virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;
	virtual void OnClicked(const FInputDeviceRay& ClickPos)override;
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn)override;

protected:
	//Default CanChangeSelection be true;
	TUniqueFunction<bool()> CanChangeSelectionCallback = []() {return true; };

	static const int AddToSelectionModifer = 1;
	bool bAddToSelectionEnable = false;
	static const int ToggleSelectionModifer = 2;
	bool bToggleSelectionEnable = false;

};
