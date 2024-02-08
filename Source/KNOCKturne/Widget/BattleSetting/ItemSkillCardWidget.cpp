// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/ItemSkillCardWidget.h"
#include "ItemSkillHoverWidget.h"

void UItemSkillCardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_Count = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Count"));
}

void UItemSkillCardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Background) {
		Button_Background->OnHovered.AddDynamic(this, &UItemSkillCardWidget::CreateSkillHoverWidget);
	}
}

int32 UItemSkillCardWidget::GetCardSkillRowNum()
{
	return BattleManagerSystem->FindItemRow(Image_Icon->Brush.GetResourceName().ToString());
}

void UItemSkillCardWidget::CreateSkillHoverWidget()
{
	bool isSelected;
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox")
		isSelected = false;
	else
		isSelected = true;

	class UItemSkillHoverWidget* ItemSkillHoverWidget;
	if (ItemSkillCardHoverWidgetClass) {
		ItemSkillHoverWidget = CreateWidget<UItemSkillHoverWidget>(GetWorld(), ItemSkillCardHoverWidgetClass);
		if (ItemSkillHoverWidget) {
			ItemSkillHoverWidget->AddToViewport();
			ItemSkillHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(ItemSkillHoverWidget);
			ItemSkillHoverWidget->SetHoverWidgetUI(GetCardSkillRowNum(), isSelected);
		}
	}
}