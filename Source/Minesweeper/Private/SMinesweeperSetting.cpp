#include "SMinesweeperSetting.h"


SLATE_IMPLEMENT_WIDGET(SMinesweeperSetting)
	void SMinesweeperSetting::PrivateRegisterAttributes(FSlateAttributeInitializer& AttributeInitializer) {}

void SMinesweeperSetting::Construct(const FArguments& Args)
{
	InternalValue = Args._InitialValue;
	InternalOnValueChanged = Args._OnValueChanged;

	// add label 
	AddSlot()
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.Padding(5)
	.AutoWidth() 
	[
		SNew(SBox).WidthOverride(100)
		[
			SNew(STextBlock).Text(FText::FromString(Args._LabelText))
		]
	];

	// Helper lambda function 
	auto IntToFText = [=](int32 Value)
	{
		return FText::FromString(FString::FromInt(Value));
	};

	AddSlot()
	.FillWidth(1)
	[
		SNew(SBorder).ColorAndOpacity(FColor::Silver)
		[
			SAssignNew(EditableText, SEditableText)
			.ColorAndOpacity(FColor::White)
			.Text(IntToFText(InternalValue))
			.OnTextCommitted_Lambda([this, IntToFText](const FText& Text, ETextCommit::Type CommitType)
			{
				// If we don't have a number, we reset 
				if (!Text.IsNumeric())
				{
					EditableText->SetText(IntToFText(InternalValue));
					return;
				}
				
				int32 intVal = FCString::Atoi(*Text.ToString());
				float floatVal = FCString::Atof(*Text.ToString());
				
				// If it's floating point or negative, we reset
				if (intVal != floatVal || intVal < 1)
				{
					EditableText->SetText(IntToFText(InternalValue));
					return;
				}

				// Success
				InternalValue = intVal;
				InternalOnValueChanged.ExecuteIfBound(InternalValue);
			})
		]
	];
}
