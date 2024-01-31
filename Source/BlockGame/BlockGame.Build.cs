// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlockGame : ModuleRules
{
	public BlockGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite", "Niagara"});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",  "SlateCore", "Niagara" });
	}
}
