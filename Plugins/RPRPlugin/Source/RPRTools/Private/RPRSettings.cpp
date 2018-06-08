// RPR COPYRIGHT

#include "RPRSettings.h"
#include "Paths.h"

DEFINE_LOG_CATEGORY_STATIC(LogRPRSettings, Log, All);

URPRSettings::URPRSettings(const FObjectInitializer& PCIP)
	: Super(PCIP)
	, RenderCachePath(FPaths::GameSavedDir() + "/RadeonProRender/Cache/")
	, TraceFolder(FPaths::GameSavedDir() + "/RadeonProRender/Trace/")
	, MaximumRenderIterations(32)
	, bEnableGPU1(true)
	, bEnableGPU2(true)
	, bEnableGPU3(true)
	, bEnableGPU4(true)
	, bEnableGPU5(true)
	, bEnableGPU6(true)
	, bEnableGPU7(true)
	, bEnableGPU8(true)
	, bEnableCPU(false) // By default, no GPUs available, abort
	, QualitySettings(ERPRQualitySettings::Medium)
	, MegaPixelCount(2.0f)
	, bSync(true)
	, bTrace(false)
	, WhiteBalanceTemperature(6500)
	, GammaCorrectionValue(1.0001f)
	, SimpleTonemapExposure(0.0f)
	, SimpleTonemapContrast(1.0f)
	, PhotolinearTonemapSensitivity(20.0f)
	, PhotolinearTonemapExposure(0.1f)
	, PhotolinearTonemapFStop(3.4f)
	, bUseErrorTexture(true)
{
	DefaultRootDirectoryForImportedTextures.Path = TEXT("/Game/Textures");
	ErrorTexture = LoadObject<UTexture2D>(nullptr, TEXT("/RPRPlugin/UETextures/T_TextureNotSupported.T_TextureNotSupported"));
	TryLoadUberMaterialFromDefaultLocation();
}

void URPRSettings::TryLoadUberMaterialFromDefaultLocation()
{
	UberMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/RPRPlugin/Materials/M_UberMaterialTemplate.M_UberMaterialTemplate"));
}

/*void	URPRSettings::PostEditChangeProperty(struct FPropertyChangedEvent &propertyChangedEvent)
{
	Super::PostEditChangeProperty(propertyChangedEvent);

	UProperty	*prop = propertyThatChanged.Property;
	if (prop->GetName() == "RenderCachePath")
	{
		// TODO: Cleanup the path & notify scene
	}
	// TODO: For other settings, notify the scene
}*/
