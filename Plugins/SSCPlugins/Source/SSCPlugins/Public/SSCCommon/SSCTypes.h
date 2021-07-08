// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameEngine.h"

#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include <Widgets/Layout/Anchors.h>
#include "SSCTypes.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCTypes : public UObject
{
	GENERATED_BODY()
	
};

#pragma region DebugHelper

class SSCPLUGINS_API SSCRecord
{
private:
	static TSharedPtr<SSCRecord> RecordInst;
public:
	inline SSCRecord() {};
	~SSCRecord() {};

	static TSharedPtr<SSCRecord> Get();

public:
	void InitParam(float _showTime, FColor _showColor);
	void SetShowPattern(int32 _showPattern);
	inline void OutPut()
	{
		switch (showPattern)
		{
			case 0:
			{
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, showTime, showColor, showInfo);
				}				
			}
			break;
			case 1:
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *showInfo);
			}
			break;
			case 2:
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *showInfo);
			}
			break;
			case 3:
			{
				UE_LOG(LogTemp, Error, TEXT("%s"), *showInfo);
			}
			break;
		}
		showInfo.Empty();
	}

	inline SSCRecord& operator<<(FString Info) { showInfo.Append(Info); return *this; }
	inline SSCRecord& operator<<(FName Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FText Info) { showInfo.Append(Info.ToString());return *this; }
	inline SSCRecord& operator<<(const char* Info) { showInfo += Info; return *this; }
	inline SSCRecord& operator<<(const char Info) { showInfo.AppendChar(Info); return *this; }
	inline SSCRecord& operator<<(int32 Info) { showInfo.Append(FString::FromInt(Info)); return *this; }
	inline SSCRecord& operator<<(float Info) { showInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline SSCRecord& operator<<(double Info) { showInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline SSCRecord& operator<<(bool Info) { showInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline SSCRecord& operator<<(FVector2D Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FVector Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FRotator Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FQuat Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FTransform Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FMatrix Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FColor Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FLinearColor Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FMargin Info) { showInfo.Append((FString::SanitizeFloat(Info.Left) + FString(" , ") + FString::SanitizeFloat(Info.Top) + FString(" , ") + FString::SanitizeFloat(Info.Right) + FString(" , ") + FString::SanitizeFloat(Info.Bottom))); return *this; }

	inline SSCRecord& operator<<(SSCRecord& _RecordInst) {_RecordInst.OutPut(); return *this;}


private:
	FString showInfo;
	float showTime = 0.f;
	FColor showColor = FColor::Yellow;
	uint8 showPattern = 0;  // 0 Debug 1 Log 2 Warning 3 Error
};

#pragma endregion

#pragma region LifeTimePart

UENUM()
enum class EBaseObjectLife : uint8
{
	None = 0,
	Init,
	Loading,
	Register,
	Enable,
	Disable,
	UnRegister,
	UnLoading,
};


UENUM()
enum class EBaseObjectState : uint8
{
	Active = 0,
	Stable,
	Destroy,
	
};

#pragma endregion

#pragma region ReflectPart

UENUM()
enum class EAgreementType : uint8
{
	SelfObject,
	OtherObject,
	ClassOtherObject,
	SelfClass,
	OtherClass,
	ALL,
};

UENUM()
enum class ERelfectCallResult : uint8
{
	LackModule = 0,
	LackObject,
	LackFunction,
	Succeed,
};

struct FRelfectFuncParam
{
public:
	ERelfectCallResult CallReslut;
	void* FuncParamPtr;
};

struct FModuleFunctionAgrement
{
public:
	int32 ModuleIndex;
	FName FunctionName;
};

struct FObjectFunctionAgrement
{
public:
	int32 ModuleIndex;
	EAgreementType ObjectAgreementType;
	TArray<FName> TargetObjectNameArray;
	FName FunctionName;
};

#pragma endregion

#pragma region TemplateFunc

struct FAnyFunc
{
	struct FBaseFunc
	{
	public:
		virtual ~FBaseFunc() { }
	};

	template<typename RetType, typename... VarTypes>
	struct FValueFunc : public FBaseFunc
	{
	public:
		TFunction<RetType(VarTypes...)> TargetFunc;
		FValueFunc(const TFunction<RetType(VarTypes...)>_Func) : TargetFunc(_Func) {}
		RetType Execute(VarTypes... Params) {
			return TargetFunc(Params...);
		}
	};

public:
	FBaseFunc* FuncPtr;

	FAnyFunc() : FuncPtr(nullptr) {}

	template<typename RetType, typename... VarTypes>
	FAnyFunc(const TFunction<RetType(VarTypes...)> _Func) : FuncPtr(new FValueFunc<RetType,VarTypes...>(_Func)) {}

	~FAnyFunc() { delete FuncPtr; FuncPtr = nullptr; }

	template<typename RetType, typename... VarTypes>
	RetType Execute(VarTypes... Params)
	{
		FValueFunc<RetType, VarTypes...>* _ValueFunc = static_cast<FValueFunc<RetType, VarTypes...>*>(FuncPtr);
		
		
		return _ValueFunc->Execute(Params...);
		
	}

	template<typename RetType, typename... VarTypes>
	TFunction<RetType(VarTypes...)>& GetFunc()
	{
		FValueFunc<RetType, VarTypes...>* ValueFunc = static_cast<FValueFunc<RetType, VarTypes...>*>(FuncPtr);
		return ValueFunc->TargetFunc;
	};

};

#pragma  endregion

#pragma region FuncNode

struct FFuncNode
{
public:
	int32 CallCount;
	TMap<int32, FAnyFunc*> FuncGroup;
	
	template<typename RetType, typename... VarTypes>
	int32 RegisterFunc(TFunction<RetType(VarTypes...)> InFunc);
	
	void UnRegisterFunc(int32 FuncId)
	{
		FAnyFunc* FuncPtr = *FuncGroup.Find(FuncId);
		if (FuncPtr)
		{
			FuncGroup.Remove(FuncId);
			delete FuncPtr;
			FuncPtr = nullptr;	
		}	
	}

	void ClearNode()
	{
		for (TMap<int32, FAnyFunc*>::TIterator it(FuncGroup); it; ++it)
		{
			delete it.Value();
		}
	}

	bool IsBound()
	{
		return FuncGroup.Num() > 0;
	}

	template<typename RetType, typename... VarTypes>
	RetType Execute(VarTypes... Params);
	
	template<typename RetType, typename... VarTypes>
	bool ExecuteIfBound(VarTypes... Params);

	FFuncNode(): CallCount(0) {}
};

template<typename RetType, typename...VarTypes>
int32 FFuncNode::RegisterFunc(TFunction<RetType(VarTypes...)> InFunc)
{
	TArray<int32> KeyArray;
	FuncGroup.GenerateKeyArray(KeyArray);
	int32 newId = 0;
	
	for (int i = KeyArray.Num(); i >= 0; --i)
	{
		if (!KeyArray.Contains(i))
		{
			newId = i;
			break;
		}
	}
	FuncGroup.Add(newId, new FAnyFunc(InFunc));
	return newId;

}

template<typename RetType, typename...VarTypes>
RetType FFuncNode::Execute(VarTypes... Params)
{
	TMap<int32, FAnyFunc*>::TIterator it(FuncGroup);
	++it;
	for (; it; ++it)
	{
		it.Value()->Execute<RetType, VarTypes...>(Params...);
	}

	TMap<int32, FAnyFunc*>::TIterator Begin_it(FuncGroup);

	return Begin_it.Value()->Execute<RetType, VarTypes...>(Params...);
}

template<typename RetType, typename... VarTypes>
bool FFuncNode::ExecuteIfBound(VarTypes... Params)
{
	if (!IsBound()) return false;
	for (TMap<int32, FAnyFunc*>::TIterator it(FuncGroup); it; ++it)
	{
		it.Value()->Execute<RetType, VarTypes...>(Params...);
	}
	return true;
}

#pragma endregion


#pragma region FuncCallHandle

struct FFuncQuene;

template<typename RetType, typename... VarTypes>
struct FFuncCallHandle
{
	FFuncQuene* FuncQuene;
	FName CallName;
	TSharedPtr<bool> IsActived;

	RetType Execute(VarTypes... Params);
	bool IsBound();
	
	bool ExecuteIfBound(VarTypes... Params);

	void UnRegister();
	
	FFuncCallHandle() {}
	FFuncCallHandle(FFuncQuene* Quene, FName _CallName) 
	{
		FuncQuene = Quene;
		CallName = _CallName;
		IsActived = MakeShareable<bool>(new bool(true));
	}

	FFuncCallHandle<RetType, VarTypes...>& operator=(const FFuncCallHandle<RetType, VarTypes...>& Other)
	{
		if (this == &Other) return *this;
		FuncQuene = Other.FuncQuene;
		CallName = Other.CallName;
		IsActived = Other.IsActived;
		return *this;
	}
};

template<typename RetType, typename...VarTypes>
void FFuncCallHandle<RetType, VarTypes...>::UnRegister()
{
	
	if (*IsActived.Get())
		FuncQuene->UnRegisterCallHandle(CallName);

	*IsActived.Get() = false;
}

template<typename RetType, typename...VarTypes>
bool FFuncCallHandle<RetType, VarTypes...>::ExecuteIfBound(VarTypes... Params)
{
	if (!IsBound || (!IsActived.Get()))  return false;
	FuncQuene->Exectue<RetType, VarTypes...>(CallName, Params...);
	return true;
}

template<typename RetType, typename...VarTypes>
bool FFuncCallHandle<RetType, VarTypes...>::IsBound()
{
	if (!*IsActived.Get()) return false;
	return FuncQuene->IsBound(CallName);
}

template<typename RetType, typename...VarTypes>
RetType FFuncCallHandle<RetType, VarTypes...>::Execute(VarTypes... Params)
{
	//if ( !IsBound() ||  !*IsActived.Get()) return NULL;
	return FuncQuene->Exectue<RetType, VarTypes...>(CallName, Params...);
}




#pragma endregion


#pragma region FuncQuene

struct FFuncHandle;

struct FFuncQuene
{
	TMap<FName, FFuncNode> FuncQuene;
	
	template<typename RetType, typename... VarTypes>
	FFuncCallHandle<RetType, VarTypes... > RegisterCallHandle(FName CallName);

	template<typename RetType, typename... VarTypes>
	FFuncHandle RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc);;
	
	void UnRegisterCallHandle(FName CallName)
	{
		if (!FuncQuene.Contains(CallName)) return;

		FFuncNode* Node = FuncQuene.Find(CallName);
		if (!Node) return;
		int32 CallCount = Node->CallCount--;
		if (CallCount <= 0)
		{
			FuncQuene.Find(CallName)->ClearNode();
			FuncQuene.Remove(CallName);
		}
	}

	void UnRegisterFuncHandle(FName CallName,int32 FuncId)
	{
		if (!FuncQuene.Contains(CallName)) return;
		FuncQuene.Find(CallName)->UnRegisterFunc(FuncId);
	}

	template<typename RetType,typename... VarTypes>
	RetType Exectue(FName CallName, VarTypes... Params);
	
	bool IsBound(FName CallName)
	{
		return  FuncQuene.Find(CallName)->IsBound();
	}

};

template<typename RetType, typename... VarTypes>
FFuncCallHandle<RetType, VarTypes... >
FFuncQuene::RegisterCallHandle(FName CallName)
{
	if (FuncQuene.Contains(CallName))
	{
		FuncQuene.Find(CallName)->CallCount++;
	}
	else
	{
		FuncQuene.Add(CallName, FFuncNode());
		FuncQuene.Find(CallName)->CallCount++;
	}

	return FFuncCallHandle<RetType, VarTypes...>(this, CallName);
}

template<typename RetType, typename... VarTypes>
FFuncHandle FFuncQuene::RegisterFuncHandle(FName CallName, TFunction<RetType(VarTypes...)> InFunc)
{
	int32 FuncId;
	if (!FuncQuene.Contains(CallName))
	{
		FuncQuene.Add(CallName, FFuncNode());
	}
	FuncId = FuncQuene.Find(CallName)->RegisterFunc(InFunc);

	return FFuncHandle(this, CallName, FuncId);
}

template<typename RetType, typename...VarTypes>
RetType FFuncQuene::Exectue(FName CallName, VarTypes... Params)
{
	return FuncQuene.Find(CallName)->Execute<RetType, VarTypes...>(Params...);
}

#pragma endregion


#pragma region FuncHandle

struct FFuncHandle
{
	FFuncQuene* FuncQuene;
	FName CallName;
	int32 FuncId;
	TSharedPtr<bool> IsActived;

	void UnRegister() 
	{
		if (*IsActived.Get())
			FuncQuene->UnRegisterFuncHandle(CallName, FuncId);

		*IsActived.Get() = false;
	}
	FFuncHandle() {}
	FFuncHandle(FFuncQuene* Quene, FName _CallName,int32 _FuncId) 
	{
		FuncQuene = Quene;
		CallName = _CallName;
		FuncId = _FuncId;

		IsActived = MakeShareable<bool>(new bool(true));
	}
	FFuncHandle& operator=(const FFuncHandle& Other)
	{
		if (this == &Other)
		{
			return *this;
		}

		FuncQuene = Other.FuncQuene;
		CallName = Other.CallName;
		FuncId = Other.FuncId;
		IsActived = Other.IsActived;
		return *this;
	}
	
};

#pragma endregion

#pragma region Coroutine

DECLARE_DELEGATE_RetVal(bool,FCoroutineDelegate)


struct FCoroNode
{
	bool IsActive;
	float RemaingTime;
	FCoroutineDelegate FCoroutineDel;
	
	FCoroNode() : IsActive(false) {}
	
	//UpdateOperate () 返回false IsActive flase 携程结束

	
	/*延迟帧函数*/
	bool UpdateOperate(int32 DelayTick)
	{
		if (!IsActive)
		{
			RemaingTime = DelayTick;
			IsActive = true;
			return true;
		}
		else
		{
			RemaingTime -= 1;
			if (RemaingTime <= 0)
			{
				IsActive = false;
				return false;
			}
			else
			{
				return true;
			}
				
		}
	}
	/**********************************************/
	
	/*延迟秒函数*/
	bool UpdateOperate(float DeltaTime, float SpaceTime)
	{
		if (!IsActive)
		{
			RemaingTime = SpaceTime;
			IsActive = true;
			return true;
		}
		else
		{
			RemaingTime -= DeltaTime;
			if (RemaingTime > 0)
			{
				return true;
			}
			else
			{
				IsActive = false;
				return false;
			}
		}
	}
	/**********************************************/

	/*延迟bool 条件false 携程结束*/
	bool UpdateOperate(bool* Condition)
	{
		if (!IsActive)
		{
			IsActive = true;
			return true;
		}
		else
		{
			if (*Condition)
			{
				return true;
			}
			else
			{
				IsActive = false;
				return false;
			}
		}
	}
	/**********************************************/


	/*延迟 绑定函数是否执行*/
	template<typename UserClass>
	bool UpdateOperate(UserClass* Object, typename FCoroutineDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr InMethod)	
	{
		if (!IsActive)
		{
			if (!FCoroutineDel.IsBound())
			{
				FCoroutineDel.BindUObject(Object, InMethod);
			}
			IsActive = true;
			return true;
		}
		else
		{
			if (FCoroutineDel.Execute())
			{
				return true;
			}
			else
			{
				IsActive = false;
				return false;
			}
		}
	}
	/**********************************************/


	/*延迟 Lambda*/
	bool UpdateOperate(TFunction<bool()> InFunction)
	{
		if (!IsActive)
		{
			IsActive = true;
			return true;
		}
		else
		{
			if (InFunction())
			{
				return true;
			}
			else
			{
				IsActive = false;
				return false;
			}
		}
	}

	/**********************************************/

	/*停止携程*/
	bool UpdateOperate()
	{
		IsActive = false;
		return false;
	}

	/**********************************************/
};

struct FCoroStack
{
	bool isDestroy;
	TArray<FCoroNode*> CoroStack;

	FCoroStack(int32 CoroCount)
	{
		isDestroy = false;
		for (int i = 0; i <= CoroCount; ++i)
		{
			CoroStack.Push(new FCoroNode());
		}
	}
	
	virtual ~FCoroStack()
	{
		for (int i = 0; i < CoroStack.Num(); ++i)
		{
			delete CoroStack[i];
		}
	}
	
	virtual void Work(float DeltaTime) {}

	bool IsFinish()
	{
		bool Flag = true;
		for (int i = 0; i < CoroStack.Num(); ++i)
		{
			if (CoroStack[i]->IsActive)
			{
				Flag = false;
				break;
			}
		}	
		return Flag;
	}
};

#pragma endregion

#pragma region Invoke

DECLARE_DELEGATE(FInvokeDelegate)

struct  FInvokeTask
{
public:
	bool isDestroy;
	float DelayTime;
	float TimeCount;
	bool IsRepeated;
	float RepeatedTime;
	bool IsRepeatedState;
	FInvokeDelegate  FInvokeDel;
	
	FInvokeTask(float _DelayTime, bool _IsRepeated, float _RepeatedTime)
	{
		DelayTime = _DelayTime;
		IsRepeated = _IsRepeated;
		RepeatedTime = _RepeatedTime;
		IsRepeatedState = false;
		TimeCount = 0.f;
		isDestroy = false;
	}

	bool UpdateOperate(float DeltaSeconds)
	{
		TimeCount+= DeltaSeconds;
		if (!IsRepeatedState)
		{
			if (TimeCount >= DelayTime)
			{
				
				FInvokeDel.ExecuteIfBound();
				TimeCount = 0.f;
				if (IsRepeated)
				{
					IsRepeatedState = true;
				}
				else
				{
					return true;
				}
			}
		}
		else
		{			
			if (TimeCount >= RepeatedTime)
			{
				FInvokeDel.ExecuteIfBound();
				TimeCount = 0.f;
			}
		}
		return false;
	}

};

#pragma endregion

#pragma region Wealth

/*********************自动加载对象*****************************/
USTRUCT()
struct SSCPLUGINS_API FWealthItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FName ObjectName;
	UPROPERTY(EditAnywhere)
		FName ClassName;
};

