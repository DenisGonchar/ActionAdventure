// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionAdventure : ModuleRules
{
	public ActionAdventure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
			"Json",
			"JsonUtilities", 
			"DeveloperSettings"
		});
	}
}
