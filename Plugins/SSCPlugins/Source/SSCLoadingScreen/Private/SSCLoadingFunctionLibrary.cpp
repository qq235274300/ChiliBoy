// Fill out your copyright notice in the Description page of Project Settings.


#include "SSCLoadingFunctionLibrary.h"
#include "MoviePlayer.h"

int32 USSCLoadingFunctionLibrary::DisplayBackgroundIndex = -1;
int32 USSCLoadingFunctionLibrary::DisplayTipTextIndex = -1;
int32 USSCLoadingFunctionLibrary::DisplayMovieIndex = -1;

void USSCLoadingFunctionLibrary::SetDisplayBackgroundIndex(int32 BackgroundIndex)
{
	USSCLoadingFunctionLibrary::DisplayBackgroundIndex = BackgroundIndex;
}

void USSCLoadingFunctionLibrary::SetDisplayTipTextIndex(int32 TipTextIndex)
{
	USSCLoadingFunctionLibrary::DisplayTipTextIndex = TipTextIndex;
}

void USSCLoadingFunctionLibrary::SetDisplayMovieIndex(int32 MovieIndex)
{
	USSCLoadingFunctionLibrary::DisplayMovieIndex = MovieIndex;
}

void USSCLoadingFunctionLibrary::StopLoadingScreen()
{
	GetMoviePlayer()->StopMovie();
}
