//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "InteractiveToolsDriver.h"
//#include "HelperKits/Public/DebugHelper.h"
//#include <AddPrimitiveTool.h>
//#include <DrawAndRevolveTool.h>
//#include <Tools/RuntimeDrawPolygonTool.h>
//#include <Tools/RuntimePolyEditTool.h>
//#include <PlaneCutTool.h>
//#include <Tools/RuntimeRemeshMeshTool.h>
//#include <MeshVertexSculptTool.h>
//#include <Tools/RuntimeDynamicMeshSculptTool.h>
//#include <Tools/RuntimeMeshBooleanTool.h>
//
//AInteractiveToolsDriver::AInteractiveToolsDriver()
//{
//	PrimaryActorTick.bStartWithTickEnabled = true;
//	PrimaryActorTick.bCanEverTick = true;
//	
//}
//void AInteractiveToolsDriver::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	if (InteractiveToolSubSystem)
//	{
//		InteractiveToolSubSystem->Tick(DeltaTime);
//	}
//}
//
//
//void AInteractiveToolsDriver::BeginPlay()
//{
//	Super::BeginPlay();
//	InitializeToolsSystem();	
//}
//
//void AInteractiveToolsDriver::InitializeToolsSystem()
//{
//	UWorld* CurrentWorld = GetWorld();
//	UGameInstance* CurrentInstance = GetGameInstance();
//
//	check(CurrentWorld && CurrentInstance);
//	InteractiveToolSubSystem = CurrentInstance->GetSubsystem<UInteractiveToolsSubsystem>(CurrentInstance);
//	UInteractiveToolsSubsystem::InitSubSysytem(InteractiveToolSubSystem);
//	InteractiveMeshSceneSubSystem = CurrentInstance->GetSubsystem<UInteractiveMeshSceneSubsystem>(CurrentInstance);
//	UInteractiveMeshSceneSubsystem::InitSubSysytem(InteractiveMeshSceneSubSystem);
//
//	check(InteractiveToolSubSystem && InteractiveMeshSceneSubSystem);
//	InteractiveToolSubSystem->Init(CurrentWorld);
//	InteractiveMeshSceneSubSystem->SetCurrentTransactionAPI(InteractiveToolSubSystem->GetTransactionAPI());
//	RegisterTool();
//}
//
//void AInteractiveToolsDriver::ShutdownToolsSystem()
//{
//	check(false);
//}
//
//void AInteractiveToolsDriver::RegisterTool()
//{
//	UInteractiveToolManager* InteractiveToolManager = InteractiveToolSubSystem->ToolContext->ToolManager;
//	
//	auto AddPrimitiveToolBuilder = NewObject<UAddPrimitiveToolBuilder>();
//	AddPrimitiveToolBuilder->AssetAPI = InteractiveToolSubSystem->GetAssetAPI();
//	AddPrimitiveToolBuilder->ShapeType = UAddPrimitiveToolBuilder::EMakeMeshShapeType::Box;
//	InteractiveToolManager->RegisterToolType("AddPrimitiveBox", AddPrimitiveToolBuilder);
//
//	auto DrawPolygonToolBuilder = NewObject<URuntimeDrawPolygonToolBuilder>();
//	DrawPolygonToolBuilder->AssetAPI = InteractiveToolSubSystem->GetAssetAPI();
//	InteractiveToolManager->RegisterToolType("DrawPolygon", DrawPolygonToolBuilder);
//
//	auto PolyRevolveToolBuilder = NewObject<UDrawAndRevolveToolBuilder>();
//	PolyRevolveToolBuilder->AssetAPI = InteractiveToolSubSystem->GetAssetAPI();
//	InteractiveToolManager->RegisterToolType("PolyRevolve", PolyRevolveToolBuilder);
//
//	auto PolyEditToolBuilder = NewObject<URuntimePolyEditToolBuilder>();
//	InteractiveToolManager->RegisterToolType("EditPolygons", PolyEditToolBuilder);
//
//	auto MeshPlaneCutToolBuilder = NewObject<UPlaneCutToolBuilder>();
//	MeshPlaneCutToolBuilder->AssetAPI = InteractiveToolSubSystem->GetAssetAPI();
//	InteractiveToolManager->RegisterToolType("PlaneCut", MeshPlaneCutToolBuilder);
//
//	auto RemeshMeshToolBuilder = NewObject<URuntimeRemeshMeshToolBuilder>();
//	RemeshMeshToolBuilder->AssetAPI = InteractiveToolSubSystem->GetAssetAPI();
//	InteractiveToolManager->RegisterToolType("RemeshMesh", RemeshMeshToolBuilder);
//
//	auto VertexSculptToolBuilder = NewObject<UMeshVertexSculptToolBuilder>();
//	InteractiveToolManager->RegisterToolType("VertexSculpt", VertexSculptToolBuilder);
//
//	auto DynaSculptToolBuilder = NewObject<URuntimeDynamicMeshSculptToolBuilder>();
//	DynaSculptToolBuilder->bEnableRemeshing = true;
//	InteractiveToolManager->RegisterToolType("DynaSculpt", DynaSculptToolBuilder);
//
//	auto MeshBooleanToolBuilder = NewObject<URuntimeMeshBooleanToolBuilder>();
//	MeshBooleanToolBuilder->AssetAPI = InteractiveToolSubSystem->GetAssetAPI();
//	InteractiveToolManager->RegisterToolType("MeshBoolean", MeshBooleanToolBuilder);
//}
//
