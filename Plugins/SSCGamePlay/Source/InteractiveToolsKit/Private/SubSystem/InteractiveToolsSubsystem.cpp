// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/InteractiveToolsSubsystem.h"
#include <ToolContextInterfaces.h>
#include <Tools/ToolsContextActor.h>
#include "HelperKits/Public/DebugHelper.h"
#include <MeshScene/SceneHistroyManager.h>
#include "Tools/DynamicMeshComponentTarget.h"
#include <BaseGizmos/GizmoRenderingUtil.h>
#include <Slate/SGameLayerManager.h>
#include <Layout/Geometry.h>
#include <Slate/SceneViewport.h>
#include <Misc/Paths.h>
#include <GeneratedMesh.h>
#include <Tools/RuntimeDrawPolygonTool.h>



#pragma region ITFAPI
class FRuntimeToolsContextQueriesImpl : public IToolsContextQueriesAPI
{
public:
	FRuntimeToolsContextQueriesImpl(UInteractiveToolsContext* InToolContext, UWorld* InWorld)
	{
		ToolContext = InToolContext;
		CurrentWorld = InWorld;
	}
	virtual void SetViewPawn(AGameplayPawn* InPawn)
	{
		ViewPawn = InPawn;
	}

	virtual void GetCurrentSelectionState(FToolBuilderState& StateOut)const override
	{
		StateOut.ToolManager = ToolContext->ToolManager;
		StateOut.GizmoManager = ToolContext->GizmoManager;
		StateOut.World = CurrentWorld;

		const TArray<UInteractiveMeshSceneObject*>& Selection = UInteractiveMeshSceneSubsystem::Get()->GetInteractiveMeshSceneObjects();
		for (UInteractiveMeshSceneObject* SO : Selection)
		{
			StateOut.SelectedActors.Add(SO->GetActor());
			StateOut.SelectedComponents.Add(SO->GetMeshComponent());
		}
	}

	virtual void GetCurrentViewState(FViewCameraState& StateOut) const override
	{
		if (!ViewPawn)
		{
			return;
		}
		bool bHasCamera = ViewPawn->HasActiveCameraComponent();
		FVector Location;
		FRotator Rotation;
		ViewPawn->GetActorEyesViewPoint(Location, Rotation);
		
		StateOut.Position = Location;
		StateOut.Orientation = Rotation.Quaternion();
		StateOut.HorizontalFOVDegrees = 90;
		StateOut.OrthoWorldCoordinateWidth = 1;
		StateOut.AspectRatio = 1.0;
		StateOut.bIsOrthographic = false;
		StateOut.bIsVR = false;
	}

	virtual EToolContextCoordinateSystem GetCurrentCoordinateSystem()const override
	{
		return UInteractiveToolsSubsystem::Get()->GetCurrentCoordinateSystem();
	}

	virtual bool ExecuteSceneSnapQuery(const FSceneSnapQueryRequest& Request, TArray<FSceneSnapQueryResult>& Results)const override
	{
		return false;
	}

	virtual UMaterialInterface* GetStandardMaterial(EStandardToolContextMaterials MaterialType) const override
	{
		return UMaterial::GetDefaultMaterial(MD_Surface);
	}

#if WITH_EDITOR
	
	virtual HHitProxy* GetHitProxy(int32 X, int32 Y)const override
	{
		return nullptr;
	}

#endif
		
protected:	
	UInteractiveToolsContext* ToolContext;	
	UWorld* CurrentWorld;
	AGameplayPawn* ViewPawn = nullptr;
};
class FRuntimeToolsContextTransactionImpl : public IToolsContextTransactionsAPI
{
public:
	bool bInTransaction = false;
	virtual void DisplayMessage(const FText& Message, EToolMessageLevel Level) override
	{
		DebugHelper::Count() << "ToolsContextTransaction--->" << Message << DebugHelper::Endl();
	}

	virtual void PostInvalidation()override
	{
		
	}
	
	virtual void BeginUndoTransaction(const FText& Description)override
	{
		UInteractiveToolsSubsystem::Get()->GetSceneHistory()->BeginTransaction(Description);
		bInTransaction = true;
	}

	virtual void EndUndoTransaction()override
	{
		UInteractiveToolsSubsystem::Get()->GetSceneHistory()->EndTransaction();
		bInTransaction = false;
	}

