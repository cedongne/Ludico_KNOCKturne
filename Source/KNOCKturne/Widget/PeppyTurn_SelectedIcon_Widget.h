// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PeppyTurn_DragVisual_Widget.h"
#include "PeppyTurn_SelectedIcon_Widget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurn_SelectedIcon_Widget : public UUserWidget
{
	GENERATED_BODY()
	void NativeConstruct();
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

protected:
	TArray<UUserWidget*> PeppyTurnWidgetArr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SelectedSkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurnWidget* PeppyTurnWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnDragVisualClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurn_DragVisual_Widget* PeppyTurnDragVisualWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isOverlapped = false;

	UFUNCTION()
	void SwapSkill();

	// 사운드
	UFUNCTION(BlueprintimplementableEvent)
	void HoverSound();
};
