// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCDefaultPawn.h"
#include "GameplayPawn.generated.h"


class UInteractiveToolsSubsystem;

UENUM()
enum class EInteractiveMode
{
	NoInteraction,
	RightMouseCameraControl,
	AltCameraControl
};

/**
 * 
 */
//监听输入事件 传入ToolSubSystem
UCLASS()
class INTERACTIVETOOLSKIT_API AGameplayPawn : public ASSCDefaultPawn
{
	GENERATED_BODY()

public:
	AGameplayPawn();
	virtual void ModelInit()override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)override;
	virtual void PossessedBy(AController* NewController)override;
	virtual void BindInputEvent();
	APlayerController* GetPlayerController();
	EInteractiveMode GetInteractiveMode();
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
/***************************Input Bind*************************************/
protected:
	virtual void OnLeftMouseDown();
	virtual void OnLeftMouseUp();
	virtual void OnMiddleMouseDown();
	virtual void OnMiddleMouseUp();

	virtual void OnRightMouseDown();
	virtual void OnRightMouseUp();

	virtual void OnAltKeyDown();
	virtual void OnAltKeyUp();

	virtual void OnToolAccept();
	virtual void OnToolExit();

	virtual void OnMoveForwardKeyAxis(float MoveDelta);
	virtual void OnMoveRightKeyAxis(float MoveDelta);
	virtual void OnMoveUpKeyAxis(float MoveDelta);

	virtual void OnMouseMoveX(float MoveX);
	virtual void OnMouseMoveY(float MoveY);

	virtual void OnDelete();
	virtual void OnUndo();
	virtual void OnRedo();

/*************************************************************************/
protected:
	UPROPERTY()
	APlayerController* PlayerController;

	UInteractiveToolsSubsystem* toolSystem;
	EInteractiveMode InteractiveMode = EInteractiveMode::NoInteraction;

	bool bIsRightMouseDown = false;
	bool bIsMiddleMouseDown = false;
	bool bIsLeftMouseDown = false;
	bool bIsAltKeyDown = false;
	
};
