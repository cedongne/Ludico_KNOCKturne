// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PackageSelectedUIWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "CommonSkillHoverWidget.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "PackageWidget.h"
#include "PackageSkillHoverWidget.h"
#include "SpecialSkillHoverWidget.h"
#include "ItemSkillHoverWidget.h"

void UPackageSelectedUIWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_SkillError = (UImage*)GetWidgetFromName(TEXT("Image_SkillError"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Button_Cancel = (UButton*)GetWidgetFromName(TEXT("Button_Cancel"));
}

void UPackageSelectedUIWidget::NativeConstruct() {
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PackageWidgetArr, PackageWidgetClass);
	PackageWidget = (UPackageWidget*)PackageWidgetArr[0];

	if (Button_Cancel) {
		Button_Cancel->OnClicked.AddDynamic(this, &UPackageSelectedUIWidget::ClickCancelBtn);
	}
	if (Button_Background) {
		Button_Background->OnHovered.AddDynamic(this, &UPackageSelectedUIWidget::HoverBackgroundBtn);
	}
}

void UPackageSelectedUIWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds) {
	Super::NativeTick(Geometry, DeltaSeconds);

	if (CurSkillHoverWidget && !IsHovered() && !CurSkillHoverWidget->IsHovered()) {
		CurSkillHoverWidget->RemoveFromParent();
		CurSkillHoverWidget = NULL;
	}
}

void UPackageSelectedUIWidget::SetHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget)
{
	FVector2D SelectedUIPixelPos;
	FVector2D SelectedUIViewportPos;
	USlateBlueprintLibrary::LocalToViewport(CanvasPanel, CanvasPanel->GetCachedGeometry(), FVector2D(0.0, 0.0), SelectedUIPixelPos, SelectedUIViewportPos);

	FVector2D SelectedUISize = CanvasPanel->GetDesiredSize();
	FVector2D HoverWidgetSize = CommonSkillHoverWidget->CanvasPanel->GetDesiredSize();

	FVector2D HoverWidgetPos;
	HoverWidgetPos.X = SelectedUIViewportPos.X + SelectedUISize.X- 1;
	HoverWidgetPos.Y = SelectedUIViewportPos.Y - HoverWidgetSize.Y / 2 + SelectedUISize.Y / 2;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(CommonSkillHoverWidget->CanvasPanel)->SetPosition(HoverWidgetPos);
}

void UPackageSelectedUIWidget::ClickCancelBtn()
{
	switch (SelectedSkillType) {
	case ESelectedSkillType::Skill:
		CancelSelectedSkill();
		break;
	case ESelectedSkillType::Item:
		CancelSelectedItem();
		break;
	}
}

void UPackageSelectedUIWidget::CancelSelectedSkill()
{
	PackageWidget->CancelSkill(Image_Icon->Brush.GetResourceName().ToString());
	if (CurSkillHoverWidget)
		CurSkillHoverWidget->RemoveFromParent();
}

void UPackageSelectedUIWidget::CancelSelectedItem()
{
	PackageWidget->CancelItem(Image_Icon->Brush.GetResourceName().ToString());
	if (CurSkillHoverWidget)
		CurSkillHoverWidget->RemoveFromParent();
}

void UPackageSelectedUIWidget::HoverBackgroundBtn()
{
	if (Image_Background->GetVisibility() == ESlateVisibility::Hidden)
		return;

	if (Image_Icon->GetVisibility() == ESlateVisibility::Visible) {
		switch (SelectedSkillType) {
		case ESelectedSkillType::Skill:
			CreateSkillHoverWidget();
			break;
		case ESelectedSkillType::SpecialSkill:
			CreateSpecialSkillHoverWidget();
			break;
		case ESelectedSkillType::Item:
			CreateItemHoverWidget();
			break;
		}
	}
}

void UPackageSelectedUIWidget::CreateSkillHoverWidget()
{
	int RowNum = BattleManagerSystem->FindSkillRow(Image_Icon->Brush.GetResourceName().ToString());

	class UPackageSkillHoverWidget* SkillCardHoverWidget;
	if (SkillCardHoverWidgetClass) {
		SkillCardHoverWidget = CreateWidget<UPackageSkillHoverWidget>(GetWorld(), SkillCardHoverWidgetClass);
		if (SkillCardHoverWidget) {
			SkillCardHoverWidget->AddToViewport();
			SkillCardHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(SkillCardHoverWidget);
			SkillCardHoverWidget->SetHoverWidgetUI(RowNum, true);
			CurSkillHoverWidget = SkillCardHoverWidget;
		}
	}
}

void UPackageSelectedUIWidget::CreateSpecialSkillHoverWidget()
{
	int RowNum = BattleManagerSystem->FindSpecialtyRow(Image_Icon->Brush.GetResourceName().ToString());

	class USpecialSkillHoverWidget* SpecialSkillHoverWidget;
	if (SpecialSkillCardHoverWidgetClass) {
		SpecialSkillHoverWidget = CreateWidget<USpecialSkillHoverWidget>(GetWorld(), SpecialSkillCardHoverWidgetClass);
		if (SpecialSkillHoverWidget) {
			SpecialSkillHoverWidget->AddToViewport();
			SpecialSkillHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(SpecialSkillHoverWidget);
			SpecialSkillHoverWidget->SetHoverWidgetUI(RowNum, true);
			CurSkillHoverWidget = SpecialSkillHoverWidget;
		}
	}
}

void UPackageSelectedUIWidget::CreateItemHoverWidget()
{
	int RowNum = BattleManagerSystem->FindItemRow(Image_Icon->Brush.GetResourceName().ToString());

	class UItemSkillHoverWidget* ItemSkillHoverWidget;
	if (ItemSkillCardHoverWidgetClass) {
		ItemSkillHoverWidget = CreateWidget<UItemSkillHoverWidget>(GetWorld(), ItemSkillCardHoverWidgetClass);
		if (ItemSkillHoverWidget) {
			ItemSkillHoverWidget->AddToViewport();
			ItemSkillHoverWidget->ForceLayoutPrepass();
			SetHoverWidgetPos(ItemSkillHoverWidget);
			ItemSkillHoverWidget->SetHoverWidgetUI(RowNum, true);
			CurSkillHoverWidget = ItemSkillHoverWidget;
		}
	}
}