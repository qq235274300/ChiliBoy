// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SSCLOADINGSCREEN_API SSLoadingScreenLayout : public SCompoundWidget
{
public:
	static float PointSizeToSlateUnits(float PointSize);
protected:
	float GetDPIScale() const;
};
