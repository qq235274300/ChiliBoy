#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "VisualWidgetPoolTemplate.generated.h"

UINTERFACE()
class UVisualWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class IVisualWidgetInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual bool IsShowing() = 0;
};

template<typename WidgetObject>
class UVisualWidgetPool
{
public:
	UVisualWidgetPool();
	~UVisualWidgetPool();

public:
	bool HasInit() { return objects.Num() > 0; }
	void Init(TArray<WidgetObject*> _maxObject) 
	{
		objects.Empty();
		objects = _maxObject;
		currentShowNum = _maxObject.Num();
	}

	void Add(TArray<WidgetObject*> _extraObject)
	{
		for (const auto& i : _extraObject)
		{
			if (IVisualWidgetInterface* tmpWidget = Cast<IVisualWidgetInterface>(i))
			{
				tmpWidget->Hide();
			}
			else
			{
				return;
			}

			objects.Add(i);
		}
		
	}

	TArray<WidgetObject*> GetWidgetObjects(int _num)
	{
		TArray<WidgetObject*> res;
		currentShowNum = _num > 0 ? (_num <= objects.Num() ? _num : objects.Num()) : 0;
		for (int i = 0; i < objects.Num(); ++i)
		{
			IVisualWidgetInterface* tmpWidget = Cast<IVisualWidgetInterface>(objects[i]);
			if (tmpWidget)
			{
				if (i < currentShowNum)
				{
					tmpWidget->Show();
					res.Add(objects[i]);
				}
				else
				{
					tmpWidget->Hide();
				}
			}
		}

		return res;
	}

	bool CanGetExtraHidingObject(int _getNum)
	{
		return (currentShowNum + _getNum) <= objects.Num();
	}


	TArray<WidgetObject*> GetExtraObject(int _extraNum)
	{
		TArray<WidgetObject*> res;
		if (CanGetExtraHidingObject(_extraNum))
		{
			for (int i = currentShowNum; i < (currentShowNum + _extraNum); ++i)
			{
				IVisualWidgetInterface* wgtIntf = Cast<IVisualWidgetInterface>(objects[i]);
				if (wgtIntf)
				{
					wgtIntf->Show();
					res.Add(objects[i]);
				}
				else
				{
					break;
				}
			}

			currentShowNum += _extraNum;
		}

		return res;
	}


	int GetCurrentShowNum()
	{
		return currentShowNum;
	}

	TArray<WidgetObject*> GetCurrentShowWidgetObjects()
	{
		TArray<WidgetObject*> res;
		for (WidgetObject* obj : objects)
		{
			IVisualWidgetInterface* wgtIntf = Cast<IVisualWidgetInterface>(obj);
			if (wgtIntf)
			{
				if (wgtIntf->IsShowing())
				{
					res.Add(obj);
				}
			}
		}

		return res;
	}

	WidgetObject* GetNextOrFrontObj(WidgetObject* _obj, int8 _next = 1)
	{
		TArray<WidgetObject*> objs = GetCurrentShowWidgetObjects();
		if (currentShowNum > 1)
		{
			for (int i = 0; i < currentShowNum; i++)
			{
				if (objs[i] == _obj)
				{
					if (_next == 1)
					{
						return objs[(++i >= currentShowNum) ? 0 : i];
					}
					else if (_next == -1)
					{
						return objs[(--i < 0) ? currentShowNum - 1 : i];
					}
					else
					{
						return nullptr;
					}
				}
			} 
		}

		return nullptr;
	}

	bool HideObject(WidgetObject* _obj)
	{
		IVisualWidgetInterface* wgtIntf = Cast<IVisualWidgetInterface>(_obj);
		if (wgtIntf)
		{
			wgtIntf->Hide();
			if (currentShowNum > 0)
			{
				currentShowNum--;
			}
			return true;
		}

		return false;
	}

	void Reset()
	{
		currentShowNum = 0;
		for (WidgetObject* obj : objects)
		{
			if (obj)
			{
				IVisualWidgetInterface* tmpWidget = Cast<IVisualWidgetInterface>(obj);
				if (tmpWidget)
				{
					tmpWidget->Hide();
				}
			}
		}
	}

	void Clear()
	{
		Reset();

		objects.Empty();
	}

	void BeginDestroy()
	{
		objects.Empty();
	}

private:

	TArray<WidgetObject*> objects;
	int32 currentShowNum = 0;
};

