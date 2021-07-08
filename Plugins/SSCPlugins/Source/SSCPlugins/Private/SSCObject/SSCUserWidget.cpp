// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCUserWidget.h"

void USSCUserWidget::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	
	RemoveFromParent();
	RemoveFromRoot();
	ConditionalBeginDestroy();
}
