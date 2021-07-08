// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleView.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

void FBindToViewTarget::GetViewInfo(FMinimalViewInfo& InOutInfo) const
{
	if (Target->IsA(ACameraActor::StaticClass()))
	{
		ACameraActor* tmpCameraActor = dynamic_cast<ACameraActor*>(Target);
		if (tmpCameraActor != nullptr)
		{
			UCameraComponent* CameraCom = tmpCameraActor->GetCameraComponent();
			InOutInfo.Location = CameraCom->GetComponentLocation();
			InOutInfo.Rotation = CameraCom->GetComponentRotation();
			InOutInfo.FOV = CameraCom->FieldOfView;
			InOutInfo.OrthoWidth = CameraCom->OrthoWidth;
			InOutInfo.OrthoNearClipPlane = CameraCom->OrthoNearClipPlane;
			InOutInfo.OrthoFarClipPlane = CameraCom->OrthoFarClipPlane;
			InOutInfo.AspectRatio = CameraCom->AspectRatio;
			InOutInfo.bConstrainAspectRatio = CameraCom->bConstrainAspectRatio;
			InOutInfo.bUseFieldOfViewForLOD = CameraCom->bUseFieldOfViewForLOD;
			InOutInfo.ProjectionMode = CameraCom->ProjectionMode;
			InOutInfo.PostProcessBlendWeight = CameraCom->PostProcessBlendWeight;
			InOutInfo.PostProcessSettings = CameraCom->PostProcessSettings;
			return;
		}
	}
}
