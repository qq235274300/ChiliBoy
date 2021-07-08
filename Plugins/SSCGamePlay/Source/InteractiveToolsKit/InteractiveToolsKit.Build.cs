// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InteractiveToolsKit : ModuleRules
{
	public InteractiveToolsKit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "RenderCore",
            "InteractiveToolsFramework",
            "MeshDescription",
            "StaticMeshDescription",
            "GeometricObjects",
            "DynamicMesh",
            "MeshConversion",
            "ModelingComponents",
            "MeshModelingTools",
             "RuntimeGeometryUtils"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "HelperKits",
                 "SSCPlugins",

            }
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
