// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PeppyTurnSelectedUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurnSelectedUIWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

	class UBattleManagerSystem* BattleManagerSystem;

protected:
	TArray<UUserWidget*> PeppyTurnWidgetArr;
	class UCommonSkillHoverWidget* CurSkillHoverWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_Background;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UPeppyTurnSelectedIconWidget* BP_PeppyTurnIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_NumBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SkillError;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_SelectNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Cancel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* PeppyTurn_SkillError;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurnUIWidget* PeppyTurnWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillCardHoverWidgetClass;

	UFUNCTION(BlueprintimplementableEvent)
	void PlaySkillErrorAnim();
	UFUNCTION()
	void SetHoverWidgetPos(UCommonSkillHoverWidget* CommonSkillHoverWidget);
	UFUNCTION()
	void CancelSelectedSkill();
	UFUNCTION()
	void CreateSkillHoverWidget();
};
