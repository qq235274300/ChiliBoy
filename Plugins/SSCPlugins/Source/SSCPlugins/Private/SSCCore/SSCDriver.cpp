// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCDriver.h"
#include "Components/SceneComponent.h"
#include "SSCObjectInterface.h"
#include "Kismet/GameplayStatics.h"
#include "SSCGameInstance.h"
#include "Engine/GameInstance.h"
#include "SSCPlayerController.h"

// Sets default values
ASSCDriver::ASSCDriver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Center = CreateDefaultSubobject<USSCCenterModule>(TEXT("Center"));
	Center->SetupAttachment(Root);

	

}

void ASSCDriver::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!GetWorld())return;
	USSCCommon::Get()->SetDirver(this);
	USSCCommon::Get()->SetCurrentWorld(GetWorld());
	
	Center->IterGetModuleChildren(Center,ModuleType);
	Center->GatherModule(ModuleType);
	Center->IterCreateSubModule(Center);
}

// Called when the game starts or when spawned
void ASSCDriver::BeginPlay()
{
	Super::BeginPlay();
	RegisterGamePlay();
	Center->IterModuleInit(Center);

}

void ASSCDriver::RegisterGamePlay()
{
	UGameInstance* tmpGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	//bug fixel later
	if (tmpGameInstance && Cast<USSCGameInstance>(tmpGameInstance))
	{
		Cast<USSCGameInstance>(tmpGameInstance)->RegisterToModule("Center", "SSCGameInstance", "SSCGameInstance");
	}

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		USSCCommon::Get()->SetPlayerController(playerController);
	}
	else
	{
		SSCHelper::Debug() << "No PlayerController In The Game" << SSCHelper::Endl();
	}
}

#if WITH_EDITOR
void ASSCDriver::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property && PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASSCDriver, ModuleType))
	{
		Center->IterGetModuleChildren(Center, ModuleType);
	}
}
#endif
bool ASSCDriver::RegisterObject(ISSCObjectInterface* Object)
{
	return Center->RegisterObject(Object);
}

void ASSCDriver::ProcessModuleReflectFuncEvnt(FModuleFunctionAgrement Agrement, FRelfectFuncParam* _Param)
{
	Center->ProcessModuleReflectFuncEvnt(Agrement, _Param);
}

void ASSCDriver::ProcessObjectReflectFuncEvnt(FObjectFunctionAgrement Agrement, FRelfectFuncParam* _Param)
{
	Center->ProcessObjectReflectFuncEvnt(Agrement, _Param);
}



// Called every frame
void ASSCDriver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bModuleHasBeginPlay)
	{
		Center->IterModuleBeginPlay(Center);
		bModuleHasBeginPlay = true;
	}
	else
	{
		Center->IterModuleTick(Center, DeltaTime);
	}
}

