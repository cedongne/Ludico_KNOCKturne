// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PeppyTurnSkillCardWidget.h"
#include "PeppyTurnSkillHoverWidget.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include <Blueprint/WidgetLayoutLibrary.h>

void UPeppyTurnSkillCardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_Stance = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Stance"));
	TextBlock_Num = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Num"));
}

void UPeppyTurnSkillCardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Background) {
		Button_Background->OnHovered.AddDynamic(this, &UPeppyTurnSkillCardWidget::CreateSkillHoverWidget);
	}
}

int32 UPeppyTurnSkillCardWidget::GetCardSkillRowNum()
{
	return BattleManagerSystem->FindSkillRow(Image_Icon->Brush.GetResourceName().ToString());
}

void UPeppyTurnSkillCardWidget::CreateSkillHoverWidget()
{
	bool isSelected;
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox")
		isSelected = false;
	else
		isSelected = true;

	class UPeppyTurnSkillHoverWidget* SkillCardHoverWidget;
	if (SkillCardHoverWidgetClass) {
		SkillCardHoverWidget = CreateWidget<UPeppyTurnSkillHoverWidget>(GetWorld(), SkillCardHoverWidgetClass);
		if (SkillCardHoverWidget) {
			SkillCardHoverWidget->AddToViewport();
			SkillCardHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(SkillCardHoverWidget);
			SkillCardHoverWidget->SetHoverWidgetUI(GetCardSkillRowNum(), isSelected);
		}
	}
}

void UPeppyTurnSkillCardWidget::SetPeppySkillHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget)
{
	FVector2D SkillCardPixelPos;
	FVector2D SkillCardViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), SkillCardPixelPos, SkillCardViewportPos);

	FVector2D SkillCardSize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = CommonSkillHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = SkillCardViewportPos.X;
	HoverWidgetPos.Y = SkillCardViewportPos.Y + HoverWidgetSize.Y / 2 - SkillCardSize.Y / 2;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(CommonSkillHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}
