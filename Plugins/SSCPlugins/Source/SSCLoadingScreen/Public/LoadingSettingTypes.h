// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MoviePlayer.h"
#include "Styling/SlateBrush.h"
#include "Framework/Text/TextLayout.h"
#include "Engine/Font.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBorder.h"
#include "Engine/Texture2D.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SOverlay.h"
#include "LoadingSettingTypes.generated.h"


#define LOCTEXT_NAMESPACE "LoadingSettingTypes"
/**
 * 
 */
UCLASS()
class SSCLOADINGSCREEN_API ULoadingSettingTypes : public UObject
{
	GENERATED_BODY()
	
};

#pragma region LodingCompleteText

/*****************加载完成时不自动退出时候，设置显示的文字*********************************************/

USTRUCT(BlueprintType)
struct FTextAppearance
{
	GENERATED_BODY()
		
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "Text Appearance")
		FSlateColor ColorAndOpacity = FSlateColor(FLinearColor::White);
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "Text Appearance")
		FSlateFontInfo Font;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "Text Appearance")
		FVector2D ShadowOffset;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "Text Appearance")
		FLinearColor ShadowColorAndOpacity;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "Text Appearance")
		TEnumAsByte <ETextJustify::Type> Justification;
};


USTRUCT(BlueprintType)
struct FWidgetAlignment
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alignment Setting")
		TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Center;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alignment Setting")
		TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Center;
};


USTRUCT(BlueprintType)
struct SSCLOADINGSCREEN_API FLoadingCompleteTextSettings
{
	GENERATED_BODY()

	FLoadingCompleteTextSettings() :LoadingCompleteText(LOCTEXT("Loading", "Press any key to continue...")) {};
	//显示文字
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Complete Text Settings")
		FText LoadingCompleteText;
	//显示字体
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Complete Text Settings")
		FTextAppearance Appearance;
	//显示布局
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Widget Setting")
		FWidgetAlignment Alignment;
	//显示布局
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Complete Text Settings")
		FMargin Padding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Complete Text Settings")
		bool bFadeInFadeOutAnim = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Complete Text Settings", meta = (UIMax = 10.00, UIMin = 0.00, ClampMin = "0", ClampMax = "10"))
		float AnimationSpeed = 1.0f;
};





#pragma endregion

#pragma region LodingWidgetLayout
UENUM(BlueprintType)
enum class EAsyncLoadingScreenLayout : uint8
{

	//预制的布局
	/**
	 * The Classic is a simple, generic layout and fits well with many designs.
	 * Loading and tip widgets can be at the bottom or top.
	 */
	ALSL_Classic UMETA(DisplayName = "Classic"),
	/**
	 * The loading widget is at the center of the screen, tip widget can be at the bottom or top.
	 * The Center layout is a good choice if your loading icon is the main design.
	 */
	ALSL_Center UMETA(DisplayName = "Center"),
	/**
	 * The Letterbox layout has two borders on top and bottom of the screen. Loading widget
	 * can be on the top and the tip is at the bottom of the screen, or vice versa.
	 */
	ALSL_Letterbox UMETA(DisplayName = "Letterbox"),
	/**
	 * The Sidebar layout has a vertical border on the left or right of the screen. The Sidebar
	 * is suitable for storytelling, long paragraphs due to the height of the tip widget.
	 */
	ALSL_Sidebar UMETA(DisplayName = "Sidebar"),

	/**
	 * Similar to Sidebar layout but Dual Sidebar layout has two vertical borders on both left and right of the screen.
	 * The Dual Sidebar layout is suitable for storytelling, long paragraphs due to the height of the tip widget.
	 */
	ALSL_DualSidebar UMETA(DisplayName = "Dual Sidebar")
};

/** Classic Layout settings*/
USTRUCT(BlueprintType)
struct FClassicLayoutSettings
{
	GENERATED_BODY()

		/** Is the border that contains loading and tip widget located at the bottom or top? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classic Layout")
		bool bIsWidgetAtBottom = true;

	/** Is loading widget on the left of the tip? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classic Layout")
		bool bIsLoadingWidgetAtLeft = true;

	/** The empty space between loading widget and the tip.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classic Layout")
		float Space = 1.0f;

	/** The alignment of the tips. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classic Layout")
		FWidgetAlignment TipAlignment;

	/** The horizontal alignment of the border background.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Center Layout")
		TEnumAsByte<EHorizontalAlignment> BorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** The padding area between the border and the widget it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classic Layout")
		FMargin BorderPadding;

	/** Background appearance settings for the border widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classic Layout")
		FSlateBrush BorderBackground;
};

/** Center Layout settings*/
USTRUCT(BlueprintType)
struct FCenterLayoutSettings
{
	GENERATED_BODY()

