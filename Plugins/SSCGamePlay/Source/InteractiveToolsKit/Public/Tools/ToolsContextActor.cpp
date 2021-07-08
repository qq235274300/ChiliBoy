// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/ToolsContextActor.h"
#include "BaseGizmos/GizmoRenderingUtil.h"
#include "SubSystem/InteractiveToolsSubsystem.h"
#include <GameFramework/PlayerInput.h>
#include <Engine/GameInstance.h>
#include "HelperKits/Public/DebugHelper.h"

// Sets default values
AToolsContextActor::AToolsContextActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AToolsContextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	while (true)
	{
		if (1)
		{
			return;
		}
		DebugHelper::Count() << "xxxx" << DebugHelper::Endl();
	}

}

// Called when the game starts or when spawned
void AToolsContextActor::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = GetGameInstance();
	InteractiveToolSubsytem = UGameInstance::GetSubsystem<UInteractiveToolsSubsystem>(GameInstance);
	//InteractiveToolSubsytem->SetContextActor(this);

#if WITH_EDITOR
	GizmoRenderingUtil::SetGlobalFocusedSceneViewTrackingEnabled(true);
#endif

}

void AToolsContextActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
#if WITH_EDITOR
	GizmoRenderingUtil::SetGlobalFocusedSceneViewTrackingEnabled(true);
#endif
}

// Called to bind functionality to input
void AToolsContextActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TFPawn_MoveForward", EKeys::W, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TFPawn_MoveForward", EKeys::S, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TFPawn_MoveRight", EKeys::A, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TFPawn_MoveRight", EKeys::D, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TFPawn_MoveUp", EKeys::E, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TFPawn_MoveUp", EKeys::Q, -1.f));


	PlayerInputComponent->BindAxis("TFPawn_MoveForward", this, &AToolsContextActor::OnMoveForwardKeyAxis);
	PlayerInputComponent->BindAxis("TFPawn_MoveRight", this, &AToolsContextActor::OnMoveRightKeyAxis);
	PlayerInputComponent->BindAxis("TFPawn_MoveUp", this, &AToolsContextActor::OnMoveUpKeyAxis);

	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("StandardAltButton", EKeys::LeftAlt));
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("StandardAltButton", EKeys::RightAlt));
	PlayerInputComponent->BindAction("StandardAltButton", IE_Pressed, this, &AToolsContextActor::OnAltKeyDown);
	PlayerInputComponent->BindAction("StandardAltButton", IE_Released, this, &AToolsContextActor::OnAltKeyUp);

	PlayerInputComponent->BindAction("LeftMouseButtonAction", IE_Pressed, this, &AToolsContextActor::OnLeftMouseDown);
	PlayerInputComponent->BindAction("LeftMouseButtonAction", IE_Released, this, &AToolsContextActor::OnLeftMouseUp);

	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("StandardMiddleMouseButton", EKeys::MiddleMouseButton));
	PlayerInputComponent->BindAction("StandardMiddleMouseButton", IE_Pressed, this, &AToolsContextActor::OnMiddleMouseDown);
	PlayerInputComponent->BindAction("StandardMiddleMouseButton", IE_Released, this, &AToolsContextActor::OnMiddleMouseUp);

	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("StandardRightMouseButton", EKeys::RightMouseButton));
	PlayerInputComponent->BindAction("StandardRightMouseButton", IE_Pressed, this, &AToolsContextActor::OnRightMouseDown);
	PlayerInputComponent->BindAction("StandardRightMouseButton", IE_Released, this, &AToolsContextActor::OnRightMouseUp);

	InputComponent->BindAxis("MouseMovementX", this, &AToolsContextActor::OnMouseMoveX);
	InputComponent->BindAxis("MouseMovementY", this, &AToolsContextActor::OnMouseMoveY);

	// generally bound to enter
	InputComponent->BindAction("ActiveToolAccept", IE_Released, this, &AToolsContextActor::OnToolAccept);
	// generally bound to escape
	InputComponent->BindAction("ActiveToolExit", IE_Released, this, &AToolsContextActor::OnToolExit);

	// generally bound to ctrl+z
	InputComponent->BindAction("UndoAction", IE_Released, this, &AToolsContextActor::OnUndo);
	// generally bound to ctrl+y
	InputComponent->BindAction("RedoAction", IE_Released, this, &AToolsContextActor::OnRedo);

	// generally bound to delete
	InputComponent->BindAction("DeleteAction", IE_Released, this, &AToolsContextActor::OnDelete);

}

void AToolsContextActor::PossessedBy(AController* ControllerIn)
{
	this->PlayerController = Cast<APlayerController>(ControllerIn);
}

void AToolsContextActor::OnLeftMouseDown()
{
	bIsLeftMouseDown = true;

	// if we are in right-mouse cam mode and we press left, ignore it
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		//ensure(InteractiveToolSubsytem->IsCapturingMouse() == false);
	}
	else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		// do orbit
		//ensure(InteractiveToolSubsytem->IsCapturingMouse() == false);
		return;
	}
	else
	{
		//InteractiveToolSubsytem->OnLeftMouseDown();
	}
}

