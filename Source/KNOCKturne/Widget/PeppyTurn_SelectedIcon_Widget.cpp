// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PeppyTurn_SelectedIcon_Widget.h"
#include "PeppyTurnWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "PeppyTurn_SelectedUI_Widget.h"
#include "SkillListFormWidget.h"

#include <Blueprint/WidgetLayoutLibrary.h>
#include "Components/CanvasPanelSlot.h"

void UPeppyTurn_SelectedIcon_Widget::NativeConstruct()
{
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, PeppyTurnWidgetArr, PeppyTurnWidgetClass);
	PeppyTurnWidget = (UPeppyTurnWidget*)PeppyTurnWidgetArr[0];
}

void UPeppyTurn_SelectedIcon_Widget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	isOverlapped = true;
}

void UPeppyTurn_SelectedIcon_Widget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	isOverlapped = false;
}

FReply UPeppyTurn_SelectedIcon_Widget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UPeppyTurn_SelectedIcon_Widget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (PeppyTurnDragVisualClass) {
		PeppyTurnDragVisualWidget = CreateWidget<UPeppyTurn_DragVisual_Widget>(GetWorld(), PeppyTurnDragVisualClass);
	}

	PeppyTurnDragVisualWidget->Image_DragVisual->SetBrush(Image_SelectedSkillIcon->Brush);
	PeppyTurnDragVisualWidget->Image_DragVisual->SetDesiredSizeOverride(FVector2D(50.0, 50.0));

	UDragDropOperation* DragOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	DragOperation->DefaultDragVisual = PeppyTurnDragVisualWidget->Image_DragVisual;
	OutOperation = DragOperation;
}

bool UPeppyTurn_SelectedIcon_Widget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& DragDropEvent, UDragDropOperation* InOperation)
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

bool UPeppyTurn_SelectedIcon_Widget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (isOverlapped) {
		SwapSkill();
	}

	return false;
}

void UPeppyTurn_SelectedIcon_Widget::SwapSkill()
{
	// 선택한 스킬 순서 변경
	UTexture2D* DraggedImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush);
	UTexture2D* OverlappedImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush);
	PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(OverlappedImg);
	PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(DraggedImg);
	FText draggedSelectNum = PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->draggedIdx]->TextBlock_SelectNum->GetText();
	FText overlappedSelectNum = PeppyTurnWidget->SelectedUIListArr[PeppyTurnWidget->overlappedIdx]->TextBlock_SelectNum->GetText();

	// 스킬 리스트 번호 변경
	for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
		int breakNum = 0;

		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush) == DraggedImg) {
			PeppyTurnWidget->SkillListArr[i]->TextBlock_Num->SetText(overlappedSelectNum);
			breakNum++;
		}
		else if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush) == OverlappedImg) {
			PeppyTurnWidget->SkillListArr[i]->TextBlock_Num->SetText(draggedSelectNum);
			breakNum++;
		}

		if (breakNum == 2) {
			break;
		}
	}
}
