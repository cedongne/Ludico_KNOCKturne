// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PeppyTurnSelectedUIWidget.h"
#include "PeppyTurnUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurnUIWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();

	class UGameInstance* GameInstance;
	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UActorManagerSystem* ActorManagerSystem;
	class ABattleManager* BattleManager;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_selected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_numbering;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnSkillHoverWidgetClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_SelectedSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_EnergyWarning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Skip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Reset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Create_PeppyTurn_UI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PeppyTurnSkillCardWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPeppyTurnSkillCardWidget*> SkillListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SelectedUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPeppyTurnSelectedUIWidget*> SelectedUIListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_BlankSpaceClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> AlertModalClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAlertModalWidget* AlertModalRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalSelectedEnergyCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DraggedImgName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString OverlappedImgName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, int32>IconNameRowMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, int32>IconSequenceRowMap;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPeppyTurnAppearAnim();
	UFUNCTION()
	void CreateSkillList();
	UFUNCTION()
	void SetSkillUI(UPeppyTurnSkillCardWidget* PeppyTurnSkillCardWidget, int RowNum);
	UFUNCTION()
	void CreateSelectedSkillList();
	UFUNCTION()
	void ResetSetting();
	UFUNCTION()
	void ClickAlertModalYes();
	UFUNCTION()
	void ClickAlertModalNo();
	UFUNCTION()
	void AddEnergy(int EnergyCost);
	UFUNCTION()
	void MinusEnergy(int EnergyCost);
	UFUNCTION()
	void SetEnergyWarningText();
	UFUNCTION()
	void ClickSkip();
	UFUNCTION()
	void SetSkillActorList();
	UFUNCTION()
	void ClickAttack();
	UFUNCTION()
	void RemoveAllHoverWidgets();
	/*스킬 선택*/
	UFUNCTION()
	bool SelectSkill(FString IconName);
	UFUNCTION()
	void CancelSkill(FString IconName);
	UFUNCTION()
	void PlayAllSelectedSkillErrorAnim();
};
