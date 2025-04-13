// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mystery : ModuleRules
{
	public Mystery(ReadOnlyTargetRules Target) : base(Target)
	{
		// for debug only
		//OptimizeCode = CodeOptimization.Never;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Mystery/Public"
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"Mystery/Private",
				"Mystery/Tests"
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", 
			"CoreUObject", "Engine", "InputCore", "EnhancedInput", 
			"UnrealEd", // Add this line for test utilities
			"AIModule"
              });
		

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore"
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
		

	}
}
