// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SceneHistroyManager.generated.h"

/**
 * 
 */

USTRUCT()
struct FChangeHistroyRecord
{
	GENERATED_BODY()

public:
	UPROPERTY()
		UObject* TargetObject = nullptr;
	UPROPERTY()
		FText Description;

	struct FChangeWrapper
	{
		TUniquePtr<FCommandChange> Change;
		
	};
	
	TSharedPtr<FChangeWrapper> ChangeWrapper;
};


USTRUCT()
struct FChangeHistroyTransaction
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FChangeHistroyRecord> Records;
	UPROPERTY()
	FText Description;
	
	bool HasExpired()const;
};



UCLASS()
class INTERACTIVETOOLSKIT_API USceneHistroyManager : public UObject
{
	GENERATED_BODY()
	
public:
	void BeginTransaction(const FText& Description);
	void AppendChange( UObject* TargetObject, TUniquePtr<FCommandChange> CommandChange,const  FText& Description);
	void EndTransaction();

	UFUNCTION(BlueprintCallable)
		bool IsBuildingTransaction()const { return BeginTransactionDepth > 0; }
	UFUNCTION(BlueprintCallable)
		void Undo();
	UFUNCTION(BlueprintCallable)
		void Redo();
	DECLARE_MULTICAST_DELEGATE(FSceneHistroyStateChangeEvent)
	FSceneHistroyStateChangeEvent SceneHistroyStateChange;
private:
	//Undo Histroy
	UPROPERTY()
		TArray<FChangeHistroyTransaction> Transactions;

	// remove any elements of Transactions list beyond CurrentIndex (called if we are in Undo state and a new transaction is opened)
	void TruncateHistory();
	UPROPERTY()
	FChangeHistroyTransaction ActiveTransaction;
	int BeginTransactionDepth = 0;
	int32 CurrentIndex;
};
