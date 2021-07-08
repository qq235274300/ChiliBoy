// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShopStack.h"

void UMyShopStack::Push(UCommandShopBase* Command)
{
	if (Command)
		CommandArray.Push(Command);
}

UCommandShopBase* UMyShopStack::Pop()
{
	if (CommandArray.Num() > 0)
	{
		int32 LastIndex = CommandArray.Num() - 1;
		UCommandShopBase* tempCommand = CommandArray[LastIndex];
		CommandArray.RemoveAt(LastIndex);
		return tempCommand;
	}

	return nullptr;
}
