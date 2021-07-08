// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSCLoadingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SSCLOADINGSCREEN_API USSCLoadingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	static int32 DisplayBackgroundIndex;
	static int32 DisplayTipTextIndex;
	static int32 DisplayMovieIndex;


public:
	//SetDisplayBackgroundManually true
	UFUNCTION(BlueprintCallable, Category = "SSCLoadingScreen")
		static void SetDisplayBackgroundIndex(int32 BackgroundIndex);

	//SetDisplayTipTextManually true
	UFUNCTION(BlueprintCallable, Category = "SSCLoadingScreen")
		static void SetDisplayTipTextIndex(int32 TipTextIndex);

	//SetDisplayMovieIndexManually true
	UFUNCTION(BlueprintCallable, Category = "SSCLoadingScreen")
		static void SetDisplayMovieIndex(int32 MovieIndex);

	//bAllowEngineTick true 
	UFUNCTION(BlueprintCallable, Category = "SSCLoadingScreen")
		static void StopLoadingScreen();

	static inline int32 GetDisplayBackgroundIndex() { return DisplayBackgroundIndex; }
	static inline int32 GetDisplayTipTextIndex() { return DisplayTipTextIndex; }
	static inline int32 GetDisplayMovieIndex() { return DisplayMovieIndex; }



};