	virtual void AppendChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description)override
	{
		bool bCloseTransaction = false;
		if (!bInTransaction)
		{
			BeginUndoTransaction(Description);
			bCloseTransaction = true;
		}
		
		UInteractiveToolsSubsystem::Get()->GetSceneHistory()->AppendChange(TargetObject, MoveTemp(Change), Description);
		
		if (bCloseTransaction)
		{
			EndUndoTransaction();
		}
	}

	virtual bool RequestSelectionChange(const FSelectedOjectsChangeList& SelectionChange)override 
	{
		return false;
	}
};
class FRuntimeToolsContextAssetImpl : public IToolsContextAssetAPI
{
	virtual FString GetWorldRelativeAssetRootPath(const UWorld* World)override
	{
		return FString("");
	}

	virtual FString GetActiveAssetFolderPath()override
	{
		return FString("");
	}

	virtual FString InteractiveSelectAssetPath(const FString& DefaultAssetName, const FText& DialogTitleMessage)override
	{
		return FString("");
	}

	virtual UPackage* MakeNewAssetPackage(const FString& FolderPath, const FString& AssetBaseName, FString& UniqueAssetNameOut)override
	{
		return NewObject<UPackage>();
	}

	virtual void InteractiveSaveGeneratedAsset(UObject* Asset, UPackage* AssetPackage)override 
	{
		ensure(false);
	}

	virtual void AutoSaveGeneratedAsset(UObject* Asset, UPackage* AssetPackage)override
	{
		ensure(false);
	}

	virtual void NotifyGeneratedAssetModified(UObject* Asset, UPackage* AssetPackage)override
	{
		ensure(false);
	}

	virtual AActor* GenerateStaticMeshActor(
		UWorld* TargetWorld,
		FTransform Transform,
		FString ObjectBaseName,
		FGeneratedStaticMeshAssetConfig&& AssetConfig)override
	{
		UInteractiveMeshSceneObject* SO = UInteractiveMeshSceneSubsystem::Get()->CreateNewSceneObject();
		SO->Initialize(TargetWorld, AssetConfig.MeshDescription.Get());
		SO->SetTransform(Transform);
		return SO->GetActor();	
	}

	virtual bool SaveGeneratedTexture2D(
		UTexture2D* GeneratedTexture,
		FString ObjectBaseName,
		const UObject* RelativeToAsset)override
	{
		ensure(false); 
		return false;
	}
};
class FRuntimeToolsFrameworkRenderImpl : public IToolsContextRenderAPI
{
public:
	UToolsContextRenderComponent* RenderComponent;
	TSharedPtr<FPrimitiveDrawInterface> PDI;
	const FSceneView* SceneView;
	FViewCameraState ViewCameraState;

	FRuntimeToolsFrameworkRenderImpl(UToolsContextRenderComponent* RenderComponentIn, const FSceneView* ViewIn, FViewCameraState CameraState)
		: RenderComponent(RenderComponentIn), SceneView(ViewIn), ViewCameraState(CameraState)
	{
		PDI = RenderComponentIn->GetPDIForView(ViewIn);
	}

	virtual FPrimitiveDrawInterface* GetPrimitiveDrawInterface() override
	{
		return PDI.Get();
	}

	virtual const FSceneView* GetSceneView() override
	{
		return SceneView;
	}

	virtual FViewCameraState GetCameraState() override
	{
		return ViewCameraState;
	}

	virtual EViewInteractionState GetViewInteractionState() override
	{
		return EViewInteractionState::Focused;
	}
};
#pragma  endregion

UInteractiveToolsSubsystem* UInteractiveToolsSubsystem::InteractiveToolSubSystem = nullptr;

void UInteractiveToolsSubsystem::InitSubSysytem(UInteractiveToolsSubsystem* InInteractiveToolsSubsystem)
{
	check(InInteractiveToolsSubsystem);
	InteractiveToolSubSystem = InInteractiveToolsSubsystem;
}

UInteractiveToolsSubsystem* UInteractiveToolsSubsystem::Get()
{
	check(InteractiveToolSubSystem);
	return InteractiveToolSubSystem;
}

void UInteractiveToolsSubsystem::Deinitialize()
{
	InteractiveToolSubSystem = nullptr;
}

