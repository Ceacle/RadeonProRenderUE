#pragma once

#include "RPRMaterialBaseMap.h"
#include "UnrealString.h"
#include "RPRMaterialMapMode.h"
#include "RPRMaterialMapChannel1.generated.h"

/*
* Represents a parameter that can be a map or a float
*/
USTRUCT(BlueprintType)
struct RPRPLUGIN_API FRPRMaterialMapChannel1 : public FRPRMaterialBaseMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	float		Constant;

	UPROPERTY(EditAnywhere, Category = Material)
	ERPRMaterialMapMode		Mode;


	FRPRMaterialMapChannel1() {}
	FRPRMaterialMapChannel1(const FString& InXmlParamName, uint32 InRprxParamID, float InConstantValue = 1.0f);

};