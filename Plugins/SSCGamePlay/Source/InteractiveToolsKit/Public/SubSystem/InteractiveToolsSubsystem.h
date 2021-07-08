// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <InteractiveToolsContext.h>
#include <Interaction/SceneObjectSelectionInteraction.h>
#include <Interaction/SceneObjectTransformInteraction.h>
#include "Tools/ToolsContextRenderComponent.h"
#include "Gameplay/GameplayPawn.h"
#include <MeshScene/SceneHistroyManager.h>
#include "InteractiveToolsSubsystem.generated.h"


class FRuntimeToolsContextQueriesImpl;
class FRuntimeToolsContextTransactionImpl;
class FRuntimeToolsContextAssetImpl;
class AToolsContextActor;


/**
 * 
 */
UCLASS()
class INTERACTIVETOOLSKIT_API UInteractiveToolsSubsystem : public UGameInstanceSubsystem
{
	friend class AGameplayPawn;
	GENERATED_BODY()
public:
	static void InitSubSysytem(UInteractiveToolsSubsystem* InInteractiveToolsSubsystem);
	static UInteractiveToolsSubsystem* Get();
public:
	virtual void Deinitialize()override;
private:
	static UInteractiveToolsSubsystem* InteractiveToolSubSystem;
/*********************************************************************************************/
public:
	void Init(UWorld* InWorld);
	virtual void Tick(float DeltaTime);
	void SetViewPawn(AGameplayPawn* InPawn);

	UFUNCTION(BlueprintCallable)
	UInteractiveTool* BeginToolByName(const FString& ToolName);
	UFUNCTION(BlueprintCallable)
	UInteractiveMeshSceneObject* GenerateMeshObj(const FString& filePath,bool ccw);

	UFUNCTION(BlueprintCallable)
	bool HaveActiveTool();
	UFUNCTION(BlueprintCallable)
	bool isCaptureingMouse()const;
	//void ShutDownInteractiveTools();
	UFUNCTION(BlueprintCallable)
	bool AcceptActiveTool();
	UFUNCTION(BlueprintCallable)
	bool CancelOrCompleteActiveTool();
	
/******************************************Get Set*******************************************************************/
public:
	IToolsContextTransactionsAPI* GetTransactionAPI();
	IToolsContextAssetAPI* GetAssetAPI();
	UInteractiveToolsContext* GetToolContext();
	UFUNCTION(BlueprintCallable)
	USceneHistroyManager* GetSceneHistory() { return SceneHistroyManager; }	
	EToolContextCoordinateSystem GetCurrentCoordinateSystem()const { return CurrentCoordinateSystem; }
/**********************************************************************************************************************/

private:
	void AddAllPropertySetKeepAlives(UInteractiveTool* Tool);
	void AddPropertySetKeepAlive(UInteractiveToolPropertySet* PropertySet);
	void InternalConsistencyChecks();

/******************************************绑定事件************************************************************************/
private:
	void OnToolStartedEvnt(UInteractiveToolManager* InManager, UInteractiveTool* InInteractiveTool);
	void OnToolEndedEvnt(UInteractiveToolManager* InManager, UInteractiveTool* InInteractiveTool);
	void OnSceneHistroyStateChangeEvnt();
	void OnLeftMouseDown();
	void OnLeftMouseUp();
	/**********************************************************************************************************************/
private:
	UPROPERTY()
	UWorld* CurrentWorld;
	UPROPERTY()
	AGameplayPawn* pViewPawn;
 // ITF Framework 
	UPROPERTY()
	UInteractiveToolsContext* ToolContext;
	UPROPERTY()
	USceneHistroyManager* SceneHistroyManager;
	TSharedPtr<FRuntimeToolsContextQueriesImpl> QueriesAPI;
	TSharedPtr<FRuntimeToolsContextTransactionImpl> TransactionAPI;
	TSharedPtr<FRuntimeToolsContextAssetImpl> AssetAPI;
//Input:: Mouse , View
	FInputDeviceState CurrentMouseState;
	FViewCameraState CurrentViewCameraState;
	FVector2D PrevMousePosition = FVector2D::ZeroVector;
	bool bPendingMouseStateChange = false;
//鼠标选中行为
	UPROPERTY()
	USceneObjectSelectionInteraction* SOSelectionInteraction;
	UPROPERTY()
	USceneObjectTransformInteraction* SOTransformInteraction;
//PDI
	UPROPERTY()
	UToolsContextRenderComponent* PDIRenderComponent;
	UPROPERTY()
	AActor* PDIRenderActor;	//挂载RenderCom的对象	
	UPROPERTY()
	EToolContextCoordinateSystem CurrentCoordinateSystem = EToolContextCoordinateSystem::World;
//GC
	UPROPERTY()
	TArray<UObject*> PropertySetKeepAlives;
	bool bIsShuttingDown = false;
};

/**
 *  Tool Createion / Manager
 */
//
//UFUNCTION(BlueprintCallable)
//	bool CanActivateToolByName(FString Name);
//UFUNCTION(BlueprintCallable)
//UInteractiveTool* BeginToolByName(FString ToolName);

//UFUNCTION(BlueprintCallable)
//UInteractiveTool* GetActiveTool();
//UFUNCTION(BlueprintCallable)
//bool IsActiveToolAcceptCancelType();
//UFUNCTION(BlueprintCallable)
//bool CanAcceptActiveTool();

//
//
///**
// *  Access API
// */

//	TArray<UObject*> GetActiveToolPropertySets();
//
///**
//* CoordinateSystem
//*/
//

//
//	void SetCurrentCoordinateSystem(EToolContextCoordinateSystem CoordSystem);
//	UFUNCTION(BlueprintCallable)
//		void CycleCurrentCoordinateSystem();
//	UFUNCTION(BlueprintCallable)
//		bool IsWorldCoordinateSystem() { return CurrentCoordinateSystem == EToolContextCoordinateSystem::World; }
//
//
///**
//* CoordinateSystem
//*/
//public:
//	UFUNCTION(BlueprintCallable)
//		UInteractiveMeshSceneObject* ImportMeshSceneObject(const FString Path, bool bFlipOrientation);
///**
//*  ...
//*/
//private:
//	void InternalConsistencyChecks();


//
//	



//
///**
//*  Mouse
//*/
//public:
//	UFUNCTION(BlueprintCallable)
//		bool IsCapturingMouse() const;
//public:
//	void OnLeftMouseDown();
//	void OnLeftMouseUp();
//protected:
//	friend class AToolsContextActor;
//
//




