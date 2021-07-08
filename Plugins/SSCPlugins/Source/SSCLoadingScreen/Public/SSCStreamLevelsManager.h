// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


class UVisualLoadingProgressWidget;
//#include "SSCStreamLevelsManager.generated.h"


/**
 * 
 */
#define LOCTEXT_NAMESPACE "StreamLevelsManager"

class SSCLOADINGSCREEN_API USSCStreamLevelsManager : public TSharedFromThis<USSCStreamLevelsManager>
{	
public:
	USSCStreamLevelsManager();
	
private:
	static TSharedPtr<USSCStreamLevelsManager> LevelsManagerInstance;
public:
	static TSharedPtr<USSCStreamLevelsManager> Get();

	void StartLoadStreamingLevel(UWorld* _World);


public:
	UPROPERTY()
	UVisualLoadingProgressWidget* LoadingWidget;
};


#undef LOCTEXT_NAMESPACE