USTRUCT()
struct SSCPLUGINS_API FWealthItemObject : public FWealthItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UObject> ObjectClass;
};

USTRUCT()
struct SSCPLUGINS_API FWealthItemActor : public FWealthItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere)
		FTransform SpawnTransform;
};

USTRUCT()
struct SSCPLUGINS_API FWealthItemWidget : public FWealthItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;
};

/*********************************************************/

/******************批量加载对象*****************************/

USTRUCT()
struct SSCPLUGINS_API FWealthObjectEntry
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FName ObjName;
	UPROPERTY(EditAnywhere)
		FName KindName;
	UPROPERTY(EditAnywhere)
		FStringAssetReference ObjectPath;
	UPROPERTY()
		UObject* ObjInst = nullptr;
};

UENUM()
enum class EWealthClassType :uint8
{
	Object = 0,
	Actor,
	Widget
};

USTRUCT()
struct SSCPLUGINS_API FWealthClassEntry
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		EWealthClassType ClassType;
	UPROPERTY(EditAnywhere)
		FName ObjName;
	UPROPERTY(EditAnywhere)
		FName KindName;
	UPROPERTY(EditAnywhere)
		TSoftClassPtr<UObject> ClassPtr;
	UPROPERTY()
		UClass* ObjInst;
};


