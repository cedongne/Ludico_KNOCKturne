// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionPopupWidget.h"

void UInteractionPopupWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	Image_interaction = (UImage*)GetWidgetFromName(TEXT("Image_interaction"));
	
}