		/** Is tip located at the bottom or top? */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Center Layout")
		bool bIsTipAtBottom = true;

	/** The alignment of the tips. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Center Layout")
		FWidgetAlignment TipAlignment;

	/** The horizontal alignment of the border.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Center Layout")
		TEnumAsByte<EHorizontalAlignment> BorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** Offset to bottom or top of the screen depending on the tip located at the bottom or top position.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Center Layout")
		float BorderVerticalOffset = 0.0f;

	/** The padding area between the border and the tips it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Center Layout")
		FMargin BorderPadding;

	/** Background appearance settings for tip area */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Center Layout")
		FSlateBrush BorderBackground;
};

/** Letterbox Layout settings*/
USTRUCT(BlueprintType)
struct FLetterboxLayoutSettings
{
	GENERATED_BODY()

		/** Is loading widget located at the bottom or top? */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Letterbox Layout")
		bool bIsLoadingWidgetAtTop = true;

	/** The alignment of the tips. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Letterbox Layout")
		FWidgetAlignment TipAlignment;

	/** The alignment of the loading widget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Letterbox Layout")
		FWidgetAlignment LoadingWidgetAlignment;

	/** The horizontal alignment of the top border.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Letterbox Layout")
		TEnumAsByte<EHorizontalAlignment> TopBorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** The horizontal alignment of the bottom border.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Letterbox Layout")
		TEnumAsByte<EHorizontalAlignment> BottomBorderHorizontalAlignment = EHorizontalAlignment::HAlign_Fill;

	/** The top padding area between the border and the widget it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Letterbox Layout")
		FMargin TopBorderPadding;

	/** The bottom padding area between the border and the widget it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Letterbox Layout")
		FMargin BottomBorderPadding;

	/** Background appearance settings for top border */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Letterbox Layout")
		FSlateBrush TopBorderBackground;

	/** Background appearance settings for bottom border */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Letterbox Layout")
		FSlateBrush BottomBorderBackground;
};

/** Sidebar Layout settings*/
USTRUCT(BlueprintType)
struct FSidebarLayoutSettings
{
	GENERATED_BODY()

		/** Is the border that contains loading and tip widgets located at the right or left? */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		bool bIsWidgetAtRight = true;

	/** Is loading widget on the top of the tip? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		bool bIsLoadingWidgetAtTop = true;

	/** The empty space between loading widget and the tip.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		float Space = 1.0f;

	/** The vertical alignment of the vertical box that contains loading/tip widgets. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Center;

	/** The alignment of the loading widget. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sidebar Layout")
		FWidgetAlignment LoadingWidgetAlignment;

	/** The alignment of the tips. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sidebar Layout")
		FWidgetAlignment TipAlignment;

	/** The vertical alignment of the border background that contains all widgets. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		TEnumAsByte<EVerticalAlignment> BorderVerticalAlignment = EVerticalAlignment::VAlign_Fill;

	/** Offset to left or right of the screen depending on the border that contains loading and tip widgets located at the left or right position.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		float BorderHorizontalOffset = 0.0f;

	/** The padding area between the border and the widget it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		FMargin BorderPadding;

	/** Background appearance settings for the border widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sidebar Layout")
		FSlateBrush BorderBackground;
};

/** Dual Sidebar Layout settings*/
USTRUCT(BlueprintType)
struct FDualSidebarLayoutSettings
{
	GENERATED_BODY()

		/** Is loading widget on the right or left border? */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		bool bIsLoadingWidgetAtRight = true;

