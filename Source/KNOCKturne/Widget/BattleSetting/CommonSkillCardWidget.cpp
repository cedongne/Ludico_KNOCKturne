// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/CommonSkillCardWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include "CommonSkillHoverWidget.h"

void UCommonSkillCardWidget::NativePreConstruct() {
	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_CheckBox = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_IconBackground = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground"));
	TextBlock_SkillName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName"));
}

void UCommonSkillCardWidget::NativeConstruct() {
	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
}

int32 UCommonSkillCardWidget::GetCardSkillRow()
{
	NTLOG(Error, TEXT("Override the (GetCardSkillRow) function!"));
	return 0;
}

void UCommonSkillCardWidget::CreateSkillHoverWidget()
{
	NTLOG(Error, TEXT("Override the (CreateHoverWidget) function!"));

	/*UCommonSkillHoverWidget* CommonSkillHoverWidget;
	if (CommonSkillHoverClass) {
		CommonSkillHoverWidget = CreateWidget<UCommonSkillHoverWidget>(GetWorld(), CommonSkillHoverClass);
		if (CommonSkillHoverWidget) {
			CommonSkillHoverWidget->AddToViewport();
		}
	}

	CommonSkillHoverWidget->ForceLayoutPrepass();
	SetHoverWidgetPos(CommonSkillHoverWidget);
	CommonSkillHoverWidget->SetHoverWidgetUI(GetCardSkillRow());*/
}

void UCommonSkillCardWidget::SetHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget)
{
	FVector2D SkillCardPixelPos;
	FVector2D SkillCardViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), SkillCardPixelPos, SkillCardViewportPos);

	FVector2D SkillCardSize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = CommonSkillHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = SkillCardViewportPos.X;
	HoverWidgetPos.Y = SkillCardViewportPos.Y - HoverWidgetSize.Y / 2 + SkillCardSize.Y / 2;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(CommonSkillHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}