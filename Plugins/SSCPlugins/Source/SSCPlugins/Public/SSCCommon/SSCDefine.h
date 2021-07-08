// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SSCTypes.h"
#include "SSCDefine.generated.h"

/**
 * 
 */
UCLASS()
class SSCPLUGINS_API USSCDefine : public UObject
{
	GENERATED_BODY()
	
};

#pragma  region ObjectCallModule
/***********Object Process Module Reflect Fucntion***********************************/
/***********************************************************************************/

#define REFMODFUNC(FuncName);\
	struct FuncName##Param : FRelfectFuncParam\
	{\
		FuncName##Param() { FuncParamPtr  = NULL; }\
	};\
	FuncName##Param*  FuncName##RT(int32 _ModuleIndex, FName _FuncName)\
	  {\
		  FModuleFunctionAgrement Agreement;\
		  Agreement.ModuleIndex = _ModuleIndex;\
		  Agreement.FunctionName = _FuncName;\
	      FuncName##Param* Parm = new FuncName##Param(); \
          ProcessModuleReflectFuncEvnt(Agreement, Parm); \
          return Parm; \
	}\
		void  FuncName(int32 _ModuleIndex, FName _FuncName)\
		{\
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = _FuncName; \
        FuncName##Param* Parm = new FuncName##Param(); \
        ProcessModuleReflectFuncEvnt(Agreement, Parm); \
        delete Parm; \
	}
/**********************************One**********************************************/
#define REFMODFUNC_ONE(FuncName, ParamType1, ParamName1); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		FuncName##Param() { FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/**********************************Two**********************************************/
#define REFMODFUNC_TWO(FuncName, ParamType1, ParamName1, ParamType2, ParamName2); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		FuncName##Param() { FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/**********************************Three**********************************************/
#define REFMODFUNC_THREE(FuncName,ParamType1,ParmName1,ParamType2,ParamName2,ParamType3,ParamName3);\
	struct FuncName##Param : FRelfectFuncParam\
	{\
		struct\
		{\
			ParamType1 ParmName1;\
			ParamType2 ParamName2;\
			ParamType3 ParamName3;\
		}Paramter;\
		ParamType1 ParmName1() { return Paramter.ParmName1; }\
		ParamType2 ParamName2() { return Paramter.ParamName2; }\
		ParamType3 ParamName3() { return Paramter.ParamName3; }\
		FuncName##Param() { FuncParamPtr  = &Paramter; }\
	};\
	FuncName##Param*  FuncName##RT(int32 _ModuleIndex, FName _FuncName, ParamType1 ParmName1, ParamType2 ParamName2, ParamType3 ParamName3)\
	  {\
		  FModuleFunctionAgrement Agreement;\
		  Agreement.ModuleIndex = _ModuleIndex;\
		  Agreement.FunctionName = _FuncName;\
	      FuncName##Param* Parm = new FuncName##Param(); \
		  Parm->Paramter.ParmName1 = ParmName1;\
		  Parm->Paramter.ParamName2 = ParamName2;\
		  Parm->Paramter.ParamName3 = ParamName3;\
          ProcessModuleReflectFuncEvnt(Agreement, Parm); \
          return Parm; \
	}\
		void  FuncName(int32 _ModuleIndex, FName _FuncName, ParamType1 ParmName1, ParamType2 ParamName2, ParamType3 ParamName3)\
		{\
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = _FuncName; \
        FuncName##Param* Parm = new FuncName##Param(); \
		Parm->Paramter.ParmName1 = ParmName1;\
		Parm->Paramter.ParamName2 = ParamName2;\
		Parm->Paramter.ParamName3 = ParamName3;\
        ProcessModuleReflectFuncEvnt(Agreement, Parm); \
        delete Parm; \
	}
/**********************************Four**********************************************/
#define REFMODFUNC_FOUR(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4); \
	struct FuncName##Param : FRelfectFuncParam\
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		FuncName##Param() { FuncParamPtr    = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FModuleFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FModuleFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/**********************************Five**********************************************/
#define REFMODFUNC_FIVE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		FuncName##Param() { FuncParamPtr    = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FModuleFunctionAgrement  Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/**********************************Six*********************************************/
#define REFMODFUNC_SIX(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		FuncName##Param() { FuncParamPtr   = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FModuleFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FModuleFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/*********************************Seven*********************************************/
#define REFMODFUNC_SEVEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7); \
	struct FuncName##Param : FRelfectFuncParam    \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		FuncName##Param() { FRelfectFuncParam = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/*********************************Eight*********************************************/
#define REFMODFUNC_EIGHT(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8); \
	struct FuncName##Param : FRelfectFuncParam    \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		FuncName##Param() { FRelfectFuncParam = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/*********************************Nine*********************************************/
#define REFMODFUNC_NINE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9); \
	struct FuncName##Param : FRelfectFuncParam    \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		FuncName##Param() { FuncParamPtr    = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FModuleFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}
/*********************************Ten*********************************************/
#define REFMODFUNC_TEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9, ParamType10, ParamName10); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
			ParamType10 ParamName10; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		ParamType10 ParamName10() { return Parameter.ParamName10; } \
		FuncName##Param() {  FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FModuleFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessModuleReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

#pragma  endregion


#pragma region ObjectCallObject

/***********Object Process Object Reflect Fucntion**********************************/
/***********************************************************************************/

