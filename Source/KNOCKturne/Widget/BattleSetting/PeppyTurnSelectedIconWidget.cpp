// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PeppyTurnSelectedIconWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurnUIWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PeppyTurnSkillCardWidget.h"

void UPeppyTurnSelectedIconWidget::NativeConstruct()
{
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

	for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
		if (this->Image_SelectedSkillIcon->Brush.GetResourceName() ==
			PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName()) {
			PeppyTurnWidget->draggedIdx = i;
			break;
		}
	}

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

	for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
		if (this == PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon) {
			PeppyTurnWidget->overlappedIdx = i;
			break;
		}
	}

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
	// 선택한 스킬 순서 변경
	UTexture2D* DraggedImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush);
	UTexture2D* OverlappedImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush);
	int draggedSkillListNum = PeppyTurnWidget->IconNameRowMap[PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString()];
	int overlappedSkillListNum = PeppyTurnWidget->IconNameRowMap[PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString()];

	PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(OverlappedImg);
	PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(DraggedImg);

	FText draggedSelectNum = PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->TextBlock_SelectNum->GetText();
	FText overlappedSelectNum = PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->TextBlock_SelectNum->GetText();
	PeppyTurnWidget->IconSequenceRowMap.Remove(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString());
	PeppyTurnWidget->IconSequenceRowMap.Remove(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString());
	PeppyTurnWidget->IconSequenceRowMap.Add(
		PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString(), PeppyTurnWidget->overlappedIdx + 1);
	PeppyTurnWidget->IconSequenceRowMap.Add(
		PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString(), PeppyTurnWidget->draggedIdx + 1);

	PeppyTurnWidget->SkillListArr[draggedSkillListNum]->TextBlock_Num->SetText(overlappedSelectNum);
	NTLOG(Error, TEXT("draggedSkillListNum %d"), draggedSkillListNum);
	PeppyTurnWidget->SkillListArr[overlappedSkillListNum]->TextBlock_Num->SetText(draggedSelectNum);
	NTLOG(Error, TEXT("overlappedSkillListNum %d"), overlappedSkillListNum);
	PeppyTurnWidget->IconNameRowMap.Remove(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString());
	PeppyTurnWidget->IconNameRowMap.Remove(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush.GetResourceName().ToString());
	PeppyTurnWidget->IconNameRowMap.Add(
		PeppyTurnWidget->SkillListArr[draggedSkillListNum]->Image_Icon->Brush.GetResourceName().ToString(), 
		FCString::Atof(*(PeppyTurnWidget->SkillListArr[draggedSkillListNum]->TextBlock_Num->GetText().ToString())));
	PeppyTurnWidget->IconNameRowMap.Add(
		PeppyTurnWidget->SkillListArr[overlappedSkillListNum]->Image_Icon->Brush.GetResourceName().ToString(),
		FCString::Atof(*(PeppyTurnWidget->SkillListArr[overlappedSkillListNum]->TextBlock_Num->GetText().ToString())));
}