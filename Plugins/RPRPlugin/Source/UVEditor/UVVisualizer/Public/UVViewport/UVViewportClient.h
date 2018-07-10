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
#include "EditorViewportClient.h"
#include "Templates/SharedPointer.h"
#include "PreviewScene.h"
#include "UnrealWidget.h"
#include "Editor.h"
#include "Framework/Commands/UICommandList.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UVViewport/UVMeshComponent.h"

DECLARE_DELEGATE(FOnUVChanged)

class FUVViewportClient : public FEditorViewportClient
{
public:

	FUVViewportClient(const TWeakPtr<SEditorViewport>& InUVViewport);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;
	virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;
	virtual void TrackingStopped() override;
	virtual bool InputWidgetDelta(FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override;

	virtual bool ShouldOrbitCamera() const override;
	void	RefreshUV();
	void	ClearUVTransform();
	void	ApplyUVTransform();

	void	SetBackgroundImage(UTexture2D* BackgroundImage);
	void	SetBackgroundOpacity(float Opacity);

	virtual FWidget::EWidgetMode GetWidgetMode() const override;
	virtual FVector GetWidgetLocation() const override;
	virtual ECoordSystem GetWidgetCoordSystemSpace() const override;
	virtual FMatrix GetWidgetCoordSystem() const override;

private:

	void	SetupUV();
	void	SetupCameraView();
	void	SetupBackground();
	void	SetupUVMesh();

	void	SelectUVMeshComponent(bool bSelect);

	TSharedPtr<class SUVViewport> GetUVViewport() const;
	FVector		ConvertUVto3DPreview(const FVector2D& UV) const;
	FVector2D	Convert3DPreviewtoUV(const FVector& In3D) const;
	bool		IsUVMeshSelected() const;

	TArray<FVector2D>&	GetRawMeshUV(int32 MeshIndex);
	const TArray<FVector2D>& GetRawMeshUV(int32 MeshIndex) const;

	void		ApplyTranslationPreview(const FVector& Drag);
	void		ApplyRotationPreview(const FRotator& Rotation);
	void		ApplyScalePreview(const FVector& Scale);
	void		PostTransformChanges();

	bool		EndTranslation();
	bool		EndRotation();
	bool		EndScale();
	void		EndTransform(const FTransform& DeltaTransform);

	FTransform	GetNewUVTransformFromPreview(bool bKeepPivotPoint = false) const;

private:

	FPreviewScene OwnedPreviewScene;
	FTransform SceneTransform;
	FVector2D Barycenter;
	FVector InitialUVMeshOffset;

	FMatrix UVTransformMatrix;

	UUVMeshComponent* UVMeshComponent;
	UStaticMeshComponent* BackgroundMeshComponent;
	UMaterialInstanceDynamic* BackgroundMeshMID;
	
	bool bIsManipulating;
	bool bHasUVTransformNotCommitted;
	FVector WidgetLocation;
};

typedef TSharedPtr<FUVViewportClient> FUVViewportClientPtr;
