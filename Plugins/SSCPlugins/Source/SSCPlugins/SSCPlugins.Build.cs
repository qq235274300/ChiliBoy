// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;


public class SSCPlugins : ModuleRules
{
    public SSCPlugins(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //PublicIncludePaths.Add(ModuleDirectory);
        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "CommandShop"));
        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "MultiViewPort"));
        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "SSCInventory"));
        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "VisualCustomWidget"));

        PublicIncludePaths.AddRange(
            new string[] {

               
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                 "SSCPlugins",
                "SSCPlugins/Private",
                "SSCPlugins/Public",
                "SSCPlugins/Public/SSCCommon",
                "SSCPlugins/Private/SSCCommon",
                "SSCPlugins/Public/SSCCore",
                "SSCPlugins/Private/SSCCore",
                "SSCPlugins/Public/SSCGame",
                "SSCPlugins/Private/SSCGame",
                "SSCPlugins/Public/SSCObject",
                "SSCPlugins/Private/SSCObject",
                "SSCPlugins/Public/SSCTest",
                "SSCPlugins/Private/SSCTest",
                  "SSCPlugins/Public/SSCUI",
                "SSCPlugins/Private/SSCUI",
                 "SSCPlugins/SSCInventory/Public",
                "SSCPlugins/SSCInventory/Private",          
                "SSCPlugins/VisualCustomWidget/Public",
                "SSCPlugins/VisualCustomWidget/Private",
                "SSCPlugins/MultiViewPort/Public",
                "SSCPlugins/MultiViewPort/Private",
                 "SSCPlugins/CommandShop/Public",
                "SSCPlugins/CommandShop/Private",
             
            }
            );


        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Engine",
                "Projects",
                "Slate",
                "SlateCore"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",		
                "UMG",
                "InputCore",
                "XmlParser",
                "Sockets",
                "Json",
                "Http",
                "JsonUtilities",
                "MoviePlayer",
                "AIModule",
                "GameplayTasks",
                "HeadMountedDisplay",
                "ProceduralMeshComponent",                     
				// ... add private dependencies that you statically link with here ...	
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
