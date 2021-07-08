// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameplayPawn.h"
#include <SubSystem/InteractiveToolsSubsystem.h>
#include "SSCCommon/SSCCommon.h"
#include <BaseGizmos/GizmoRenderingUtil.h>
#include <SubSystem/InteractiveMeshSceneSubsystem.h>

AGameplayPawn::AGameplayPawn()
{
	
	//PrimaryActorTick.bCanEverTick = true;
}
void AGameplayPawn::ModelInit()
{
	Super::ModelInit();
	UGameInstance* GameInstance = GetGameInstance();
	toolSystem = UGameInstance::GetSubsystem<UInteractiveToolsSubsystem>(GameInstance);
	toolSystem->SetViewPawn(this);
	//绑定输入事件
	BindInputEvent();
#if WITH_EDITOR
	// disable gizmo focus tracking
	GizmoRenderingUtil::SetGlobalFocusedSceneViewTrackingEnabled(false);
#endif
}

void AGameplayPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}

void AGameplayPawn::PossessedBy(AController* NewController)
{
	this->PlayerController = Cast<APlayerController>(NewController);
}



void AGameplayPawn::BindInputEvent()
{
	BindAxis("MoveForward", this, &AGameplayPawn::OnMoveForwardKeyAxis);
	BindAxis("MoveRight", this, &AGameplayPawn::OnMoveRightKeyAxis);
	BindAxis("MoveUp", this, &AGameplayPawn::OnMoveUpKeyAxis);
	BindAxis("MouseMovementX", this, &AGameplayPawn::OnMouseMoveX);
	BindAxis("MouseMovementY", this, &AGameplayPawn::OnMouseMoveY);
	
	BindAction("StandardAltButton", IE_Pressed, this, &AGameplayPawn::OnAltKeyDown);
	BindAction("StandardAltButton", IE_Released, this, &AGameplayPawn::OnAltKeyUp);
	BindAction("LeftMouseButtonAction", IE_Pressed, this, &AGameplayPawn::OnLeftMouseDown);
	BindAction("LeftMouseButtonAction", IE_Released, this, &AGameplayPawn::OnLeftMouseUp);
	BindAction("StandardMiddleMouseButton", IE_Pressed, this, &AGameplayPawn::OnMiddleMouseDown);
	BindAction("StandardMiddleMouseButton", IE_Released, this, &AGameplayPawn::OnMiddleMouseUp);
	BindAction("StandardRightMouseButton", IE_Pressed, this, &AGameplayPawn::OnRightMouseDown);
	BindAction("StandardRightMouseButton", IE_Released, this, &AGameplayPawn::OnRightMouseUp);

	BindKey(EKeys::Enter, IE_Released, this, &AGameplayPawn::OnToolAccept);
	BindKey(EKeys::Escape, IE_Released, this, &AGameplayPawn::OnToolExit);
	BindKey(EKeys::Delete, IE_Released, this, &AGameplayPawn::OnDelete);
	BindKeys(this, &AGameplayPawn::OnUndo, EKeys::LeftControl, EKeys::Z);
	BindKeys(this, &AGameplayPawn::OnRedo, EKeys::LeftControl, EKeys::Y);
}



APlayerController* AGameplayPawn::GetPlayerController()
{
	return PlayerController;
}

EInteractiveMode AGameplayPawn::GetInteractiveMode()
{
	return InteractiveMode;
}

void AGameplayPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
#if WITH_EDITOR
	GizmoRenderingUtil::SetGlobalFocusedSceneViewTrackingEnabled(true);
#endif
}

void AGameplayPawn::OnLeftMouseDown()
{
	bIsLeftMouseDown = true;

	//按住鼠标右键模式 直接忽略
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		//没有在按住鼠标左键移动
		ensure(toolSystem->isCaptureingMouse() == false);
	}
	//按住ALT键模式 返回
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// do orbit
		ensure(toolSystem->isCaptureingMouse() == false);
		return;
	}
	else
	{
		toolSystem->OnLeftMouseDown();
	}
}

