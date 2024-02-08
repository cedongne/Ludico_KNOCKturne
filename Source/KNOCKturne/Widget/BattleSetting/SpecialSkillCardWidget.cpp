// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/SpecialSkillCardWidget.h"
#include "SpecialSkillHoverWidget.h"

void USpecialSkillCardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
}

void USpecialSkillCardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Background) {
		Button_Background->OnHovered.AddDynamic(this, &USpecialSkillCardWidget::CreateSkillHoverWidget);
	}
}

int32 USpecialSkillCardWidget::GetCardSkillRowNum()
{
	return BattleManagerSystem->FindSpecialtyRow(Image_Icon->Brush.GetResourceName().ToString());
}

void USpecialSkillCardWidget::CreateSkillHoverWidget()
{
	bool isSelected;
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox")
		isSelected = false;
	else
		isSelected = true;

	class USpecialSkillHoverWidget* SpecialSkillHoverWidget;
	if (SpecialSkillCardHoverWidgetClass) {
		SpecialSkillHoverWidget = CreateWidget<USpecialSkillHoverWidget>(GetWorld(), SpecialSkillCardHoverWidgetClass);
		if (SpecialSkillHoverWidget) {
			SpecialSkillHoverWidget->AddToViewport();
			SpecialSkillHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(SpecialSkillHoverWidget);
			SpecialSkillHoverWidget->SetHoverWidgetUI(GetCardSkillRowNum(), isSelected);
		}
	}
}