void UInteractiveToolsSubsystem::Init(UWorld* InWorld)
{
	CurrentWorld = InWorld;
	//Init ToolContext,Init ITF API
	ToolContext = NewObject<UInteractiveToolsContext>();
	//包含当前查询对象及View Info
	QueriesAPI = MakeShared<FRuntimeToolsContextQueriesImpl>(ToolContext, CurrentWorld);
	if (pViewPawn)
	{
		QueriesAPI->SetViewPawn(pViewPawn);
	}
	TransactionAPI = MakeShared<FRuntimeToolsContextTransactionImpl>();
	AssetAPI = MakeShared<FRuntimeToolsContextAssetImpl>();
	//输入管理器，tool管理器完成初始化
	ToolContext->Initialize(QueriesAPI.Get(), TransactionAPI.Get());
	//记录Tool 属性
	ToolContext->ToolManager->OnToolStarted.AddUObject(this, &UInteractiveToolsSubsystem::OnToolStartedEvnt);
	ToolContext->ToolManager->OnToolEnded.AddUObject(this, &UInteractiveToolsSubsystem::OnToolEndedEvnt);
	//创建Change管理器
	SceneHistroyManager = NewObject<USceneHistroyManager>(this);
	SceneHistroyManager->SceneHistroyStateChange.AddUObject(this, &UInteractiveToolsSubsystem::OnSceneHistroyStateChangeEvnt);
	//提供选中对象的行为 如左键选择 点击BG取消选中 shift多选 etc... 目前选中对象只为SO
	SOSelectionInteraction = NewObject<USceneObjectSelectionInteraction>();
	SOSelectionInteraction->Initialize
	(
		[this]() {return HaveActiveTool() == false; } // 初始化为false
	);
	//注册输入行为  InputRouter会查询所有InputBehavior捕获输入
	ToolContext->InputRouter->RegisterSource(SOSelectionInteraction);
	//创建SO gizmo管理类，选择的对象从subSystem查询，update gizmo 实际也只是从这个类查询 eg::要么在选定对象的原点之间移动，要么在有多个选定对象时移动到共享原点
	//具体实现MeshSceneSubSyetem  SelectionModify回调 每次会生成新的UTransformGizmo 更新  UTransformProxy;
	SOTransformInteraction = NewObject<USceneObjectTransformInteraction>();
	SOTransformInteraction->Initialize
	(
		[this]() {return HaveActiveTool() == false; }
	);
	//创建绘制组件 PDI(PrimitiveDrawInterface)在运行访问只能通过UPrimitiveComponent 
	//由于渲染独立线程 一次PDIRenderComponent::GetPDIForView();并将此PDI最终传递到Gizmo::Render() 
	//FToolsContextRenderComponentSceneProxy::GetDynamicMeshElements()
	FActorSpawnParameters SpawnInfo;
	PDIRenderActor = CurrentWorld->SpawnActor<AActor>(FVector::ZeroVector, FRotator(0, 0, 0), SpawnInfo);
	PDIRenderComponent = NewObject<UToolsContextRenderComponent>(PDIRenderActor);
	PDIRenderActor->SetRootComponent(PDIRenderComponent);
	PDIRenderComponent->RegisterComponent();
	//防止GC PropertySet  目前PropertySet（UObject）只是tool 的属性
	GShouldVerifyGCAssumptions = false;
	// make sure we have registered FPrimitiveComponentTarget factories
	FSimpleDynamicMeshComponentTargetFactory::RegisterFactory();
}

