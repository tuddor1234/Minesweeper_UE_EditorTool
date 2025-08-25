#pragma once

DECLARE_DELEGATE_OneParam(NewValueChangedDelegate, int32);

class SMinesweeperSetting : public SHorizontalBox
{
	SLATE_DECLARE_WIDGET(SMinesweeperSetting, SHorizontalBox)
public:

	SLATE_BEGIN_ARGS(SMinesweeperSetting){}
		SLATE_ARGUMENT(FString, LabelText)
		SLATE_ARGUMENT(int32 , InitialValue)
		SLATE_EVENT(NewValueChangedDelegate, OnValueChanged)
	SLATE_END_ARGS();

	void Construct(const FArguments& args);
private:
	NewValueChangedDelegate InternalOnValueChanged;
	TSharedPtr<SEditableText> EditableText;
	int32 InternalValue;
};
