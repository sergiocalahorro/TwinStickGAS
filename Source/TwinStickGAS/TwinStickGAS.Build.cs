// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TwinStickGAS : ModuleRules
{
	public TwinStickGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"ModularGameplay",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"ObjectPool"
		});
	}
}
