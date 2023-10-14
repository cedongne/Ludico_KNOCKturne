// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemCardWidget.h"
#include "KNOCKturne.h"
#include "DreamFragmentWidget.h"

void UItemCardWidget::NativePreConstruct() {
	Image_SubBackground = (UImage*)GetWidgetFromName(TEXT("Image_SubBackground"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	TextBlock_Name = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Name"));
	RichTextBlock_Description = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_Description"));
	TextBlock_Easteregg = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Easteregg"));
	RichTextBlock_EastereggCharacter = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_EastereggCharacter"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
}

void UItemCardWidget::NativeConstruct() {
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, DreamFragmentWidgetArr, DreamFragmentWidgetClass);
	DreamFragmentWidget = (UDreamFragmentWidget*)DreamFragmentWidgetArr[0];

	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &UItemCardWidget::Button_BackgroundOnClicked);
	}
}

void UItemCardWidget::Button_BackgroundOnClicked() {
	for (int i = 0; i < DreamFragmentWidget->ItemCardArr.Num(); i++) {
		if (DreamFragmentWidget->ItemCardArr[i]->Button_Background == this->Button_Background) {
			DreamFragmentWidget->ItemCardArr[i]->Image_SubBackground->SetBrushFromTexture(UI_DreamFragments_SubBackground_Selected);
		}
		else {
			DreamFragmentWidget->ItemCardArr[i]->Image_SubBackground->SetBrushFromTexture(UI_DreamFragments_SubBackground);
		}
	}

	if (!DreamFragmentWidget->Button_Select->GetIsEnabled()) {
		DreamFragmentWidget->Button_Select->SetIsEnabled(true);
	}
}