// Fill out your copyright notice in the Description page of Project Settings.


#include "SplitScreenBPLibrary.h"
#include "SimpleMultiViews.h"
#include "Kismet/GameplayStatics.h"

USplitScreenBPLibrary::USplitScreenBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USplitScreenBPLibrary::GetLocalPlayer(const APlayerController* PlayerController, ULocalPlayer*& LocalPlayer)
{
	if (PlayerController != nullptr)
	{
		LocalPlayer = PlayerController->GetLocalPlayer();
	}
}

void USplitScreenBPLibrary::GetSimpleLocalPlayer(UObject* WorldContextObject, USimpleLocalPlayer*& SimpleLocalPlayer, const int32 PlayerIndex /*= 0*/)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex);
	if (PlayerController != nullptr)
	{
		SimpleLocalPlayer = dynamic_cast<USimpleLocalPlayer*>(PlayerController->GetLocalPlayer());
	}
}

void USplitScreenBPLibrary::SetLocalPlayer(APlayerController* PlayerController, ULocalPlayer* LocalPlayer)
{
	if (PlayerController == nullptr || LocalPlayer == nullptr)
	{
		return;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(PlayerController, EGetWorldErrorMode::ReturnNull);
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	if (GameInstance != nullptr)
	{
		UEngine* Engine = GameInstance->GetEngine();
		ULocalPlayer * LP = PlayerController->GetLocalPlayer();
		if (LP != nullptr)
		{
			LocalPlayerShallowCopy(LP, LocalPlayer);
			LP->ViewportClient = nullptr;
			LP->PlayerController = nullptr;
			GameInstance->RemoveLocalPlayer(LP);
			PlayerController->SetPlayer(LocalPlayer);
			GameInstance->AddLocalPlayer(LocalPlayer, LP->GetControllerId());
		}
		else
		{
			PlayerController->SetPlayer(LocalPlayer);
			GameInstance->AddLocalPlayer(LocalPlayer, 0);
		}
	}
}

void USplitScreenBPLibrary::SetSimpleLocalPlayer(UObject* WorldContextObject, USimpleLocalPlayer* SimpleLocalPlayer, const int32 PlayerIndex /*= 0*/)
{
	if (SimpleLocalPlayer == nullptr)
	{
		return;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	if (GameInstance != nullptr)
	{
		UEngine* Engine = GameInstance->GetEngine();
		bool DidFindOneExistingLocalPlayer = false;
		for (ULocalPlayer * LP : GameInstance->GetLocalPlayers())
		{
			if (LP && (LP->GetControllerId() == PlayerIndex))
			{
				APlayerController* PlayerController = LP->PlayerController;
				LocalPlayerShallowCopy(LP, SimpleLocalPlayer);
				LP->ViewportClient = nullptr;
				LP->PlayerController = nullptr;
				GameInstance->RemoveLocalPlayer(LP);
				PlayerController->SetPlayer(SimpleLocalPlayer);
				DidFindOneExistingLocalPlayer = true;
				GameInstance->AddLocalPlayer(SimpleLocalPlayer, PlayerIndex);
				break;
			}
		}

		if (false == DidFindOneExistingLocalPlayer)
		{

		}
	}
}

void USplitScreenBPLibrary::LocalPlayerShallowCopy(ULocalPlayer* From_LocalPlayer, ULocalPlayer* To_LocalPlayer)
{
	if (From_LocalPlayer == nullptr || To_LocalPlayer == nullptr)
	{
		return;
	}

	To_LocalPlayer->PlayerController = From_LocalPlayer->PlayerController;
	To_LocalPlayer->ViewportClient = From_LocalPlayer->ViewportClient;
	To_LocalPlayer->CurrentNetSpeed = From_LocalPlayer->CurrentNetSpeed;
	To_LocalPlayer->ConfiguredInternetSpeed = From_LocalPlayer->ConfiguredInternetSpeed;
	To_LocalPlayer->ConfiguredLanSpeed = From_LocalPlayer->ConfiguredLanSpeed;
	To_LocalPlayer->CachedUniqueNetId = From_LocalPlayer->CachedUniqueNetId;
	To_LocalPlayer->CachedUniqueNetId = From_LocalPlayer->CachedUniqueNetId;

	To_LocalPlayer->Origin = From_LocalPlayer->Origin;
	To_LocalPlayer->Size = From_LocalPlayer->Size;
	To_LocalPlayer->LastViewLocation = From_LocalPlayer->LastViewLocation;
	To_LocalPlayer->AspectRatioAxisConstraint = From_LocalPlayer->AspectRatioAxisConstraint;
	To_LocalPlayer->PendingLevelPlayerControllerClass = From_LocalPlayer->PendingLevelPlayerControllerClass;
	To_LocalPlayer->bSentSplitJoin = From_LocalPlayer->bSentSplitJoin;
}

void USplitScreenBPLibrary::GetNumOfLocalPlayers(UObject* WorldContextObject, int32& NumOfLocalPlayers)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	if (GameInstance != nullptr)
	{
		NumOfLocalPlayers = GameInstance->GetNumLocalPlayers();
	}
}

void USplitScreenBPLibrary::CreateAndSetLocalPlayer(UObject* WorldContextObject, TSubclassOf<ULocalPlayer> LocalPlayerClass, int32 PlayerIndex, bool CreateNewPlayerController, int32 BindToOtherPlayerIndex, ULocalPlayer*& LocalPlayer)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	if (GameInstance != nullptr)
	{
		UEngine* Engine = GameInstance->GetEngine();
		if (Engine != nullptr)
		{
			TSubclassOf<class ULocalPlayer> LocalPlayerClassTemp = Engine->LocalPlayerClass;
			Engine->LocalPlayerClass = LocalPlayerClass;

			{
				bool DidFindOneExistingLocalPlayer = false;
				for (ULocalPlayer * LP : GameInstance->GetLocalPlayers())
				{
					if (LP && (LP->GetControllerId() == PlayerIndex))
					{
						LocalPlayer = NewObject<ULocalPlayer>(Engine, Engine->LocalPlayerClass);
						LocalPlayerShallowCopy(LP, LocalPlayer);
						LP->ViewportClient = nullptr;
						LP->PlayerController = nullptr; 
						GameInstance->RemoveLocalPlayer(LP);
						LocalPlayer->PlayerController->SetPlayer(LocalPlayer);
						DidFindOneExistingLocalPlayer = true;
						GameInstance->AddLocalPlayer(LocalPlayer, PlayerIndex);
						break;
					}
				}
				//世界中没有对应玩家
				if (false == DidFindOneExistingLocalPlayer)
				{
					APlayerController* PlayerController = nullptr;
					bool DidFindOnePlayerController = false;
					if (!CreateNewPlayerController)
					{
						for (ULocalPlayer * LP : GameInstance->GetLocalPlayers())
						{
							if (LP && (LP->GetControllerId() == BindToOtherPlayerIndex))
							{
								if (LP->PlayerController != nullptr)
								{
									PlayerController = LP->PlayerController;
									DidFindOnePlayerController = true;
									break;
								}
							}
						}
						BindToOtherPlayerIndex = 0;
						if (!DidFindOnePlayerController)
						{
							for (ULocalPlayer * LP : GameInstance->GetLocalPlayers())
							{
								if (LP && (LP->GetControllerId() == BindToOtherPlayerIndex))
								{
									if (LP->PlayerController != nullptr)
									{
										PlayerController = LP->PlayerController;
										DidFindOnePlayerController = true;
										break;
									}
								}
							}
						}
						if (!DidFindOnePlayerController)
						{
							const TArray<class ULocalPlayer*> LocalPlayers = GameInstance->GetLocalPlayers();
							if (LocalPlayers.Num() > 0 && LocalPlayers[0] != nullptr && LocalPlayers[0]->PlayerController != nullptr)
							{
								PlayerController = LocalPlayers[0]->PlayerController;
								DidFindOnePlayerController = true;
							}
						}

						if (false == DidFindOnePlayerController || nullptr == PlayerController)
						{
							CreateNewPlayerController = true;
						}

					}
					FString OutError;
					LocalPlayer = GameInstance->CreateLocalPlayer(PlayerIndex, OutError, CreateNewPlayerController);
					if (!CreateNewPlayerController)
					{
						PlayerController->SetPlayer(LocalPlayer);
					}
				}
			}
			Engine->LocalPlayerClass = LocalPlayerClassTemp;
		}
	}
}
