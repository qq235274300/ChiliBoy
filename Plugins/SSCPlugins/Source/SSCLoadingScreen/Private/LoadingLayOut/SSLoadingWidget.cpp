// Fill out your copyright notice in the Description page of Project Settings.


#include "SSLoadingWidget.h"
#include "SlateOptMacros.h"



EActiveTimerReturnType SSLoadingWidget::AnimatingImageSequence(double InCurrentTime, float InDeltaTime)
{
	if (CleanupBrushList.Num() > 1)
	{
		if (bPlayReverse)
		{
			ImageIndex--;
		}
		else
		{
			ImageIndex++;
		}

		if (ImageIndex >= CleanupBrushList.Num())
		{
			ImageIndex = 0;
		}
		else if (ImageIndex < 0)
		{
			ImageIndex = CleanupBrushList.Num() - 1;
		}

		StaticCastSharedRef<SImage>(LoadingIcon)->SetImage(CleanupBrushList[ImageIndex].IsValid() ? CleanupBrushList[ImageIndex]->GetSlateBrush() : nullptr);

		return EActiveTimerReturnType::Continue;
	}
	else
	{
		bIsActiveTimerRegistered = false;
		return EActiveTimerReturnType::Stop;
	}

}



SThrobber::EAnimation SSLoadingWidget::GetThrobberAnimation(FThrobberSettings ThrobberSettings) const
{
	const int32 AnimationParams = (ThrobberSettings.bAnimateVertically ? SThrobber::Vertical : 0) |
		(ThrobberSettings.bAnimateHorizontally ? SThrobber::Horizontal : 0) |
		(ThrobberSettings.bAnimateOpacity ? SThrobber::Opacity : 0);

	return static_cast<SThrobber::EAnimation>(AnimationParams);

}

void SSLoadingWidget::ConstructLoadingIcon(const FLoadingWidgetSettings& Settings)
{
	if (Settings.LoadingIconType == ELoadingIconType::LIT_ImageSequence)
	{
		// Loading Widget is image sequence
		if (Settings.ImageSequenceSettings.Images.Num() > 0)
		{
			CleanupBrushList.Empty();
			ImageIndex = 0;

			FVector2D Scale = Settings.ImageSequenceSettings.Scale;

			for (auto Image : Settings.ImageSequenceSettings.Images)
			{
				if (Image)
				{
					CleanupBrushList.Add(FDeferredCleanupSlateBrush::CreateBrush(Image, FVector2D(Image->GetSurfaceWidth() * Scale.X, Image->GetSurfaceHeight() * Scale.Y)));
				}
			}

			// Create Image slate widget
			LoadingIcon = SNew(SImage)
				.Image(CleanupBrushList[ImageIndex]->GetSlateBrush());

			// Register animated image sequence active timer event
			if (!bIsActiveTimerRegistered)
			{
				bIsActiveTimerRegistered = true;
				RegisterActiveTimer(Settings.ImageSequenceSettings.Interval, FWidgetActiveTimerDelegate::CreateSP(this, &SSLoadingWidget::AnimatingImageSequence));
			}
		}
		else
		{
			// If there is no image in the array then create a spacer instead
			LoadingIcon = SNew(SSpacer).Size(FVector2D::ZeroVector);
		}

	}
	else if (Settings.LoadingIconType == ELoadingIconType::LIT_CircularThrobber)
	{
		// Loading Widget is SCircularThrobber
		LoadingIcon = SNew(SCircularThrobber)
			.NumPieces(Settings.CircularThrobberSettings.NumberOfPieces)
			.Period(Settings.CircularThrobberSettings.Period)
			.Radius(Settings.CircularThrobberSettings.Radius)
			.PieceImage(&Settings.CircularThrobberSettings.Image);
	}
	else
	{
		// Loading Widget is SThrobber
		LoadingIcon = SNew(SThrobber)
			.NumPieces(Settings.ThrobberSettings.NumberOfPieces)
			.Animate(GetThrobberAnimation(Settings.ThrobberSettings))
			.PieceImage(&Settings.ThrobberSettings.Image);
	}

	// Set Loading Icon render transform
	LoadingIcon.Get().SetRenderTransform(FSlateRenderTransform(FScale2D(Settings.TransformScale), Settings.TransformTranslation));
	LoadingIcon.Get().SetRenderTransformPivot(Settings.TransformPivot);
}
