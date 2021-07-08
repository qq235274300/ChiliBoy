// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCObject/SSCUserWidget.h"
#include "SSCPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCPanelWidget : public USSCUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void PanelEnter();
	virtual void PanelHidden();
	virtual void PanelDisplay();
	virtual void PanelFreeze();
	virtual void PanelUnFreeze();
	virtual void PanelExit();

protected:
	UFUNCTION()
		void SetPanelHidden();
	UFUNCTION()
		void SetPanelExit();
/*******************调用UI管理器方法***********************************/
	void ShowSelfPanel();
	void HideSelfPanel();
	void ExitSelfPanel();
	//加载其他UI
	void AdvanceLoadSelfPanel(FName PanelName);
	void ShowUIPanel(FName PanelName);
	void HideUIPanel(FName PanelName);
	void ExitUIPanel(FName PanelName);
	/**********************************************************/
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "SSCPanel")
		float PlayPanelEnterAnim();
	UFUNCTION(BlueprintImplementableEvent, Category = "SSCPanel")
		float PlayPanelExitAnim();
	

public:
	UPROPERTY(EditAnywhere, Category = "CustomData")
		FUINature UINature;
protected:
	//UI移动动画延迟任务名
	static FName InvokeDelayName ;
	//主画布模组ID 约定HUD下为1
	static int32 UIFarmeModuleIndex;
	//主画布对象名 SSCUIRoot
	static FName SSCUIRootName;
	//移除画布回调名 
	static FName PanelExitCallBackName;


	static FName ShowUIPanelName;
	static FName HideUIPanelName;
	static FName ExitUIPanelName;
	static FName AdvanceLoadPanelName;

protected:
	REFOBJFUNC_TWO(PanelExitCallBack, ELayOutType, LayoutType, UPanelWidget*, Layout);
	REFOBJFUNC_ONE(OperatorUIPanel, FName,PanelName);
};
