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
#include "RPRMaterialBoolPropertiesLayout.h"
#include "DetailWidgetRow.h"
#include "SCheckBox.h"

TSharedRef<IPropertyTypeCustomization> FRPRMaterialBoolPropertiesLayout::MakeInstance()
{
	return (MakeShareable(new FRPRMaterialBoolPropertiesLayout()));
}

TSharedRef<SWidget> FRPRMaterialBoolPropertiesLayout::GetPropertyValueRowWidget()
{
	return
		SNew(SCheckBox)
		.OnCheckStateChanged(this, &FRPRMaterialBoolPropertiesLayout::OnCheckStateChanged)
		.IsChecked(this, &FRPRMaterialBoolPropertiesLayout::IsChecked);
}

void FRPRMaterialBoolPropertiesLayout::OnCheckStateChanged(ECheckBoxState CheckboxState)
{
	TArray<UObject*> objects;
	CurrentPropertyHandle->GetOuterObjects(objects);

	for (int32 i = 0; i < objects.Num(); ++i)
	{
		SetBoolValue(CheckboxState == ECheckBoxState::Checked);
	}
}

ECheckBoxState FRPRMaterialBoolPropertiesLayout::IsChecked() const
{
	TArray<UObject*> objects;
	CurrentPropertyHandle->GetOuterObjects(objects);

	bool bIsInitialized = false;
	bool bIsChecked = false;

	for (int32 i = 0; i < objects.Num(); ++i)
	{
		bool parameterBoolValue = GetBoolValue();
		if (!bIsInitialized)
		{
			bIsInitialized = true;
			bIsChecked = parameterBoolValue;
		}
		else if (parameterBoolValue != bIsChecked)
		{
			return (ECheckBoxState::Undetermined);
		}
	}

	return (bIsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

bool FRPRMaterialBoolPropertiesLayout::GetBoolValue() const
{
	bool value;
	GetIsEnabledPropertyHandle()->GetValue(value);
	return (value);
}

void FRPRMaterialBoolPropertiesLayout::SetBoolValue(bool Value)
{
	GetIsEnabledPropertyHandle()->SetValue(Value);
}

TSharedPtr<IPropertyHandle> FRPRMaterialBoolPropertiesLayout::GetIsEnabledPropertyHandle() const
{
	return (CurrentPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FRPRMaterialBool, bIsEnabled)));
}
