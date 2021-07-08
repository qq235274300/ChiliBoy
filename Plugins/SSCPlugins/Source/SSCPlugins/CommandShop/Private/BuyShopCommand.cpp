// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyShopCommand.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "MyShopStateSubsystem.h"

#define  GET_SHOP_SUBSYSTEM  UGameplayStatics::GetPlayerController(GEngine->GetWorld(),0)->GetLocalPlayer()->GetSubsystem<UMyShopStateSubsystem>()

void UBuyShopCommand::Execute()
{
	GET_SHOP_SUBSYSTEM->AddGold(Item.Gold);
}

void UBuyShopCommand::Undo()
{
	GET_SHOP_SUBSYSTEM->ReduceGold(Item.Gold);
}
