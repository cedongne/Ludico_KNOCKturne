// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "PackageSkillWidget.generated.h"

/**
 *
 */
UCLASS()
class KNOCKTURNE_API UPackageSkillWidget : public UUserWidget
{
	GENERATED_BODY()

	UPackageSkillWidget(const FObjectInitializer& ObjectInitializer);
	void NativePreConstruct();
	void NativeConstruct();

protected:

public:
	class UDataTable* PeppySkillTable;
	TArray<FPeppySkillData*> PeppySkillTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_SelectedSkill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillListFormClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkillListFormWidget* SkillListFormRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USkillListFormWidget*> SkillListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SelectedUIClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPac_SelectedUI_Widget* SelectedUIRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPac_SelectedUI_Widget*> SelectedUIListArr;

	UFUNCTION()
	void CreateSkillList();
	UFUNCTION()
	void CreateSelectedSkillList();
	UFUNCTION()
	void SetSkillUI(USkillListFormWidget* SkillListForm, int idx);
};