void AToolsContextActor::OnLeftMouseUp()
{
	bIsLeftMouseDown = false;

	// if we are in right-mouse cam mode and we press left, ignore it
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		//ensure(InteractiveToolSubsytem->IsCapturingMouse() == false);
	}
	else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		// end orbit
		//ensure(InteractiveToolSubsytem->IsCapturingMouse() == false);
		return;
	}
	else
	{
		//InteractiveToolSubsytem->OnLeftMouseUp();
	}
}

void AToolsContextActor::OnMiddleMouseDown()
{
	bIsMiddleMouseDown = true;

	if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		// want to start pan...
	}
}

void AToolsContextActor::OnMiddleMouseUp()
{
	bIsMiddleMouseDown = false;

	if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		// want to end pan...
	}
}


void AToolsContextActor::OnRightMouseDown()
{
	bIsRightMouseDown = true;

	// ignore if tool system is capturing
	/*if (InteractiveToolSubsytem && InteractiveToolSubsytem->IsCapturingMouse())
	{
		ensure(CurrentInteractionMode == EToolActorInteractionMode::NoInteraction);
		return;
	}*/

	if (CurrentInteractionMode == EToolActorInteractionMode::NoInteraction)
	{
		CurrentInteractionMode = EToolActorInteractionMode::RightMouseCameraControl;
	}
	else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		// want to start dolly...
	}
}

void AToolsContextActor::OnRightMouseUp()
{
	bIsRightMouseDown = false;

	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		CurrentInteractionMode = EToolActorInteractionMode::NoInteraction;
	}
	else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		// end dolly
	}
}




void AToolsContextActor::OnAltKeyDown()
{
	bIsAltKeyDown = true;

	// if we are in right-mouse cam mode and we press alt, ignore it
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		//ensure(InteractiveToolSubsytem->IsCapturingMouse() == false);
	}
	//else if (InteractiveToolSubsytem->IsCapturingMouse())
	//{
	//	// if tool system is capturing, ignore alt
	//}
	else
	{
		// switch to alt-camera control
		CurrentInteractionMode = EToolActorInteractionMode::AltCameraControl;
	}
}



void AToolsContextActor::OnAltKeyUp()
{
	bIsAltKeyDown = false;

	// if we are in right-mouse cam mode and we release alt, ignore it
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		//ensure(InteractiveToolSubsytem->IsCapturingMouse() == false);
	}
	//else if (InteractiveToolSubsytem->IsCapturingMouse())
	//{
	//	// if tool system is capturing, ignore alt
	//}
	//else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	//{
	//	// switch out of alt-camera control
	//	CurrentInteractionMode = EToolActorInteractionMode::NoInteraction;
	//}
}




void AToolsContextActor::OnMouseMoveX(float MoveX)
{
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		ADefaultPawn::AddControllerYawInput(MoveX);
	}
	else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		if (bIsLeftMouseDown)
		{
			ADefaultPawn::AddControllerYawInput(MoveX);
		}
		else if (bIsMiddleMouseDown)
		{
			ADefaultPawn::MoveRight(100.0 * MoveX);
		}
		else if (bIsRightMouseDown)
		{
			//ADefaultPawn::MoveForward(MoveX);
		}
	}
	else
	{
	}
}


void AToolsContextActor::OnMouseMoveY(float MoveY)
{
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		ADefaultPawn::AddControllerPitchInput(-MoveY);
	}
	else if (CurrentInteractionMode == EToolActorInteractionMode::AltCameraControl)
	{
		if (bIsLeftMouseDown)
		{
			ADefaultPawn::AddControllerPitchInput(-MoveY);
		}
		else if (bIsMiddleMouseDown)
		{
			ADefaultPawn::MoveUp_World(100.0 * MoveY);
		}
		else if (bIsRightMouseDown)
		{
			ADefaultPawn::MoveForward(-100.0 * MoveY);
		}
		// else RMB		
	}
	else
	{
	}
}




void AToolsContextActor::OnMoveForwardKeyAxis(float MoveDelta)
{
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		ADefaultPawn::MoveForward(MoveDelta);
	}
}
void AToolsContextActor::OnMoveRightKeyAxis(float MoveDelta)
{
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		ADefaultPawn::MoveRight(MoveDelta);
	}
}
void AToolsContextActor::OnMoveUpKeyAxis(float MoveDelta)
{
	if (CurrentInteractionMode == EToolActorInteractionMode::RightMouseCameraControl)
	{
		ADefaultPawn::MoveUp_World(MoveDelta);
	}
}




void AToolsContextActor::OnToolAccept()
{
	//InteractiveToolSubsytem->AcceptActiveTool();
}

void AToolsContextActor::OnToolExit()
{
	//InteractiveToolSubsytem->CancelOrCompleteActiveTool();
}

void AToolsContextActor::OnUndo()
{
	InteractiveToolSubsytem->GetSceneHistory()->Undo();
}

void AToolsContextActor::OnRedo()
{
	InteractiveToolSubsytem->GetSceneHistory()->Redo();
}

void AToolsContextActor::OnDelete()
{
	/*if (InteractiveToolSubsytem->HaveActiveTool() == false)
	{
		UInteractiveMeshSceneSubsystem::Get()->DeleteSelectedSceneObjects();
	}*/
}
