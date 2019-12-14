/**********************************************************************
* Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
********************************************************************/
#pragma once

#include "Containers/UnrealString.h"
#include "Typedefs/RPRTypedefs.h"
#include "Helpers/RPRHelpers.h"
#include "Enums/RPREnums.h"
#include "ImageManager/RPRImageManager.h"
#include "Templates/IsEnum.h"

namespace RPR
{
	/*
	* Interface between the RPR material native functions and UE4
	*/
	class RPRCORE_API FMaterialHelpers
	{
	public:

		static const TCHAR*	ImageDataInputName;

		static FResult	CreateNode(FMaterialSystem MaterialSystem, EMaterialNodeType NodeType, FMaterialNode& OutMaterialNode);
		static FResult	CreateNode(FMaterialSystem MaterialSystem, EMaterialNodeType NodeType, const FString& NodeName, FMaterialNode& OutMaterialNode);
		static FResult	DeleteNode(FMaterialNode& MaterialNode);

		static FResult	CreateImageNode(RPR::FContext RPRContext, FMaterialSystem MaterialSystem, RPR::FImageManager& ImageManager,
										UTexture2D* Texture, RPR::FImagePtr& OutImage, RPR::FMaterialNode& MaterialNode, RPR::FMaterialNode& OutImageNode);

		static FResult	CreateNormalMap(RPR::FContext RPRContext, FMaterialSystem MaterialSystem, RPR::FImageManager& ImageManager,
										UTexture2D* Texture, RPR::FImagePtr& OutImage, RPR::FMaterialNode& OutMaterialNode, RPR::FMaterialNode& OutImageNode);

		static FResult	CreateBumpMap(RPR::FContext RPRContext, FMaterialSystem MaterialSystem, RPR::FImageManager& ImageManager,
										UTexture2D* Texture, float BumpScale,
										RPR::FImagePtr& OutImage, RPR::FMaterialNode& OutMaterialNode, RPR::FMaterialNode& OutImageNode);

		class FMaterialNode
		{
		public:

			static FResult	SetInputUInt(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, unsigned int Value);
			static FResult	SetInputNode(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, RPR::FMaterialNode InMaterialNode);
			static FResult	SetInputImageData(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, RPR::FImage InImage);

			static FResult	SetInputFloats(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, float x, float y = 0.0f, float z = 0.0f, float w = 0.0f);
			static FResult	SetInputFloats(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, const FVector2D& Value, float z = 0.0f, float w = 0.0f);
			static FResult	SetInputFloats(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, const FVector& Value, float w = 0.0f);
			static FResult	SetInputFloats(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, const FVector4& Value);

			template<typename TEnum>
			static FResult	SetInputEnum(RPR::FMaterialNode MaterialNode, unsigned int ParameterName, TEnum Value)
			{
				static_assert(TIsEnum<TEnum>::Value, "Value must be an enum!");
				return SetInputUInt(MaterialNode, ParameterName, (uint8) Value);
			}

		};

		class FArithmeticNode
		{
		public:

			class FRotationNode
			{
			public:

				static FResult	CreateRotationNode(FMaterialSystem MaterialSystem, const FString& NodeName, FRotationNode& OutRotationNode);

				void SetRotationAngle(float RadAngle);
				void SetInputVector2D(RPR::FMaterialNode MaterialNode);

				RPR::FMaterialNode	GetOutputNode() const;

			private:
				RPR::FMaterialNode OutputNode;
				RPR::FMaterialNode InputVector2DNode;
				RPR::FMaterialNode InputRotationCenter;
				RPR::FMaterialNode InputRotationAngleA;
				RPR::FMaterialNode InputRotationAngleB;
			};

		public:

			static FResult	CreateArithmeticNode(FMaterialSystem MaterialSystem, RPR::EMaterialNodeArithmeticOperation Operation, RPR::FMaterialNode& OutMaterialNode);
			static FResult	CreateArithmeticNode(FMaterialSystem MaterialSystem, RPR::EMaterialNodeArithmeticOperation Operation, const FString& NodeName, RPR::FMaterialNode& OutMaterialNode);

			static FResult	CreateVector2DRotationNode(FMaterialSystem MaterialSystem, const FString& NodeName, FRotationNode& OutRotationNode);

		};

	};


}
