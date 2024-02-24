// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BuffHoverWidget.h"

void UBuffHoverWidget::NativePreConstruct()
{
	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_SkillBG = (UImage*)GetWidgetFromName(TEXT("Image_SkillBG"));
	Image_SkillIcon = (UImage*)GetWidgetFromName(TEXT("Image_SkillIcon"));
	TextBlock_Name = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Name"));
	TextBlock_RemainTurn = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_RemainTurn"));
	RichTextBlock_Description = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_Description"));
}

void UBuffHoverWidget::NativeConstruct()
{
}