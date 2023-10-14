// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/AlertModalWidget.h"

void UAlertModalWidget::NativePreConstruct() {
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_AlertIcon = (UImage*)GetWidgetFromName(TEXT("Image_AlertIcon"));
	TextBlock_Skip = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Skip"));
	TextBlock_ItemName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_ItemName"));
	TextBlock_SelectOrNot = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SelectOrNot"));
	Button_Yes = (UButton*)GetWidgetFromName(TEXT("Button_Yes"));
	Button_No = (UButton*)GetWidgetFromName(TEXT("Button_No"));
}

void UAlertModalWidget::NativeConstruct() {
	
}