USTRUCT()
struct SSCPLUGINS_API FWealthURL
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FName ObjName;
	UPROPERTY(EditAnywhere)
		FName KindName;
	UPROPERTY(EditAnywhere)
		FStringAssetReference ObjectPath;
	UPROPERTY(EditAnywhere)
		TSoftClassPtr<UObject> ClassPtr;
};
/*********************************************************/

UCLASS()
class SSCPLUGINS_API UWealthDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ModuleName;  //为空默认为所在模组

	UPROPERTY(EditAnywhere)
		TArray<FWealthItemObject> AutoObjects;
	
	UPROPERTY(EditAnywhere)
		TArray<FWealthItemActor> AutoActors;

	UPROPERTY(EditAnywhere)
		TArray<FWealthItemWidget> AutoWidgets;

	/*******************************/

	UPROPERTY(EditAnywhere)
		TArray<FWealthObjectEntry> WealthObjects;
	UPROPERTY(EditAnywhere)
		TArray<FWealthClassEntry> WealthClasses;
	UPROPERTY(EditAnywhere)
		TArray<FWealthURL> WealthURLs;
};



#pragma endregion

#pragma region UIFrame

UENUM()
enum class ELayOutType : uint8
{
	Canvas = 0,
	OverLay,
};

UENUM()
enum class ELayOutLevel : uint8
{
	Level_0 = 0,
	Level_1,
	Level_2,
	Level_3,
	Level_4,
	Level_ALL ,
};

UENUM()
enum class EPanelShowType : uint8
{
	 DoNothing = 0 ,
	 HideOther,
	 PopUps
};

UENUM()
enum class EPanelTransparentType : uint8 {
	FullTransparent,        //全透明不可点击
	Transparent,			//半透明不可点击
	LowTransparent,			//低透明不可点击
	FullTransparentClick,   //全透明可点击
};

USTRUCT()
struct FUINature 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ELayOutType LayOutType;
	UPROPERTY(EditAnywhere)
		ELayOutLevel LayOutLevel;
	UPROPERTY(EditAnywhere)
		EPanelShowType PanelShowType;
	UPROPERTY(EditAnywhere)
		EPanelTransparentType TransparentType;
	UPROPERTY(EditAnywhere) // canvas
		FAnchors Anchors;
	UPROPERTY(EditAnywhere) //pos size , padding
		FMargin Margin;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EVerticalAlignment> VerticalAlignment;
};

#pragma endregion