PRAGMA_DISABLE_OPTIMIZATION
void UInteractiveToolsSubsystem::Tick(float DeltaTime)
{
	if (!pViewPawn)
	{
		return;
	}
	GizmoRenderingUtil::SetGlobalFocusedEditorSceneView(nullptr);

	FInputDeviceState InputState = CurrentMouseState;
	InputState.InputDevice = EInputDevices::Mouse;

	FVector2D MousePosition = FSlateApplication::Get().GetCursorPos();
	FVector2D LastMousePosition = FSlateApplication::Get().GetLastCursorPos();
	FModifierKeysState ModifierState = FSlateApplication::Get().GetModifierKeys();
	UGameViewportClient* ViewportClient = CurrentWorld->GetGameViewport();
	TSharedPtr<IGameLayerManager> LayerManager = ViewportClient->GetGameLayerManager();
	FGeometry ViewportGeometry;
	if (ensure(LayerManager.IsValid()))
	{
		ViewportGeometry = LayerManager->GetViewportWidgetHostGeometry();
	}
	FVector2D ViewportMousePos = ViewportGeometry.Scale * ViewportGeometry.AbsoluteToLocal(MousePosition);


	// update modifier keys
	InputState.SetModifierKeyStates(
		ModifierState.IsLeftShiftDown(),
		ModifierState.IsAltDown(),
		ModifierState.IsControlDown(),
		ModifierState.IsCommandDown());

	if (ViewportClient)
	{	
		FSceneViewport* Viewport = ViewportClient->GetGameViewport();
		FEngineShowFlags* ShowFlags = ViewportClient->GetEngineShowFlags();
		//这里是构建一个场景视图成员，用于渲染
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			ViewportClient->Viewport,//render Target 
			CurrentWorld->Scene,//当前世界的数据信息
			*ShowFlags)
			.SetRealtimeUpdate(true));
		//FSceneViewFamily 只是包含了视口数据， 实际渲染需要ViewMatrix ,ProjecttionMatrix 在后面进行求解 VPMatrix 
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(pViewPawn->GetPlayerController()->Player);
		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily,  /*out*/ ViewLocation, /*out*/ ViewRotation, LocalPlayer->ViewportClient->Viewport);
		if (SceneView == nullptr)
		{
			return;		// abort abort
		}

		CurrentViewCameraState.Position = ViewLocation;
		CurrentViewCameraState.Orientation = ViewRotation.Quaternion();
		CurrentViewCameraState.HorizontalFOVDegrees = SceneView->FOV;
		CurrentViewCameraState.AspectRatio = Viewport->GetDesiredAspectRatio(); //ViewportClient->AspectRatio;
		CurrentViewCameraState.bIsOrthographic = false;
		CurrentViewCameraState.bIsVR = false;
		CurrentViewCameraState.OrthoWorldCoordinateWidth = 1;

		FVector4 ScreenPos = SceneView->PixelToScreen(ViewportMousePos.X, ViewportMousePos.Y, 0);

		const FMatrix InvViewMatrix = SceneView->ViewMatrices.GetInvViewMatrix();
		const FMatrix InvProjMatrix = SceneView->ViewMatrices.GetInvProjectionMatrix();

		const float ScreenX = ScreenPos.X;
		const float ScreenY = ScreenPos.Y;

		FVector Origin;
		FVector Direction;
		if (!ViewportClient->IsOrtho())
		{
			Origin = SceneView->ViewMatrices.GetViewOrigin();
			Direction = InvViewMatrix.TransformVector(FVector(InvProjMatrix.TransformFVector4(FVector4(ScreenX * GNearClippingPlane, ScreenY * GNearClippingPlane, 0.0f, GNearClippingPlane)))).GetSafeNormal();
		}
		else
		{
			Origin = InvViewMatrix.TransformFVector4(InvProjMatrix.TransformFVector4(FVector4(ScreenX, ScreenY, 0.5f, 1.0f)));
			Direction = InvViewMatrix.TransformVector(FVector(0, 0, 1)).GetSafeNormal();
		}

		// fudge factor so we don't hit actor...
		Origin += 1.0 * Direction;

		InputState.Mouse.Position2D = ViewportMousePos;
		InputState.Mouse.Delta2D = CurrentMouseState.Mouse.Position2D - PrevMousePosition;
		PrevMousePosition = InputState.Mouse.Position2D;
		InputState.Mouse.WorldRay = FRay(Origin, Direction);


		// if we are in camera control we don't send any events
		EInteractiveMode mode = pViewPawn->GetInteractiveMode();
		bool bInCameraControl = (pViewPawn->GetInteractiveMode() != EInteractiveMode::NoInteraction);
		if (bInCameraControl)
		{
			//ensure(bPendingMouseStateChange == false);
			ensure(ToolContext->InputRouter->HasActiveMouseCapture() == false);
			//ToolsContext->InputRouter->PostHoverInputEvent(InputState);
		}
		else if (bPendingMouseStateChange || ToolContext->InputRouter->HasActiveMouseCapture())
		{
			ToolContext->InputRouter->PostInputEvent(InputState);
		}
		else
		{
			ToolContext->InputRouter->PostHoverInputEvent(InputState);
		}

		// clear down or up flags now that we have sent event
		/*if (bPendingMouseStateChange)
		{
			if (CurrentMouseState.Mouse.Left.bDown)
			{
				CurrentMouseState.Mouse.Left.SetStates(false, true, false);
			}
			else
			{
				CurrentMouseState.Mouse.Left.SetStates(false, false, false);
			}
			bPendingMouseStateChange = false;
		}
*/

		// tick things
		ToolContext->ToolManager->Tick(DeltaTime);
		ToolContext->GizmoManager->Tick(DeltaTime);

		// render things
		FRuntimeToolsFrameworkRenderImpl RenderAPI(PDIRenderComponent, SceneView, CurrentViewCameraState);
		ToolContext->ToolManager->Render(&RenderAPI);
		ToolContext->GizmoManager->Render(&RenderAPI);

		// force rendering flush so that PDI lines get drawn
		FlushRenderingCommands();
	}
}
PRAGMA_ENABLE_OPTIMIZATION

