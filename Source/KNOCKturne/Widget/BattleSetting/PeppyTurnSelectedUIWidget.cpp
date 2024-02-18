// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PeppyTurnSelectedUIWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurnUIWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "CommonSkillHoverWidget.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include "PeppyTurnSelectedIconWidget.h"
#include "PeppyTurnSkillHoverWidget.h"

void UPeppyTurnSelectedUIWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	BP_PeppyTurnIcon = (UPeppyTurnSelectedIconWidget*)GetWidgetFromName(TEXT("BP_PeppyTurnIcon"));
	Image_SkillError = (UImage*)GetWidgetFromName(TEXT("Image_SkillError"));
	TextBlock_SelectNum = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SelectNum"));
	Button_Cancel = (UButton*)GetWidgetFromName(TEXT("Button_Cancel"));
}

void UPeppyTurnSelectedUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
	PeppyTurnWidget = (UPeppyTurnUIWidget*)PeppyTurnWidgetArr[0];

	if (Button_Cancel) {
		Button_Cancel->OnClicked.AddDynamic(this, &UPeppyTurnSelectedUIWidget::CancelSelectedSkill);
	}
}

void UPeppyTurnSelectedUIWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds) {
	Super::NativeTick(Geometry, DeltaSeconds);

	if (CurSkillHoverWidget == NULL && BP_PeppyTurnIcon->IsHovered()) {
		CreateSkillHoverWidget();
	}

	if (CurSkillHoverWidget && !IsHovered() && !CurSkillHoverWidget->IsHovered()) {
		CurSkillHoverWidget->RemoveFromParent();
		CurSkillHoverWidget = NULL;
	}
}

void UPeppyTurnSelectedUIWidget::SetHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget)
{
	FVector2D SelectedUIPixelPos;
	FVector2D SelectedUIViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), SelectedUIPixelPos, SelectedUIViewportPos);

	FVector2D SelectedUISize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = CommonSkillHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = SelectedUIViewportPos.X + SelectedUISize.X / 2 - HoverWidgetSize.X / 2;
	HoverWidgetPos.Y = SelectedUIViewportPos.Y + SelectedUISize.Y - 5;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(CommonSkillHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}

void UPeppyTurnSelectedUIWidget::CancelSelectedSkill()
{
	PeppyTurnWidget->CancelSkill(BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString());
	if (CurSkillHoverWidget)
		CurSkillHoverWidget->RemoveFromParent();
}

void UPeppyTurnSelectedUIWidget::CreateSkillHoverWidget()
{
	if (BP_PeppyTurnIcon->GetVisibility() == ESlateVisibility::Hidden)
		return;

	int RowNum = BattleManagerSystem->FindSkillRow(BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString());

	class UPeppyTurnSkillHoverWidget* SkillCardHoverWidget;
	if (SkillCardHoverWidgetClass) {
		SkillCardHoverWidget = CreateWidget<UPeppyTurnSkillHoverWidget>(GetWorld(), SkillCardHoverWidgetClass);
		if (SkillCardHoverWidget) {
			SkillCardHoverWidget->AddToViewport();
			SkillCardHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(SkillCardHoverWidget);
			SkillCardHoverWidget->SetHoverWidgetUI(RowNum, true);
			CurSkillHoverWidget = SkillCardHoverWidget;
		}
	}
}