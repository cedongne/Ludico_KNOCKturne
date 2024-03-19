// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HUDItemHoverWidget.h"

void UHUDItemHoverWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_SkillBG = (UImage*)GetWidgetFromName(TEXT("Image_SkillBG"));
	Image_SkillIcon = (UImage*)GetWidgetFromName(TEXT("Image_SkillIcon"));
	TextBlock_Name = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Name"));
	RichTextBlock_Description = (URichTextBlock*)GetWidgetFromName(TEXT("RichTextBlock_Description"));
}

void UHUDItemHoverWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

}
