// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PeppyTurnSelectedIconWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurnUIWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PeppyTurnSkillCardWidget.h"
#include "GameInstance/BattleManagerSystem.h"
#include "GameInstance/BattleTableManagerSystem.h"

void UPeppyTurnSelectedIconWidget::NativeConstruct()
{
	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
	PeppyTurnWidget = (UPeppyTurnUIWidget*)PeppyTurnWidgetArr[0];
}

void UPeppyTurnSelectedIconWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	isOverlapped = true;
}

void UPeppyTurnSelectedIconWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	isOverlapped = false;
}

FReply UPeppyTurnSelectedIconWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	PeppyTurnWidget->DraggedImgName = this->Image_SelectedSkillIcon->Brush.GetResourceName().ToString();

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UPeppyTurnSelectedIconWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (PeppyTurnDragVisualClass) {
		PeppyTurnDragVisualWidget = CreateWidget<UPeppyTurnDragVisualWidget>(GetWorld(), PeppyTurnDragVisualClass);
	}

	PeppyTurnDragVisualWidget->Image_DragVisual->SetBrush(Image_SelectedSkillIcon->Brush);
	PeppyTurnDragVisualWidget->Image_DragVisual->SetDesiredSizeOverride(FVector2D(50.0, 50.0));

	UDragDropOperation* DragOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	DragOperation->DefaultDragVisual = PeppyTurnDragVisualWidget->Image_DragVisual;
	OutOperation = DragOperation;
}

bool UPeppyTurnSelectedIconWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& DragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, DragDropEvent, InOperation);

	PeppyTurnWidget->OverlappedImgName = Image_SelectedSkillIcon->Brush.GetResourceName().ToString();

	return false;
}

bool UPeppyTurnSelectedIconWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (isOverlapped) {
		SwapSkill();
	}

	return false;
}

void UPeppyTurnSelectedIconWidget::SwapSkill()
{
	int SelectedSkillDraggedSequenceNum = PeppyTurnWidget->IconSequenceRowMap[PeppyTurnWidget->DraggedImgName];
	int SelectedSkillOverlappedSequenceNum = PeppyTurnWidget->IconSequenceRowMap[PeppyTurnWidget->OverlappedImgName];
	int DraggedSkillTableRowNum = BattleManagerSystem->FindSkillRow(PeppyTurnWidget->DraggedImgName);
	int OverlappedSkillTableRowNum = BattleManagerSystem->FindSkillRow(PeppyTurnWidget->OverlappedImgName);

	// 선택한 스킬 칸 아이콘 이미지 변경
	PeppyTurnWidget->SelectedUIListArr[SelectedSkillDraggedSequenceNum - 1]->BP_PeppyTurnIcon->Image_SelectedSkillIcon
		->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[OverlappedSkillTableRowNum]->SkillIcon);
	PeppyTurnWidget->SelectedUIListArr[SelectedSkillOverlappedSequenceNum - 1]->BP_PeppyTurnIcon->Image_SelectedSkillIcon
		->SetBrushFromTexture(BattleTableManagerSystem->PeppySkillTableRows[DraggedSkillTableRowNum]->SkillIcon);

	// 스킬 카드 순서 번호 변경
	int DraggedSkillCardNum = PeppyTurnWidget->IconNameRowMap[PeppyTurnWidget->DraggedImgName];
	int OverlappedSkillCardNum = PeppyTurnWidget->IconNameRowMap[PeppyTurnWidget->OverlappedImgName];

	PeppyTurnWidget->SkillListArr[DraggedSkillCardNum]->TextBlock_Num->SetText(FText::FromString(FString::FromInt(SelectedSkillOverlappedSequenceNum)));
	PeppyTurnWidget->SkillListArr[OverlappedSkillCardNum]->TextBlock_Num->SetText(FText::FromString(FString::FromInt(SelectedSkillDraggedSequenceNum)));

	PeppyTurnWidget->IconSequenceRowMap[PeppyTurnWidget->DraggedImgName];
	PeppyTurnWidget->IconSequenceRowMap[PeppyTurnWidget->OverlappedImgName];
	PeppyTurnWidget->IconSequenceRowMap.Add(PeppyTurnWidget->DraggedImgName, SelectedSkillOverlappedSequenceNum);
	PeppyTurnWidget->IconSequenceRowMap.Add(PeppyTurnWidget->OverlappedImgName, SelectedSkillDraggedSequenceNum);
}