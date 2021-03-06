/*************************************************************************
* Copyright 2020 Advanced Micro Devices
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*************************************************************************/

#pragma once

#include "UObject/ObjectMacros.h"
#include "TriPlanarSettings.generated.h"

/**
 * Describes the settings of the tri planar mode
 */
USTRUCT(BlueprintType)
struct RPRCORE_API FTriPlanarSettings
{
	GENERATED_BODY()

public:

	FTriPlanarSettings();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool	bUseTriPlanar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	Angle;

};
