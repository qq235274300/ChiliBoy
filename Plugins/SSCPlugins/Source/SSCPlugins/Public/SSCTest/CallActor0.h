// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCActor.h"
#include "CallActor0.generated.h"

//struct AnyElement
//{
//	struct BaseElement
//	{
//		virtual ~BaseElement() {}
//	};
//	
//	template<typename T>
//	struct ValueElement : public BaseElement
//	{
//	public:
//		
//		T Value;
//		ValueElement(const T& _Value) :Value(_Value) {};		
//	};
//
//	BaseElement* ElementPtr;
//	
//	AnyElement() : ElementPtr(nullptr) {}
//	template<typename T>
//	AnyElement(const T& _Value) : ElementPtr(new ValueElement<T>(_Value)) {}
//	~AnyElement() { delete ElementPtr; ElementPtr = nullptr; }
//	template<typename T>
//	T Get()const 
//	{
//		ValueElement<T>* ValuePtr = static_cast<ValueElement<T>*>(ElementPtr);
//		return ValuePtr->Value;
//	}
//};



UCLASS()
class SSCPLUGINS_API ACallActor0 : public ASSCActor
{
	GENERATED_BODY()
public:
	ACallActor0();
	virtual void ModelEnable()override;

//protected:
//	TArray<AnyElement*> ElementArray;
};
