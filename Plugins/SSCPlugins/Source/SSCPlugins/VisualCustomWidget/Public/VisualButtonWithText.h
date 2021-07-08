
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VisualWidgetPoolTemplate.h"
#include "VisualButtonWithText.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickButtonTextWithStrDelegate,FString,str);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickButtonTextWithInt32Delegate,int32,index);

USTRUCT(BlueprintType)
struct FButtonWithTextData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CustomData")
	FString str;
	UPROPERTY(EditAnywhere, Category = "CustomData")
	int32 num = 0;

	
	FButtonWithTextData() {}

	FButtonWithTextData(FString _str) :str(_str) {}

	FButtonWithTextData(FString _str,int32 _num) :str(_str),num(_num){}

};

UCLASS()
class SSCPLUGINS_API UButtonWithTextWidget : public UUserWidget , public IVisualWidgetInterface
{
	GENERATED_BODY()
public:
	virtual bool Initialize()override;
	virtual void BeginDestroy()override;
	virtual void Show()override;
	virtual void Hide()override;
	virtual bool IsShowing()override;

	UFUNCTION(BlueprintCallable, Category = "ButtonWithTextWidget|Construct")
	virtual void Init();
	UFUNCTION(BlueprintCallable, Category = "ButtonWithTextWidget")
	virtual void Reset();
	UFUNCTION(BlueprintCallable, Category = "ButtonWithTextWidget")
	virtual void ForceToChangeState(bool _isChecked, bool _executeEvent = false);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		bool bLimitedCharNum = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		bool bIsColorStyle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		FButtonStyle BtnCheckedStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		FButtonStyle BtnUnCheckedStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		FButtonWithTextData Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		bool BtnState = false;

public:
	UPROPERTY(EditAnywhere, Category = "CustomData")
		int8 LimitedNameCharNum = 8;
	UPROPERTY(EditAnywhere, Category = "CustomData")
		FString LimitedNameReplacedString = TEXT("...");
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "CustomData")
		FSlateColor CheckedTextColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
		FSlateColor UnCheckedTextColor;
	void SetCheckedTextColor(FVector4 _color);
	void SetUncheckedTextColor(FVector4 _color);
	void SetBtnCheckedStyle();
	void SetBtnUnCheckedStyle();

	

	

protected:

	UFUNCTION()
		virtual void OnClick_Bt();
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (BindWidget))
		class UButton* btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (BindWidget))
		class UTextBlock* text;
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnClickButtonTextWithStrDelegate OnClickButtonTextWithStrDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnClickButtonTextWithInt32Delegate OnClickButtonTextWithInt32Delegate;

private:
	void ChangeTextColor(bool _isChecked);
	void ChangeBtnStyle(bool _isChecked);

	bool HasInit = false;
	

};