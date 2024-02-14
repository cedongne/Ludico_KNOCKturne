// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PeppyTurnDragVisualWidget.h"
#include "PeppyTurnSelectedIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurnSelectedIconWidget : public UUserWidget
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
	class UPeppyTurnUIWidget* PeppyTurnWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnDragVisualClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurnDragVisualWidget* PeppyTurnDragVisualWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isOverlapped = false;

	UFUNCTION()
	void SwapSkill();

	// 사운드
	UFUNCTION(BlueprintimplementableEvent)
	void HoverSound();
};
