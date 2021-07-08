// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "ToolsContextActor.generated.h"


UENUM()
enum class EToolActorInteractionMode : uint8
{
	NoInteraction,
	RightMouseCameraControl,
	AltCameraControl
};

UCLASS()
class INTERACTIVETOOLSKIT_API AToolsContextActor : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AToolsContextActor();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	UFUNCTION(BlueprintCallable)
		EToolActorInteractionMode GetCurrentInteractionMode() { return CurrentInteractionMode; }
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* ControllerIn);
public:
	UPROPERTY()
		APlayerController* PlayerController;
protected:
	EToolActorInteractionMode CurrentInteractionMode = EToolActorInteractionMode::NoInteraction;
	UInteractiveToolsSubsystem* InteractiveToolSubsytem;

	bool bIsRightMouseDown = false;
	bool bIsMiddleMouseDown = false;
	bool bIsLeftMouseDown = false;
	bool bIsAltKeyDown = false;
	
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

	virtual void OnDelete();
	virtual void OnUndo();
	virtual void OnRedo();

	virtual void OnMoveForwardKeyAxis(float MoveDelta);
	virtual void OnMoveRightKeyAxis(float MoveDelta);
	virtual void OnMoveUpKeyAxis(float MoveDelta);

	virtual void OnMouseMoveX(float MoveX);
	virtual void OnMouseMoveY(float MoveY);


	
};