void UInteractiveToolsSubsystem::SetViewPawn(AGameplayPawn* InPawn)
{
	pViewPawn = InPawn;
	if (QueriesAPI)
	{
		QueriesAPI->SetViewPawn(pViewPawn);
	}
}

UInteractiveTool* UInteractiveToolsSubsystem::BeginToolByName(const FString& ToolName)
{
	if (ToolContext && ToolContext->ToolManager)
	{
		bool bFound = ToolContext->ToolManager->SelectActiveToolType(EToolSide::Mouse, ToolName);
		if (bFound)
		{
			bool bActivated = ToolContext->ToolManager->ActivateTool(EToolSide::Mouse);
			if (bActivated)
			{
				UInteractiveTool* NewTool = ToolContext->ToolManager->GetActiveTool(EToolSide::Mouse);
				URuntimeDrawPolygonTool* PolyTool = Cast<URuntimeDrawPolygonTool>(NewTool);
				if (PolyTool)
				{
					PolyTool->RuntimeProperties->SelectedPolygonType = 1;
				}
				return NewTool;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::BeginToolByName - Failed to Activate Tool of type %s!"), *ToolName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::BeginToolByName - Tool Type %s Not Registered!"), *ToolName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::BeginToolByName - Tools Context is not initialized!"));
	}
	return nullptr;
}

UInteractiveMeshSceneObject* UInteractiveToolsSubsystem::GenerateMeshObj(const FString& filePath, bool ccw)
{
	FString absPath = FPaths::ProjectContentDir() + filePath;
	UGeneratedMesh* ImportMesh = NewObject<UGeneratedMesh>();
	if (!ImportMesh->ReadSimpleMeshFromFile(absPath, ccw))
	{
		ImportMesh->AppendSphere(200, 8, 8);
	}
	/*if (!ImportMesh->ReadMeshFromFile(absPath, ccw))
	{
		ImportMesh->AppendSphere(200, 8, 8);
	}*/
	UInteractiveMeshSceneObject* SO = UInteractiveMeshSceneSubsystem::Get()->CreateNewSceneObject();
	SO->Initialize(CurrentWorld, ImportMesh->GetMesh().Get());

	return SO;
}

IToolsContextTransactionsAPI* UInteractiveToolsSubsystem::GetTransactionAPI()
{
	return TransactionAPI.Get();
}

IToolsContextAssetAPI* UInteractiveToolsSubsystem::GetAssetAPI()
{
	return AssetAPI.Get();
}


UInteractiveToolsContext* UInteractiveToolsSubsystem::GetToolContext()
{
	return ToolContext;
}

void UInteractiveToolsSubsystem::OnToolStartedEvnt(UInteractiveToolManager* InManager, UInteractiveTool* InInteractiveTool)
{
	AddAllPropertySetKeepAlives(InInteractiveTool);
	//SOTransformInteraction->ForceUpdateGizmoState();

}

void UInteractiveToolsSubsystem::OnToolEndedEvnt(UInteractiveToolManager* InManager, UInteractiveTool* InInteractiveTool)
{
	if (!bIsShuttingDown)
	{
		//SOTransformInteraction->ForceUpdateGizmoState();
	}
}


void UInteractiveToolsSubsystem::AddAllPropertySetKeepAlives(UInteractiveTool* Tool)
{
	TArray<UObject*> PropertySets = Tool->GetToolProperties(false);
	for (UObject* PropSetObj : PropertySets)
	{
		if (UInteractiveToolPropertySet* PropertySet = Cast<UInteractiveToolPropertySet>(PropSetObj))
		{
			AddPropertySetKeepAlive(PropertySet);
		}
	}
}

void UInteractiveToolsSubsystem::AddPropertySetKeepAlive(UInteractiveToolPropertySet* PropertySet)
{
	//Get Class Default OBJ

	if (ensure(PropertySet != nullptr))
	{
		bool bCached = false;

		UInteractiveToolPropertySet* CDO = GetMutableDefault<UInteractiveToolPropertySet>(PropertySet->GetClass());

		for (TFieldIterator<FProperty> It(PropertySet->GetClass(), EFieldIteratorFlags::IncludeSuper); It; ++It)
		{
			FString Name = It->GetName();
			if (Name == TEXT("CachedProperties"))
			{
				const FProperty* Property = *It;
				if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
				{
					UObject* TargetObject = ObjectProperty->GetObjectPropertyValue(Property->ContainerPtrToValuePtr<UObject*>(CDO));
					PropertySetKeepAlives.AddUnique(TargetObject);
					bCached = true;
				}
			}
		}

		if (bCached == false)
		{
			FString PropSetName;
			PropertySet->GetClass()->GetName(PropSetName);
			UE_LOG(LogTemp, Warning, TEXT("Failed to find PropertySet Keepalive for %s!"), *PropSetName);
		}
	}
}

void UInteractiveToolsSubsystem::OnSceneHistroyStateChangeEvnt()
{
	if (!bIsShuttingDown)
	{
		SOTransformInteraction->ForceUpdateGizmoState();
	}
}

void UInteractiveToolsSubsystem::OnLeftMouseDown()
{
	CurrentMouseState.Mouse.Left.SetStates(true, false, false);
	bPendingMouseStateChange = true;
}

void UInteractiveToolsSubsystem::OnLeftMouseUp()
{
	CurrentMouseState.Mouse.Left.SetStates(false, false, true);
	bPendingMouseStateChange = true;
}

bool UInteractiveToolsSubsystem::HaveActiveTool()
{
	return (ToolContext != nullptr) && (ToolContext->ToolManager != nullptr)
		&& (ToolContext->ToolManager->HasActiveTool(EToolSide::Mouse));
}


bool UInteractiveToolsSubsystem::isCaptureingMouse() const
{
	return ToolContext->InputRouter->HasActiveMouseCapture();
}

bool UInteractiveToolsSubsystem::AcceptActiveTool()
{
	if (ToolContext && ToolContext->ToolManager)
	{
		bool bActive = ToolContext->ToolManager->HasActiveTool(EToolSide::Mouse);
		if (bActive)
		{
			bool bCanAccept = ToolContext->ToolManager->CanAcceptActiveTool(EToolSide::Mouse);
			if (bCanAccept)
			{
				ToolContext->ToolManager->DeactivateTool(EToolSide::Mouse, EToolShutdownType::Accept);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::AcceptActiveTool - Cannot Accept Active Tool!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::AcceptActiveTool - No Active Tool!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::AcceptActiveTool - Tools Context is not initialized!"));
	}

	InternalConsistencyChecks();
	return false;
}

bool UInteractiveToolsSubsystem::CancelOrCompleteActiveTool()
{
	if (ToolContext && ToolContext->ToolManager)
	{
		bool bActive = ToolContext->ToolManager->HasActiveTool(EToolSide::Mouse);
		if (bActive)
		{
			EToolShutdownType ShutdownType = ToolContext->ToolManager->CanCancelActiveTool(EToolSide::Mouse) ?
				EToolShutdownType::Cancel : EToolShutdownType::Completed;
			ToolContext->ToolManager->DeactivateTool(EToolSide::Mouse, ShutdownType);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::CancelOrCompleteActiveTool - No Active Tool!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::CancelOrCompleteActiveTool - Tools Context is not initialized!"));
	}

	InternalConsistencyChecks();
	return false;
}

void UInteractiveToolsSubsystem::InternalConsistencyChecks()
{
	if (GetSceneHistory())
	{
		if (!ensure(GetSceneHistory()->IsBuildingTransaction() == false))
		{
			UE_LOG(LogTemp, Warning, TEXT("[URuntimeToolsFrameworkSubsystem::InternalConsistencyChecks] still Building Transaction! Likely forgot to EndTransaction() somewhere!!"));
		}
	}
}

//
//void UInteractiveToolsSubsystem::ShutDownInteractiveTools()
//{
//	bIsShuttingDown = true;
//	if (InteractiveToolsContext != nullptr)
//	{
//		CancelOrCompleteActiveTool();
//
//		SOTransformInteraction->Shutdown();
//
//		InteractiveToolsContext->Shutdown();
//	}
//	if (PDIRenderActor)
//	{
//		PDIRenderActor->Destroy();
//		PDIRenderActor = nullptr;
//		PDIRenderComponent = nullptr;
//	}
//
//	CurrentWorld = nullptr;
//	InteractiveToolsContext = nullptr;
//	ContextActor = nullptr;
//	
//	ToolsContextQueriesAPI = nullptr;
//	ToolsContextTransactionAPI = nullptr;
//	ToolsContextAssetAPI = nullptr;
//	SOSelectionInteraction = nullptr;
//	SOTransformInteraction = nullptr;
//
//	bIsShuttingDown = false;
//	
//}
//

//

//

//
//bool UInteractiveToolsSubsystem::AcceptActiveTool()
//{
//	if (InteractiveToolsContext && InteractiveToolsContext->ToolManager)
//	{
//		bool bActive = InteractiveToolsContext->ToolManager->HasActiveTool(EToolSide::Mouse);
//		if (bActive)
//		{
//			bool bCanAccept = InteractiveToolsContext->ToolManager->CanAcceptActiveTool(EToolSide::Mouse);
//			if (bCanAccept)
//			{
//				InteractiveToolsContext->ToolManager->DeactivateTool(EToolSide::Mouse, EToolShutdownType::Accept);
//			}
//			else
//			{
//				UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::AcceptActiveTool - Cannot Accept Active Tool!"));
//			}
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::AcceptActiveTool - No Active Tool!"));
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::AcceptActiveTool - Tools Context is not initialized!"));
//	}
//
//	InternalConsistencyChecks();
//	return false;
//}
//
//bool UInteractiveToolsSubsystem::CancelOrCompleteActiveTool()
//{
//	if (InteractiveToolsContext && InteractiveToolsContext->ToolManager)
//	{
//		bool bActive = InteractiveToolsContext->ToolManager->HasActiveTool(EToolSide::Mouse);
//		if (bActive)
//		{
//			EToolShutdownType ShutdownType = InteractiveToolsContext->ToolManager->CanCancelActiveTool(EToolSide::Mouse) ?
//				EToolShutdownType::Cancel : EToolShutdownType::Completed;
//			InteractiveToolsContext->ToolManager->DeactivateTool(EToolSide::Mouse, ShutdownType);
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::CancelOrCompleteActiveTool - No Active Tool!"));
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("URuntimeToolsFrameworkSubsystem::CancelOrCompleteActiveTool - Tools Context is not initialized!"));
//	}
//
//	InternalConsistencyChecks();
//	return false;
//}
//
//bool UInteractiveToolsSubsystem::CanActivateToolByName(FString Name)
//{
//	return true;
//}
//
//UInteractiveTool* UInteractiveToolsSubsystem::BeginToolByName(FString ToolName)
//{
//	if (InteractiveToolsContext && InteractiveToolsContext->ToolManager)
//	{
//		bool bFound = InteractiveToolsContext->ToolManager->SelectActiveToolType(EToolSide::Mouse, ToolName);
//		if (bFound)
//		{
//			bool bActive = InteractiveToolsContext->ToolManager->ActivateTool(EToolSide::Mouse);
//			if (bActive)
//			{
//				UInteractiveTool* NewTool = InteractiveToolsContext->ToolManager->GetActiveTool(EToolSide::Mouse);
//				return NewTool;
//			}
//			else
//			{
//				DebugHelper::Count() << "InteractiveToolSubSystem-->BeginToolByName()" << "Failed Activeate Tool By Type"<< ToolName<< DebugHelper::Endl();
//			}
//
//		}
//		else
//		{
//			DebugHelper::Count() << "InteractiveToolSubSystem-->BeginToolByName()" << " Tool Type Not Register" << DebugHelper::Endl();
//		}
//	}
//	else
//	{
//		DebugHelper::Count() << "InteractiveToolSubSystem-->BeginToolByName()" << "InteractiveToolConext is not Initialize!" << DebugHelper::Endl();
//	}
//	
//	return nullptr;
//}
//
//IToolsContextTransactionsAPI* UInteractiveToolsSubsystem::GetTransactionAPI()
//{
//	return ToolsContextTransactionAPI.Get();
//}
//
//IToolsContextAssetAPI* UInteractiveToolsSubsystem::GetAssetAPI()
//{
//	return ToolsContextAssetAPI.Get();
//}
//
//TArray<UObject*> UInteractiveToolsSubsystem::GetActiveToolPropertySets()
//{
//	TArray<UObject*> Results;
//	if (HaveActiveTool())
//	{
//		Results = InteractiveToolsContext->ToolManager->GetActiveTool(EToolSide::Mouse)->GetToolProperties();
//	}
//	return Results;
//}
//
//void UInteractiveToolsSubsystem::SetCurrentCoordinateSystem(EToolContextCoordinateSystem CoordSystem)
//{
//	CurrentCoordinateSystem = CoordSystem;
//}
//
//void UInteractiveToolsSubsystem::CycleCurrentCoordinateSystem()
//{
//	int32 CurCoordSystem = (int)CurrentCoordinateSystem;
//	int32 NewCoordSystem = (CurCoordSystem + 1) % 2;
//	SetCurrentCoordinateSystem((EToolContextCoordinateSystem)(NewCoordSystem));
//}
//

//
//UInteractiveTool* UInteractiveToolsSubsystem::GetActiveTool()
//{
//	return HaveActiveTool() ? InteractiveToolsContext->ToolManager->GetActiveTool(EToolSide::Mouse) : nullptr;
//}
//
//bool UInteractiveToolsSubsystem::IsActiveToolAcceptCancelType()
//{
//	return (InteractiveToolsContext != nullptr)
//		&& (InteractiveToolsContext->ToolManager != nullptr)
//		&& InteractiveToolsContext->ToolManager->HasActiveTool(EToolSide::Mouse)
//		&& InteractiveToolsContext->ToolManager->GetActiveTool(EToolSide::Mouse)->HasAccept();
//
//}
//
//bool UInteractiveToolsSubsystem::CanAcceptActiveTool()
//{
//	return (InteractiveToolsContext != nullptr)
//		&& (InteractiveToolsContext->ToolManager != nullptr)
//		&& InteractiveToolsContext->ToolManager->CanAcceptActiveTool(EToolSide::Mouse);
//}
//

//
//UInteractiveMeshSceneObject* UInteractiveToolsSubsystem::ImportMeshSceneObject(const FString Path, bool bFlipOrientation)
//{
//	FString UsePath = Path;
//	if (FPaths::FileExists(UsePath) == false && FPaths::IsRelative(UsePath))
//	{
//		UsePath = FPaths::ProjectContentDir() + Path;
//	}
//
//	UGeneratedMesh* ImportMesh = NewObject<UGeneratedMesh>();
//	if (ImportMesh->ReadMeshFromFile(UsePath, bFlipOrientation) == false)
//	{
//		ImportMesh->AppendSphere(200, 8, 8);
//	}
//
//	UInteractiveMeshSceneObject* SceneObject = UInteractiveMeshSceneSubsystem::Get()->CreateNewSceneObject();
//	SceneObject->Initialize(CurrentWorld, ImportMesh->GetMesh().Get());
//
//	return SceneObject;
//}
//

//
//bool UInteractiveToolsSubsystem::IsCapturingMouse() const
//{
//	return InteractiveToolsContext && InteractiveToolsContext->InputRouter->HasActiveMouseCapture();
//}
//
//void UInteractiveToolsSubsystem::OnLeftMouseDown()
//{
//	CurrentMouseState.Mouse.Left.SetStates(true, false, false);
//	bPendingMouseStateChange = true;
//}
//
//void UInteractiveToolsSubsystem::OnLeftMouseUp()
//{
//	CurrentMouseState.Mouse.Left.SetStates(false, false, true);
//	bPendingMouseStateChange = true;
//}
//
