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
#include "UVProjectionMappingEditor/Algorithms/UVProjectionAlgorithmBase.h"
#include "MaterialEditor/DEditorParameterValue.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "MaterialEditor/MaterialEditorInstanceConstant.h"
#include "Materials/MaterialInstanceConstant.h"
#include "MaterialEditHelper.h"

DECLARE_STATS_GROUP(TEXT("FUVProjectionTriPlanarAlgo"), STATGROUP_UVProjection_TriPlanarAlgo, STATCAT_Advanced)

class FUVProjectionTriPlanarAlgo : public FUVProjectionAlgorithmBase, public FGCObject
{
public:
	struct FSettings
	{
		FSettings();

		bool bApply;
		float Scale;
		float Angle;
	};
	

public:
	FUVProjectionTriPlanarAlgo();

	void SetSettings(const FSettings& InSettings);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual void StartAlgorithm() override;
	virtual void Finalize() override {}

private:

	void								SetMaterialParameterByMeshSection(UStaticMesh* StaticMesh, int32 SectionIndex);
	UMaterialEditorInstanceConstant*	CreateMaterialEditorInstanceConstant() const;
	TMap<FName, FMaterialParameterBrowseDelegate>	CreateEditMaterialParametersRouter() const;

	void	EditMaterialParameter_TriPlanar_TextureScale(UDEditorParameterValue* ParameterValue);
	void	EditMaterialParameter_TriPlanar_TextureAngle(UDEditorParameterValue* ParameterValue);

private:

	UMaterialEditorInstanceConstant*		MaterialEditorInstance;

	FSettings	Settings;
	
private:

	static const FName	MaterialParameterName_UseTriPlanar;
	static const FName	MaterialParameterName_TriPlanar_TextureScale;
	static const FName	MaterialParameterName_TriPlanar_TextureAngle;
};

typedef TSharedPtr<FUVProjectionTriPlanarAlgo>	FUVProjectionTriPlanarAlgoPtr;
