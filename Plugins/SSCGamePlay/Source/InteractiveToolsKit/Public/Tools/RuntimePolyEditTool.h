#pragma once

#include "EditMeshPolygonsTool.h"
#include "RuntimePolyEditTool.generated.h"

UCLASS()
class INTERACTIVETOOLSKIT_API URuntimePolyEditToolBuilder : public UEditMeshPolygonsToolBuilder
{
	GENERATED_BODY()
public:
	virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;
};


UCLASS(BlueprintType)
class INTERACTIVETOOLSKIT_API URuntimePolyEditToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
public:

};


UCLASS(BlueprintType)
class INTERACTIVETOOLSKIT_API URuntimePolyEditTool : public UEditMeshPolygonsTool
{
	GENERATED_BODY()

public:
	virtual void Setup() override;

	UPROPERTY(BlueprintReadOnly)
	URuntimePolyEditToolProperties* RuntimeProperties;



	UFUNCTION(BlueprintCallable)
	void BeginExtrudeAction();

	UFUNCTION(BlueprintCallable)
	void BeginInsetAction();

	UFUNCTION(BlueprintCallable)
	void BeginOutsetAction();

	UFUNCTION(BlueprintCallable)
	void BeginCutFacesAction();


};