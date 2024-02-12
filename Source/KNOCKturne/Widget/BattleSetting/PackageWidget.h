// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackageWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPackageWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();

	class UGameInstance* GameInstance;
	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	AKNOCKturneGameState* KNOCKturneGameState;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox_selected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, int32> SelectedSkillIconRowMap;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Skill;
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
	class UUniformGridPanel* UniformGridPanel_SelectedSkill;
	
	class UPackageSelectedUIWidget* Selected_Specialty;
	class UPackageSelectedUIWidget* Selected_Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PackageSkillCardWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPackageSkillCardWidget*> SkillListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SpecialSkillCardWigetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USpecialSkillCardWidget*> SpecialtyListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> ItemSkillCardWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UItemSkillCardWidget*> ItemListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SelectedUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UPackageSelectedUIWidget*> SelectedUIListArr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_BlankSpaceClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> AlertModalClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAlertModalWidget* AlertModalRef;

	UFUNCTION()
	void CreateSkillList();
	UFUNCTION()
	void SetSkillUI(UPackageSkillCardWidget* PackageSkillCardWidget, int RowNum);
	UFUNCTION()
	void CreateSpecialtyList();
	UFUNCTION()
	void SetSpecialtyUI(USpecialSkillCardWidget* SpecialtyListForm, int RowNum);
	UFUNCTION()
	void CreateItemList();
	UFUNCTION()
	void SetItemUI(UItemSkillCardWidget* ItemListForm, int RowNum);
	UFUNCTION()
	void CreateSelectedSkillList();
	UFUNCTION()
	void ClickSkillTab();
	UFUNCTION()
	void ClickSpecialtyTab();
	UFUNCTION()
	void ClickItemTab();
	UFUNCTION()
	void SkillTabStyle(bool Clicked);
	UFUNCTION()
	void SpecialtyTabStyle(bool Clicked);
	UFUNCTION()
	void ItemTabStyle(bool Clicked);
	UFUNCTION()
	void Exit();
	UFUNCTION()
	void ResetSetting();
	UFUNCTION()
	void ClickSettingDone();
	UFUNCTION()
	void ClickAlertModalYes();
	UFUNCTION()
	void ClickAlertModalNo();
	UFUNCTION()
	void SaveSelectedSkill();
	UFUNCTION()
	void SaveSelectedSpecialty();
	UFUNCTION()
	void SaveSelectedItem();
	/*이전 전투 세팅 기록을 불러오는 함수*/
	UFUNCTION()
	void LoadBeforeSelectedSkills();
	/*스킬 선택*/
	UFUNCTION()
	void SelectSkill(FString IconName);
	UFUNCTION()
	void CancelSkill(FString IconName);
	UFUNCTION()
	void UpdateSelectedSkillIcon();
	/*특수기 선택*/
	UFUNCTION()
	void SelectSpecialSkill(FString IconName);
	/*아이템 선택*/
	UFUNCTION()
	void SelectItem(FString IconName);
	UFUNCTION()
	void CancelItem(FString IconName);
	UFUNCTION()
	void PlayAllSelectedSkillErrorAnim();
};