/******************************Zero*************************************************/
#define REFOBJFUNC(FuncName);\
struct FuncName##Param : FRelfectFuncParam \
	{ \
		FuncName##Param() { FuncParamPtr  = NULL; }\
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName)\
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	}\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/*******************************One*************************************************/
#define REFOBJFUNC_ONE(FuncName, ParamType1, ParamName1); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		FuncName##Param() { FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/*******************************Two*************************************************/
#define REFOBJFUNC_TWO(FuncName, ParamType1, ParamName1, ParamType2, ParamName2); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		FuncName##Param() { FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/*******************************Three*************************************************/
#define REFOBJFUNC_THREE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		FuncName##Param() { FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/*******************************Four*************************************************/
#define REFOBJFUNC_FOUR(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4); \
	struct FuncName##Param : FRelfectFuncParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		FuncName##Param() { FuncParamPtr  = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		FObjectFunctionAgrement   Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EAgreementType::SelfObject;\
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param();\
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ProcessObjectReflectFuncEvnt(Agreement, Param);\
		delete Param;\
	}

/******************************Five*************************************************/
#define REFOBJFUNC_FIVE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5); \
	struct FuncName##Param : FRelfectFuncParam  \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		FuncName##Param() { FuncParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}


/******************************Six*************************************************/
#define REFOBJFUNC_SIX(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6); \
	struct FuncName##Param : FRelfectFuncParam  \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		FuncName##Param() { FuncParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/******************************Seven*************************************************/
#define REFOBJFUNC_SEVEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7); \
	struct FuncName##Param : FRelfectFuncParam  \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		FuncName##Param() { FuncParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/******************************Eight*************************************************/
#define REFOBJFUNC_EIGHT(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8); \
	struct FuncName##Param : FRelfectFuncParam  \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		FuncName##Param() { FuncParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}

/******************************Nine*************************************************/
#define REFOBJFUNC_NINE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9); \
	struct FuncName##Param : FRelfectFuncParam  \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		FuncName##Param() { FuncParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}


/******************************Ten*************************************************/
#define REFOBJFUNC_TEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9, ParamType10, ParamName10); \
	struct FuncName##Param : FRelfectFuncParam  \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
			ParamType10 ParamName10; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		ParamType10 ParamName10() { return Parameter.ParamName10; } \
		FuncName##Param() { FuncParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, TArray<FName> TargetObjectNameArray, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray = TargetObjectNameArray; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, EObjectAgreementType ObjectAgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = ObjectAgreementType; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 _ModuleIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		FObjectFunctionAgrement Agreement; \
		Agreement.ModuleIndex = _ModuleIndex; \
		Agreement.ObjectAgreementType = EObjectAgreementType::SelfObject; \
		Agreement.TargetObjectNameArray.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ProcessObjectReflectFuncEvnt(Agreement, Param); \
		delete Param; \
	}


#pragma endregion



#pragma region CoroutineDefine

//参数区域宏定义
#define SSCCORO_PARAM(UserClass); \
struct SSCCoroTask : public FCoroStack \
{ \
	UserClass* D; \
	SSCCoroTask(UserClass* Data, int32 CoroCount) : FCoroStack(CoroCount) { D = Data; }


//Work方法开头
#define SSCCORO_WORK_START \
virtual void Work(float DeltaTime) override \
{ \
	goto SSCCORO_LABEL_PICKER; \
SSCCORO_LABEL_START:



//Work方法中间
#define SSCCORO_WORK_MIDDLE \
	goto SSCCORO_LABEL_END; \
SSCCORO_LABEL_PICKER:


//Work方法结尾
#define  SSCCORO_WORK_END \
		goto SSCCORO_LABEL_START; \
	SSCCORO_LABEL_END: \
		; \
	} \
}; \
return new SSCCoroTask(this, SSCYIELD_COUNT);


#define SSCCORO_BEGIN() "SSCCoroBegin.h"

#define SSCCORO_END() "SSCCoroEnd.h"

#define SSCYIELD_READY() "SSCCoroYieldReady.h"


#define SSCYIELD_RETURN_TICK(Tick); \
if (CoroStack[SSCYIELD_COUNT]->UpdateOperate(Tick)) \
	goto SSCCORO_LABEL_END;


#define SSCYIELD_RETURN_SECOND(Time); \
if (CoroStack[SSCYIELD_COUNT]->UpdateOperate(DeltaTime, Time)) \
	goto SSCCORO_LABEL_END;


#define  SSCYIELD_RETURN_BOOL(Param); \
if (CoroStack[SSCYIELD_COUNT]->UpdateOperate(Param)) \
	goto SSCCORO_LABEL_END;


#define SSCYIELD_RETURN_FUNC(UserClass, UserFunc); \
if (CoroStack[SSCYIELD_COUNT]->UpdateOperate(UserClass, UserFunc)) \
	goto SSCCORO_LABEL_END;


#define SSCYIELD_RETURN_LAMB(Expression); \
if (CoroStack[SSCYIELD_COUNT]->UpdateOperate([this](){ return Expression; })) \
	goto SSCCORO_LABEL_END;


#define SSCYIELD_RETURN_STOP(); \
if (CoroStack[SSCYIELD_COUNT]->UpdateOperate()) \
	goto SSCCORO_LABEL_END;



#pragma  endregion