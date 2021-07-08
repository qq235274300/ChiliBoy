// Fill out your copyright notice in the Description page of Project Settings.


#include "SSBackgroundWidget.h"
#include "SlateOptMacros.h"
#include "LoadingSettingTypes.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "SSCLoadingFunctionLibrary.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSBackgroundWidget::Construct(const FArguments& InArgs, FBackgroundSettings Settings)
{

	if (Settings.Images.Num() > 0)
	{
		int32 ImageIndex = FMath::RandRange(0, Settings.Images.Num() - 1);

		if (Settings.bSetDisplayBackgroundManually == true)
		{
			if (Settings.Images.IsValidIndex(USSCLoadingFunctionLibrary::GetDisplayBackgroundIndex()))
			{
				ImageIndex = USSCLoadingFunctionLibrary::GetDisplayBackgroundIndex();
			}
		}

		const FSoftObjectPath& ImageAsset = Settings.Images[ImageIndex];
		UObject* ImageObject = ImageAsset.TryLoad();
		if (UTexture2D* LoadingImage = Cast<UTexture2D>(ImageObject))
		{
			ImageBrush = FDeferredCleanupSlateBrush::CreateBrush(LoadingImage);
			ChildSlot
				[
					SNew(SBorder)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(Settings.Padding)
					.BorderBackgroundColor(Settings.BackgroundColor)
					.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
				[
					SNew(SScaleBox)
					.Stretch(Settings.ImageStretch)
				[
					SNew(SImage)
					.Image(ImageBrush.IsValid() ? ImageBrush->GetSlateBrush() : nullptr)
				]
				]
				];
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
