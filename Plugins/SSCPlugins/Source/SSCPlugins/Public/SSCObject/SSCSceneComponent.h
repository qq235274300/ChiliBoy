// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SSCObjectInterface.h"
#include "SSCSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SSCPLUGINS_API USSCSceneComponent : public USceneComponent , public ISSCObjectInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCSceneComponent();

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
