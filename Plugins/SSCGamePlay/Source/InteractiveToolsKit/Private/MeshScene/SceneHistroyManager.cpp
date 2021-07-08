// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshScene/SceneHistroyManager.h"
#include "HelperKits/Public/DebugHelper.h"

bool FChangeHistroyTransaction::HasExpired() const
{
	for (const FChangeHistroyRecord& Record : Records)
	{
		if (Record.ChangeWrapper->Change->HasExpired(Record.TargetObject) == false)
		{
			return false;
		}
	}

	return true;
}

void USceneHistroyManager::BeginTransaction(const FText& Description)
{
	if (BeginTransactionDepth != 0)
	{
		BeginTransactionDepth++;
		return;
	}
	else
	{
		TruncateHistory();	
		ActiveTransaction = FChangeHistroyTransaction();
		ActiveTransaction.Description = Description;
		BeginTransactionDepth++;
		
	}
}

void USceneHistroyManager::AppendChange(UObject* TargetObject, TUniquePtr<FCommandChange> CommandChange, const FText& Description)
{
	bool bAutoCloseTransaction = false;
	if (ensure(BeginTransactionDepth > 0) == false)
	{
		BeginTransaction(Description);
		bAutoCloseTransaction = true;
	}

	FChangeHistroyRecord Record;
	Record.TargetObject = TargetObject;
	Record.Description = Description;
	Record.ChangeWrapper = MakeShared<FChangeHistroyRecord::FChangeWrapper>();
	Record.ChangeWrapper->Change = MoveTemp(CommandChange);

	DebugHelper::Count() << Description << DebugHelper::Endl();

	ActiveTransaction.Records.Add(MoveTemp(Record));
	if (bAutoCloseTransaction)
	{
		EndTransaction();
	}

}

void USceneHistroyManager::EndTransaction()
{
	if (ensure(BeginTransactionDepth > 0) == false) return;
	BeginTransactionDepth--;

	if (BeginTransactionDepth == 0)
	{
		if (ActiveTransaction.Records.Num() > 0)
		{
			Transactions.Add(MoveTemp(ActiveTransaction));
		}
		else
		{
			DebugHelper::Count() << "EndTransaction --> Empty Transaction Record" << DebugHelper::Endl();
		}

		ActiveTransaction = FChangeHistroyTransaction();
		CurrentIndex = Transactions.Num();
	}
	
}

void USceneHistroyManager::Undo()
{
	int32 NumReverted = 0;
	while (CurrentIndex > 0 )
	{
		CurrentIndex = CurrentIndex - 1;
		DebugHelper::Count() << Transactions[CurrentIndex].Description << DebugHelper::Endl();

		bool bContinue = Transactions[CurrentIndex].HasExpired();
		const TArray<FChangeHistroyRecord>& Records = Transactions[CurrentIndex].Records;
		
		for (int32 k = Records.Num() - 1; k >= 0; --k)
		{
			if (Records[k].TargetObject)
			{
				Records[k].ChangeWrapper->Change->Revert(Records[k].TargetObject);
			}
			NumReverted++;
		}
		if (!bContinue)
		{
			return;
		}
	}

	if (NumReverted > 0)
	{
		SceneHistroyStateChange.Broadcast();
	}
}

void USceneHistroyManager::Redo()
{
	int32 NumApplied = 0;
	while (CurrentIndex < Transactions.Num())
	{
		bool bContinue = Transactions[CurrentIndex].HasExpired();
		const TArray<FChangeHistroyRecord>& Records = Transactions[CurrentIndex].Records;
		for (int32 k = 0; k < Records.Num(); ++k)
		{
			if (Records[k].TargetObject)
			{
				Records[k].ChangeWrapper->Change->Apply(Records[k].TargetObject);
			}
			++NumApplied;		
		}
		DebugHelper::Count() << Transactions[CurrentIndex].Description << DebugHelper::Endl();
		CurrentIndex = CurrentIndex + 1;
		
		if (!bContinue)
		{
			return;
		}
	}
	if (NumApplied > 0)
	{
		SceneHistroyStateChange.Broadcast();
	}
	
}

void USceneHistroyManager::TruncateHistory()
{
	//If undo state Truncate
	if (CurrentIndex < Transactions.Num())
	{
		Transactions.SetNum(CurrentIndex);
	}
}
