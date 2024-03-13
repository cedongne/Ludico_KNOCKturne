// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SaveAlertModalWidget.h"

void USaveAlertModalWidget::NativePreConstruct() {


	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	TextBlock_Question = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Question"));
	TextBlock_Warning = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Warning"));
	Button_Yes = (UButton*)GetWidgetFromName(TEXT("Button_Yes"));
	Button_No = (UButton*)GetWidgetFromName(TEXT("Button_No"));
}

void USaveAlertModalWidget::NativeConstruct() {

}