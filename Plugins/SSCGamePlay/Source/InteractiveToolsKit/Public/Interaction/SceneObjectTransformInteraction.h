// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SceneObjectTransformInteraction.generated.h"

class UInteractiveMeshSceneObject;
class UTransformGizmo; 
class UTransformProxy; 

/**
 * 
 * Behavior of the TRS Gizmo (ie pivot position, etc) is controlled by a standard UTransformProxy.
 * See UTransformMeshesTool for sample code for doing things like modifying pivot dynamically/etc.
 */
UCLASS()
class INTERACTIVETOOLSKIT_API USceneObjectTransformInteraction : public UObject
{
	GENERATED_BODY()
	
public:
	//whether Gizmo should be create and visible 
	void Initialize(TUniqueFunction<bool()> GizmoEnableCallbackCallbackin);
	void Shutdown();
	UFUNCTION(BlueprintCallable)
		void SetEnableScaling(bool bEnable);
	UFUNCTION(BlueprintCallable)
		void SetEnableNonUniformScaling(bool bEnable);
	
	// eg Selection add
	UFUNCTION(BlueprintCallable)
		void ForceUpdateGizmoState();
protected:

	void UpdateGizmoTargets(const TArray<UInteractiveMeshSceneObject*>& Selections);
	
	FDelegateHandle SelectionChangedEventHandle;
	
	UPROPERTY()
		UTransformProxy* TransformProxy;
	UPROPERTY()
		UTransformGizmo* TransformGizmo;
	
	bool bEnableScaling = true;
	bool bEnableNonUniformScaling = true;
	TUniqueFunction<bool()> GizmoEnableCallback = [&]() {return true; };
};
