// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnterBattleAlertModalWidget.h"

void UEnterBattleAlertModalWidget::NativePreConstruct() {
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_AlertIcon = (UImage*)GetWidgetFromName(TEXT("Image_AlertIcon"));
	TextBlock_Enter = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Enter"));
	TextBlock_Warning = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Warning"));
	Button_Yes = (UButton*)GetWidgetFromName(TEXT("Button_Yes"));
	Button_No = (UButton*)GetWidgetFromName(TEXT("Button_No"));
}

void UEnterBattleAlertModalWidget::NativeConstruct() {

}