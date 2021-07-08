// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "SimpleLocalPlayer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SplitScreenBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USplitScreenBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetLocalPlayer"), Category = "SSCMultiViews")
		static void GetLocalPlayer(const APlayerController* PlayerController, ULocalPlayer*& LocalPlayer);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetSimpleLocalPlayer", WorldContext = "WorldContextObject"), Category = "SSCMultiViews")
		static void GetSimpleLocalPlayer(UObject* WorldContextObject, USimpleLocalPlayer*& SimpleLocalPlayer, const int32 PlayerIndex = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetLocalPlayer"), Category = "SSCMultiViews")
		static void SetLocalPlayer(APlayerController* PlayerController, ULocalPlayer* LocalPlayer);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetSimpleLocalPlayer", WorldContext = "WorldContextObject"), Category = "SSCMultiViews")
		static void SetSimpleLocalPlayer(UObject* WorldContextObject, USimpleLocalPlayer* SimpleLocalPlayer, const int32 PlayerIndex = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LocalPlayerShallowCopy"), Category = "SSCMultiViews")
		static void LocalPlayerShallowCopy(ULocalPlayer* From_LocalPlayer, ULocalPlayer* To_LocalPlayer);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetNumOfLocalPlayers", WorldContext = "WorldContextObject"), Category = "SSCMultiViews")
		static void GetNumOfLocalPlayers(UObject* WorldContextObject, int32& NumOfLocalPlayers);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMaxNumOfViews"), Category = "SSCMultiViews")
		static int32 GetMaxNumOfViews()
	{
		return USimpleLocalPlayer::MaxNumOfViews;
	}

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateAndSetLocalPlayer", WorldContext = "WorldContextObject"), Category = "SSCMultiViews")
		static void CreateAndSetLocalPlayer(UObject* WorldContextObject, TSubclassOf<ULocalPlayer> LocalPlayerClass, int32 PlayerIndex, bool CreateNewPlayerController, int32 BindToOtherPlayerIndex, ULocalPlayer*& LocalPlayer);
};