	/** The vertical alignment of the left widget. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		TEnumAsByte<EVerticalAlignment> LeftVerticalAlignment = EVerticalAlignment::VAlign_Center;

	/** The vertical alignment of the right widget. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		TEnumAsByte<EVerticalAlignment> RightVerticalAlignment = EVerticalAlignment::VAlign_Center;

	/** The vertical alignment of the left border background that contains all widgets. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		TEnumAsByte<EVerticalAlignment> LeftBorderVerticalAlignment = EVerticalAlignment::VAlign_Fill;

	/** The vertical alignment of the right border background that contains all widgets. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		TEnumAsByte<EVerticalAlignment> RightBorderVerticalAlignment = EVerticalAlignment::VAlign_Fill;

	/** The padding area between the left border and the widget it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		FMargin LeftBorderPadding;

	/** The padding area between the right border and the widget it contains.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		FMargin RightBorderPadding;

	/** Background appearance settings for the left border widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		FSlateBrush LeftBorderBackground;

	/** Background appearance settings for the right border widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dual Sidebar Layout")
		FSlateBrush RightBorderBackground;
};


#pragma endregion


#pragma region LoadingMoivesSetting


#pragma endregion



#pragma region LodingWidget






USTRUCT(BlueprintType)
struct SSCLOADINGSCREEN_API FTipSettings
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tip Settings", meta = (MultiLine = true))
		TArray<FText> TipText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tip Settings")
		FTextAppearance Appearance;

	// The size of the tip before it's wrapped to the next line
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tip Settings")
		float TipWrapAt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
		bool bSetDisplayTipTextManually = false;
};

USTRUCT(BlueprintType)
struct SSCLOADINGSCREEN_API FBackgroundSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background", meta = (AllowedClasses = "Texture2D"))
		TArray<FSoftObjectPath> Images;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
		TEnumAsByte<EStretch::Type> ImageStretch = EStretch::ScaleToFit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
		FMargin Padding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
		FLinearColor BackgroundColor = FLinearColor::Black;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Background")
		bool bSetDisplayBackgroundManually = false;
};

UENUM(BlueprintType)
enum class ELoadingIconType : uint8
{
	
	LIT_Throbber UMETA(DisplayName = "Throbber"),
	LIT_CircularThrobber UMETA(DisplayName = "Circular Throbber"),
	LIT_ImageSequence UMETA(DisplayName = "Image Sequence")
};

UENUM(BlueprintType)
enum class ELoadingWidgetType : uint8
{
	LWT_Horizontal UMETA(DisplayName = "Horizontal"),
	LWT_Vertical UMETA(DisplayName = "Vertical"),
};

USTRUCT(BlueprintType)
struct FThrobberSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (ClampMin = "1", ClampMax = "25", UIMin = "1", UIMax = "25"))
		int32 NumberOfPieces = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		bool bAnimateHorizontally = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		bool bAnimateVertically = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		bool bAnimateOpacity = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateBrush Image;
};

USTRUCT(BlueprintType)
struct FCircularThrobberSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance, meta = (ClampMin = "1", ClampMax = "25", UIMin = "1", UIMax = "25"))
		int32 NumberOfPieces = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance, meta = (ClampMin = "0", UIMin = "0"))
		float Period = 0.75f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		float Radius = 64.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
		FSlateBrush Image;
};

USTRUCT(BlueprintType)
struct FImageSequenceSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (AllowedClasses = "Texture2D"))
		TArray<UTexture2D*> Images;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		FVector2D Scale = FVector2D(1.0f, 1.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (UIMax = 1.00, UIMin = 0.00, ClampMin = "0", ClampMax = "1"))
		float Interval = 0.05f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		bool bPlayReverse = false;
};


USTRUCT(BlueprintType)
struct SSCLOADINGSCREEN_API FLoadingWidgetSettings
{
	GENERATED_BODY()

		FLoadingWidgetSettings() : LoadingText(LOCTEXT("Loading", "LOADING")) {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		ELoadingIconType LoadingIconType = ELoadingIconType::LIT_CircularThrobber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		ELoadingWidgetType LoadingWidgetType = ELoadingWidgetType::LWT_Horizontal;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (DisplayName = "IconPos"))
		FVector2D TransformTranslation = FVector2D(0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (DisplayName = "IconScale"))
		FVector2D TransformScale = FVector2D(1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (DisplayName = "IconPivot"))
		FVector2D TransformPivot = FVector2D(0.5f, 0.5f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting" ,meta = (DisplayName = "TextBesideIcon"))
		FText LoadingText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (DisplayName = "OnIconRight"))
		bool bLoadingTextRightPosition = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting", meta = (DisplayName = "OnIconTop"))
		bool bLoadingTextTopPosition = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tip Settings")
		FTextAppearance Appearance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		FThrobberSettings ThrobberSettings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		FCircularThrobberSettings CircularThrobberSettings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Loading Widget Setting")
		FImageSequenceSettings ImageSequenceSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Widget Setting")
		FWidgetAlignment TextAlignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Widget Setting")
		FWidgetAlignment LoadingIconAlignment;

	/** Empty space between the loading text and the loading icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Widget Setting")
		float Space = 1.0f;
};


#pragma endregion



#undef LOCTEXT_NAMESPACE