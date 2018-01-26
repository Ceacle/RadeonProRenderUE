#include "RPRMaterialHelpers.h"
#include "RadeonProRender.h"
#include "RPRHelpers.h"
#include "LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogRPRMaterialHelpers, Log, All)

namespace RPR
{
	const TCHAR* FMaterialHelpers::ImageDataInputName(TEXT("data"));

	FResult FMaterialHelpers::CreateNode(FMaterialSystem MaterialSystem, EMaterialNodeType NodeType, FMaterialNode& OutMaterialNode)
	{
		FResult result = rprMaterialSystemCreateNode(MaterialSystem, NodeType, &OutMaterialNode);

		if (IsResultFailed(result))
		{
			UE_LOG(LogRPRMaterialHelpers, Warning, TEXT("Couldn't create RPR material node (%#08)"), result);
		}

		return (result);
	}

	RPR::FResult FMaterialHelpers::DeleteNode(FMaterialNode& MaterialNode)
	{
		FResult result = rprObjectDelete(MaterialNode);
		MaterialNode = nullptr;
		return (result);
	}

	RPR::FResult FMaterialHelpers::CreateImageNode(RPR::FContext RPRContext, FMaterialSystem MaterialSystem, 
															UTexture2D* Texture, FMaterialNode& OutMaterialNode)
	{
		RPR::FResult result = CreateNode(MaterialSystem, EMaterialNodeType::ImageTexture, OutMaterialNode);
		if (IsResultSuccess(result))
		{
			// TODO : Cache the image built
			RPR::FImage image = BuildImage(Texture, RPRContext);
			result = rprMaterialNodeSetInputImageData(OutMaterialNode, TCHAR_TO_ANSI(ImageDataInputName), image);
		}

		return (result);
	}

}