void AGameplayPawn::OnLeftMouseUp()
{
	bIsLeftMouseDown = false;

	//按住鼠标右键模式 直接忽略
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		//没有在按住鼠标左键移动
		ensure(toolSystem->isCaptureingMouse() == false);
	}
	//按住ALT键模式 返回
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// do orbit
		ensure(toolSystem->isCaptureingMouse() == false);
		return;
	}
	else
	{
		toolSystem->OnLeftMouseUp();
	}
}

void AGameplayPawn::OnMiddleMouseDown()
{
	bIsMiddleMouseDown = true;

	if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// want to start pan...
	}
}

void AGameplayPawn::OnMiddleMouseUp()
{
	bIsMiddleMouseDown = false;

	if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// want to start pan...
	}
}

void AGameplayPawn::OnRightMouseDown()
{
	bIsRightMouseDown = true;

	// ignore if tool system is capturing
	if (toolSystem && toolSystem->isCaptureingMouse())
	{
		ensure(InteractiveMode == EInteractiveMode::NoInteraction);
		return;
	}

	if (InteractiveMode == EInteractiveMode::NoInteraction)
	{
		InteractiveMode = EInteractiveMode::RightMouseCameraControl;
	}
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// want to start dolly...
	}
}

void AGameplayPawn::OnRightMouseUp()
{
	bIsRightMouseDown = false;

	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		InteractiveMode = EInteractiveMode::NoInteraction;
	}
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// end dolly
	}
}

void AGameplayPawn::OnAltKeyDown()
{
	bIsAltKeyDown = true;

	// if we are in right-mouse cam mode and we press alt, ignore it
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ensure(toolSystem->isCaptureingMouse() == false);
	}
	else if (toolSystem->isCaptureingMouse())
	{
		// if tool system is capturing, ignore alt
	}
	else
	{
		// switch to alt-camera control
		InteractiveMode = EInteractiveMode::AltCameraControl;
	}
}

void AGameplayPawn::OnAltKeyUp()
{
	bIsAltKeyDown = false;

	// if we are in right-mouse cam mode and we release alt, ignore it
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ensure(toolSystem->isCaptureingMouse() == false);
	}
	else if (toolSystem->isCaptureingMouse())
	{
		// if tool system is capturing, ignore alt
	}
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
	{
		// switch out of alt-camera control
		InteractiveMode = EInteractiveMode::NoInteraction;
	}
}


void AGameplayPawn::OnMoveForwardKeyAxis(float MoveDelta)
{
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ADefaultPawn::MoveForward(MoveDelta);
	}
}

void AGameplayPawn::OnMoveRightKeyAxis(float MoveDelta)
{
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ADefaultPawn::MoveRight(MoveDelta);
	}
}

void AGameplayPawn::OnMoveUpKeyAxis(float MoveDelta)
{
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ADefaultPawn::MoveUp_World(MoveDelta);
	}
}

void AGameplayPawn::OnMouseMoveX(float MoveX)
{
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ADefaultPawn::AddControllerYawInput(MoveX);
	}
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
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
			ADefaultPawn::MoveForward(MoveX);
		}
	}
	else
	{
	}
}

void AGameplayPawn::OnMouseMoveY(float MoveY)
{
	if (InteractiveMode == EInteractiveMode::RightMouseCameraControl)
	{
		ADefaultPawn::AddControllerPitchInput(-MoveY);
	}
	else if (InteractiveMode == EInteractiveMode::AltCameraControl)
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

void AGameplayPawn::OnDelete()
{
	if (toolSystem->HaveActiveTool() == false)
	{
		UInteractiveMeshSceneSubsystem::Get()->DeleteSelectedSceneObjects();
	}
}

void AGameplayPawn::OnUndo()
{
	toolSystem->GetSceneHistory()->Undo();
}

void AGameplayPawn::OnRedo()
{
	toolSystem->GetSceneHistory()->Redo();
}

void AGameplayPawn::OnToolAccept()
{
	toolSystem->AcceptActiveTool();
}

void AGameplayPawn::OnToolExit()
{
	toolSystem->CancelOrCompleteActiveTool();
}