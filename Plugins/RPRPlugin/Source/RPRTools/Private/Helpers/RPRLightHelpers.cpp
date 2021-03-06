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

#include "Helpers/RPRLightHelpers.h"
#include "RadeonProRender.h"
#include "Helpers/GenericGetInfo.h"

namespace RPR
{
	namespace Light
	{

		template<typename T>
		RPR::FResult GetInfoNoAlloc(RPR::FLight Light, RPR::ELightInfo Info, T& OutValue)
		{
			return RPR::Generic::GetInfoNoAlloc(rprLightGetInfo, Light, Info, &OutValue);
		}

		template<typename T>
		RPR::FResult GetInfoToArray(RPR::FLight Light, RPR::ELightInfo Info, TArray<T>& OutValue)
		{
			return RPR::Generic::GetInfoToArray(rprLightGetInfo, Light, Info, OutValue);
		}

		//////////////////////////////////////////////////////////////////////////

		RPR::FResult GetName(RPR::FLight Light, FString& OutObjectName)
		{
			return RPR::Generic::GetObjectName(rprLightGetInfo, Light, OutObjectName);
		}

		FString		GetName(RPR::FLight Light)
		{
			FString name;
			RPR::FResult status = GetName(Light, name);
			if (RPR::IsResultFailed(status))
			{
				name = TEXT("[Unknown]");
			}
			if (name.IsEmpty())
			{
				name = TEXT("[Undefined]");
			}
			return (name);
		}

		RPR::FResult GetWorldTransform(RPR::FLight Light, FTransform& OutTransform)
		{
			return RPR::Generic::GetObjectTransform(rprLightGetInfo, Light, ELightInfo::Transform, OutTransform);
		}

		RPR::FResult SetWorldTransform(RPR::FLight Light, FTransform Transform)
		{
			RadeonProRender::matrix matrix = BuildMatrixWithScale(Transform);

			RPR::FResult status = rprLightSetTransform(Light, RPR_TRUE, &matrix.m00);

			UE_LOG(LogRPRTools_Step, Verbose,
				TEXT("rprLightSetTransform(light=%s, tranpose=true, matrix=%s) -> %d"),
				*RPR::Light::GetName(Light),
				*Transform.ToString(),
				status
			);

			return status;
		}

		RPR::FResult GetLightType(RPR::FLight Light, RPR::ELightType& OutLightType)
		{
			return GetInfoNoAlloc(Light, ELightInfo::Type, OutLightType);
		}

		bool IsLightPowerSupportedByLightType(RPR::ELightType LightType)
		{
			switch (LightType)
			{
				case ELightType::Point:
				case ELightType::Directional:
				case ELightType::Spot:
				case ELightType::IES:
				return true;

				default:
				return false;
			}
		}

		RPR::FResult GetLightPower(RPR::FLight Light, RPR::ELightType LightType, FLinearColor& OutColor)
		{
			ELightInfo lightInfoType;
			bool isLightInfoSupported = true;

			switch (LightType)
			{
				case ELightType::Point:
				lightInfoType = ELightInfo::PointLight_RadiantPower;
				break;

				case ELightType::Directional:
				lightInfoType = ELightInfo::DirectionalLight_RadiantPower;
				break;

				case ELightType::Spot:
				lightInfoType = ELightInfo::SpotLight_RadiantPower;
				break;

				case ELightType::IES:
				lightInfoType = ELightInfo::IES_RadiantPower;
				break;
			
				default:
				isLightInfoSupported = false;
				lightInfoType = (ELightInfo) 0x0;
				break;
			}

			if (isLightInfoSupported)
			{
				return GetInfoNoAlloc(Light, lightInfoType, OutColor);
			}

			return (RPR_ERROR_UNSUPPORTED);
		}

		RPR::FResult GetLightConeShape(RPR::FLight Light, float& OutInnerAngle, float& OutOuterAngle)
		{
			FVector2D values;
			RPR::FResult status = GetInfoNoAlloc(Light, ELightInfo::SpotLight_ConeShape, values);
			if (RPR::IsResultSuccess(status))
			{
				OutInnerAngle = values[0];
				OutOuterAngle = values[1];
			}
			return status;
		}

		RPR::FResult GetEnvironmentLightIntensityScale(RPR::FLight Light, float& OutLightIntensityScale)
		{
			return GetInfoNoAlloc(Light, ELightInfo::Environment_LightIntensityScale, OutLightIntensityScale);
		}

		RPR::FResult GetEnvironmentLightImage(RPR::FLight Light, RPR::FImage& OutImage)
		{
			return GetInfoNoAlloc(Light, ELightInfo::Environment_Image, OutImage);
		}

		RPR::FResult GetDirectionalShadowSoftness(RPR::FLight Light, float& OutShadowSoftness)
		{
			return GetInfoNoAlloc(Light, ELightInfo::DirectionalLight_ShadowSoftness, OutShadowSoftness);
		}

	} // namespace Light
} // namespace RPR

