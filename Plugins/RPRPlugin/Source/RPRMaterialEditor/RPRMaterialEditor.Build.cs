// Some copyright should be here...

using UnrealBuildTool;

/// <summary>
/// Module for all the RPRMaterial editor part (editor-only).
/// </summary>
public class RPRMaterialEditor : ModuleRules
{
	public RPRMaterialEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        DefineIncludesAndDependencies();
    }

    void DefineIncludesAndDependencies()
    {
        PublicIncludePaths.AddRange(
            new string[] {
                "RPRMaterialEditor/Public",
                "RPRPlugin/Public",
				// ... add public include paths required here ...
                
                "Runtime/Slate/Private"
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "RPRMaterialEditor/Private",

                "RPRMaterialEditor/Private/Tools/PropertyHelper",

                "RPRMaterialEditor/Private/RPRMaterialEditor",
                "RPRMaterialEditor/Public/RPRMaterialEditor/PropertiesLayout",

                "RPRMaterialEditor/Private"
				// ... add other private include paths required here ...
			}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "RPR_SDK",
                "RPRPlugin",
                "RPRMaterialImporter",
                "RPREditorTools",
                "RPRTools",
                "RPRImageManager"
				
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
                "EditorStyle",
                "Slate",
                "LevelEditor",
                "Settings",
                "PropertyEditor",
                "MaterialEditor",
                "AssetTools",
                "AppFramework"
				// ... add private dependencies that you statically link with here ...	
			}
        );
    }
}
