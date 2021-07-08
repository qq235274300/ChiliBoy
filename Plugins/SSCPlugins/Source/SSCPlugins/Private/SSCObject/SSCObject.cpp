// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCObject.h"

void USSCObject::ModelRelease()
{
	ISSCObjectInterface::ModelRelease();
	RemoveFromRoot();
	ConditionalBeginDestroy();
}
