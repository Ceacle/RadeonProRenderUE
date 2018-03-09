#pragma once

#include "DeclarativeSyntaxSupport.h"
#include "SCompoundWidget.h"
#include "SUVVisualizer.h"
#include "UVVisualizerEditorSettings.h"
#include "IStructureDetailsView.h"
#include "NotifyHook.h"

class SUVVisualizerEditor : public SCompoundWidget, public FNotifyHook
{
	struct FChannelInfo
	{
		int32	ChannelIndex;
	};

public:

	SLATE_BEGIN_ARGS(SUVVisualizerEditor)
		: _StaticMesh()
	{}

		SLATE_ARGUMENT(TWeakObjectPtr<class UStaticMesh>, StaticMesh)

	SLATE_END_ARGS()

	void	Construct(const FArguments& InArgs);
	void	Refresh();
	void	RefreshUVs();
	
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, UProperty* PropertyThatChanged) override;

private:

	void	SetUVChannelIndex(int32 ChannelIndex);

	void	InitUVVisualizerEditorSettings();

	FText					GetSelectedUVChannel() const;
	void					BuildUVChannelInfos();
	TSharedRef<SWidget>		GenerateUVChannelItem(TSharedPtr<FChannelInfo> ChannelInfo);
	void					OnUVChannelSelected(TSharedPtr<FChannelInfo> ChannelInfo, ESelectInfo::Type SelectInfoType);
	FText					GenerateUVComboBoxText(int32 ChannelIndex) const;

private:

	SUVVisualizerPtr					UVVisualizer;
	TSharedPtr<IStructureDetailsView>	UVVisualizerEditorSettingsView;
	TSharedPtr<FStructOnScope>			UVVisualizerEditorSettingsStructOnScopePtr;

	TWeakObjectPtr<UStaticMesh>	StaticMesh;
	FUVVisualizerEditorSettings	UVVisualizerEditorSettings;

	TSharedPtr<FChannelInfo>			SelectedUVChannel;
	TArray<TSharedPtr<FChannelInfo>>	UVChannels;

};
