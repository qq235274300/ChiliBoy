#pragma once

#include "RemeshMeshTool.h"
#include "RuntimeRemeshMeshTool.generated.h"

/** ToolBuilder for URuntimeDrawPolygonTool instances */
UCLASS()
class INTERACTIVETOOLSKIT_API URuntimeRemeshMeshToolBuilder : public URemeshMeshToolBuilder
{
	GENERATED_BODY()
public:
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};



UCLASS(BlueprintType)
class INTERACTIVETOOLSKIT_API URuntimeRemeshMeshToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int TargetTriangleCount;

	UPROPERTY(BlueprintReadWrite)
	bool bDiscardAttributes;
};


UCLASS(BlueprintType)
class INTERACTIVETOOLSKIT_API URuntimeRemeshMeshTool : public URemeshMeshTool
{
	GENERATED_BODY()

public:
	virtual void Setup() override;

	UPROPERTY(BlueprintReadOnly)
	URuntimeRemeshMeshToolProperties* RuntimeProperties;
};