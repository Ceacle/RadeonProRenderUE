// Some copyright should be here...

using UnrealBuildTool;

public class Outliners : ModuleRules
{
	public Outliners(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        DefineIncludesAndDependencies();
    }

    void DefineIncludesAndDependencies()
    {
        PublicIncludePaths.AddRange(
            new string[] {
                "Outliners/Public",
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "Outliners/Private",
                "Outliners/Private/SObjectOutliner"
				// ... add other private include paths required here ...
			}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
				
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
                "UnrealEd",
                "InputCore",
                "RawMesh",
                "EditorStyle",
				"RPREditorTools"
				// ... add private dependencies that you statically link with here ...	
			}
        );
    }
    
}
