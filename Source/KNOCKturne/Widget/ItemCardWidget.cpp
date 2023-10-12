// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemCardWidget.h"

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
	if (Button_Background) {
		Button_Background->OnClicked.AddDynamic(this, &UItemCardWidget::Button_BackgroundOnClicked);
	}
}

void UItemCardWidget::Button_BackgroundOnClicked() {

}