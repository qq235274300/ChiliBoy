// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimpleView.generated.h"



//Camera Info 


UENUM(BlueprintType)
enum class EViewPointType : uint8
{
	BindToController = 0,
	BindToViewTarget,
};

USTRUCT(BlueprintType, Blueprintable,meta = (ShortToolTip = ""))
struct SSCPLUGINS_API  FBindToController
{
public:
	GENERATED_USTRUCT_BODY()	
};

USTRUCT(BlueprintType, Blueprintable, meta = (ShortToolTip = ""))
struct SSCPLUGINS_API FBindToViewTarget
{
public:
	GENERATED_USTRUCT_BODY()
public:
	FBindToViewTarget() {}
	//has be a camera
	void GetViewInfo(FMinimalViewInfo& InOutInfo)const;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		AActor* Target;
};


USTRUCT(BlueprintType, Blueprintable, meta = (ShortToolTip = ""))
struct SSCPLUGINS_API FView
{
public:
	GENERATED_USTRUCT_BODY()
		FView() : LocationAndSizeOnScreen(0.0f, 0.0f, 0.5f, 1.0f) {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
	EViewPointType ViewPointType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews", meta = (EditCondition = "ViewPointType == EViewPointType::BindToController"))
		FBindToController BindToController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews", meta = (EditCondition = "ViewPointType == EViewPointType::BindToViewTarget"))
		FBindToViewTarget BindToViewTargte;
	
	//Uniquely identifies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		FName ViewName;
	// 0 x 1 y 2 with 3 height
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		FVector4 LocationAndSizeOnScreen;



	/********************Adjust***************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		FVector LocationOffsetOfViewPort;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SSCMultiViews")
		FRotator RotationOffsetOfViewPort;
};


UCLASS()
class SSCPLUGINS_API USimpleView : public UObject
{
	GENERATED_BODY()

};
