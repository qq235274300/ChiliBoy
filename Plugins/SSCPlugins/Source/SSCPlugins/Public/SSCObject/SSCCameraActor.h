// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SSCObjectInterface.h"
#include "SSCCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API ASSCCameraActor : public ACameraActor ,public ISSCObjectInterface
{
	GENERATED_BODY()
public:
	ASSCCameraActor();
public:
	virtual void ModelRelease()override;

protected:
	virtual void BeginPlay()override;

public:
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ModuleName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ObjectName;
	UPROPERTY(EditAnywhere, Category = "SSCObject")
		FName ClassName;

};
