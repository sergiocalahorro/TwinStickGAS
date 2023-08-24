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
			"CommonInput",
			"ObjectPool"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"ModularGameplay",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
	}
}
