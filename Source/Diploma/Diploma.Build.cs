// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Diploma : ModuleRules
{
	public Diploma(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Foliage" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
