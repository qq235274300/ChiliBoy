// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class SSCLoadingScreen : ModuleRules
{
    public SSCLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
       

        PublicIncludePaths.AddRange(
            new string[] {

               
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                
                "SSCLoadingScreen/Private/LoadingLayOut",
               "SSCLoadingScreen/Public/LoadingLayOut",

            }
            );


        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                 "SSCPlugins"
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
                "MoviePlayer",
                "DeveloperSettings",
                "UMG"
             
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
