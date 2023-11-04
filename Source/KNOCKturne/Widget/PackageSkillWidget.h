// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "GameMode/KNOCKturneGameState.h"
#include "AlertModalWidget.h"
#include "GameInstance/BattleManagerSystem.h"

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

	AKNOCKturneGameState* KNOCKturneGameState;
	class UBattleManagerSystem* BattleManagerSystem;

protected:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_beforeBattle_skill_click;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_beforeBattle_skill_default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_beforeBattle_specialty_click;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_beforeBattle_specialty_default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_beforeBattle_item_click;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_beforeBattle_item_default;

	class UDataTable* PeppySkillTable;
	TArray<FPeppySkillData*> PeppySkillTableRows;
	class UDataTable* SpecialSkillTable;
	TArray<FSpecialSkillData*> SpecialSkillTableRows;
	class UDataTable* ItemTable;
	TArray<FItemData*> ItemTableRows;
	class UDataTable* SkillBuffStringTable;
	TArray<FDialogueString*> SkillBuffStringTableRows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_SelectedSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Specialty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SkillTab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SpecialtyTab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ItemTab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Exit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Reset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* ScrollBox_Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_SettingDone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UPac_SelectedUI_Widget* Selected_Specialty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UPac_SelectedUI_Widget* Selected_Item;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SpecialtyListFormClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpecialtyListFormWidget* SpecialtyListFormRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USpecialtyListFormWidget*> SpecialtyListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemListFormClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemListFormWidget* ItemListFormRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UItemListFormWidget*> ItemListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_BlankSpaceClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* BP_BlankSpaceRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> AlertModalClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAlertModalWidget* AlertModalRef;

	UFUNCTION()
	void CreateSkillList();
	UFUNCTION()
	void CreateSelectedSkillList();
	UFUNCTION()
	void SetSkillUI(USkillListFormWidget* SkillListForm, int idx);
	UFUNCTION()
	void CreateSpecialtyList();
	UFUNCTION()
	void SetSpecialtyUI(USpecialtyListFormWidget* SpecialtyListForm, int idx);
	UFUNCTION()
	void CreateItemList();
	UFUNCTION()
	void SetItemUI(UItemListFormWidget* ItemListForm, int idx);
	UFUNCTION()
	void OnClick_SkillTab();
	UFUNCTION()
	void OnClick_SpecialtyTab();
	UFUNCTION()
	void OnClick_ItemTab();
	UFUNCTION()
	void SkillTabStyle(bool Clicked);
	UFUNCTION()
	void SpecialtyTabStyle(bool Clicked);
	UFUNCTION()
	void ItemTabStyle(bool Clicked);
	UFUNCTION()
	void OnClick_Exit();
	UFUNCTION()
	void OnClick_Reset();
	UFUNCTION()
	void OnClick_SettingDone();
	UFUNCTION()
	void OnClick_AlertModalYes();
	UFUNCTION()
	void OnClick_AlertModalNo();
};
