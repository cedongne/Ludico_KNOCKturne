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
	NTLOG(Warning, TEXT("OnDragEnter"));
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	isOverlapped = true;
	NTLOG(Warning, TEXT("OnDragEnter"));
}

void UPeppyTurn_SelectedIcon_Widget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* WidgetDetectDrag)
{
	Super::NativeOnDragLeave(InDragDropEvent, WidgetDetectDrag);
	isOverlapped = false;
}

FReply UPeppyTurn_SelectedIcon_Widget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Local_Reply = Super::OnMouseButtonDown(InGeometry, InMouseEvent).NativeReply;

	for (int i = 0; i < PeppyTurnWidget->SelectedUIListArr.Num(); i++) {
		if (this == PeppyTurnWidget->SelectedUIListArr[i]->BP_PeppyTurnIcon) {
			draggedIdx = i;
			break;
		}
	}

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, Image_SelectedSkillIcon, EKeys::LeftMouseButton).NativeReply;
}

void UPeppyTurn_SelectedIcon_Widget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	NTLOG(Warning, TEXT("OnDragDetected"));

	if (PeppyTurnDragVisualClass) {
		PeppyTurnDragVisualWidget = CreateWidget<UPeppyTurn_DragVisual_Widget>(GetWorld(), PeppyTurnDragVisualClass);
		if (PeppyTurnDragVisualWidget) {
			PeppyTurnDragVisualWidget->AddToViewport();
		}
	}

	PeppyTurnDragVisualWidget->Image_DragVisual->SetBrush(Image_SelectedSkillIcon->Brush);
	PeppyTurnDragVisualWidget->Image_DragVisual = Image_SelectedSkillIcon;
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
			overlappedIdx = i;
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
	else {

	}

	return false;
}

void UPeppyTurn_SelectedIcon_Widget::SwapSkill()
{
	// 선택한 스킬 순서 변경
	UTexture2D* DraggedImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush);
	UTexture2D* OverlappedImg = UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SelectedUIListArr[overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->Brush);
	PeppyTurnWidget->SelectedUIListArr[draggedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(OverlappedImg);
	PeppyTurnWidget->SelectedUIListArr[overlappedIdx]->BP_PeppyTurnIcon->Image_SelectedSkillIcon->SetBrushFromTexture(DraggedImg);

	// 스킬 리스트 번호 변경
	for (int i = 0; i < PeppyTurnWidget->SkillListArr.Num(); i++) {
		int breakNum = 0;

		if (UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush) == DraggedImg
			|| UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(PeppyTurnWidget->SkillListArr[i]->Image_Icon->Brush) == OverlappedImg) {
			PeppyTurnWidget->SkillListArr[i]->TextBlock_Num->SetText(PeppyTurnWidget->SelectedUIListArr[i]->TextBlock_SelectNum->GetText());
			breakNum++;
		}

		if (breakNum == 2) {
			break;
		}
	}
}
