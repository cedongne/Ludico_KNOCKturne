// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "GameMode/KNOCKturneGameState.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "AlertModalWidget.h"
#include "GameInstance/BattleManagerSystem.h"
#include <GameInstance/BattleTableManagerSystem.h>

#include "PeppyTurnWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPeppyTurnWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPeppyTurnWidget(const FObjectInitializer& ObjectInitializer);
	void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	class UBattleManagerSystem* BattleManagerSystem;

protected:
	class UActorManagerSystem* ActorManagerSystem;
	class ABattleManager* BattleManager;

public:
	class UDataTable* PeppySkillTable;
	TArray<FPeppySkillData*> PeppySkillTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillListFormClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkillListFormWidget* SkillListFormRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USkillListFormWidget*> SkillListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SelectedUIClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPeppyTurn_SelectedUI_Widget* SelectedUIRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPeppyTurn_SelectedUI_Widget*> SelectedUIListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_BlankSpaceClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* BP_BlankSpaceRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> AlertModalClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAlertModalWidget* AlertModalRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TotalSelectedEnergyCost = 0;

	UFUNCTION()
	void CreateSkillList();
	UFUNCTION()
	void SetSkillUI(USkillListFormWidget* SkillListForm, int idx);
	UFUNCTION()
	void CreateSelectedSkillList();
	UFUNCTION()
	void OnClick_Reset();
	UFUNCTION()
	void OnClick_AlertModalYes();
	UFUNCTION()
	void OnClick_AlertModalNo();
	UFUNCTION()
	void AddEnergy(int EnergyCost);
	UFUNCTION()
	void MinusEnergy(int EnergyCost);
	UFUNCTION()
	void SetEnergyWarningText();
	UFUNCTION()
	void OnClick_Skip();
	UFUNCTION()
	void SetSkillActorList();
	UFUNCTION()
	void OnClick_Attack();
};
