// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageTextWidget.h"

void UDamageTextWidget::NativePreConstruct()
{
	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	TextBlock_Damage = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Damage"));
}

void UDamageTextWidget::PlayDamgeTextUpAnim()
{
	PlayAnimation(DamageTextUp);
}
