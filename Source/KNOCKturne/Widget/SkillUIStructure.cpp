// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillUIStructure.h"
#include <Components/SlateWrapperTypes.h>

SkillUIStructure::SkillUIStructure()
{
	FString UI_battleSetting_background_default_Path = TEXT("/Game/Assets/Art_UI/BattleUI/UI_battleSetting/Common/UI_battleSetting_background_default.UI_battleSetting_background_default");
	FString UI_battleSetting_skill_default_Path = TEXT("/Game/Assets/Art_UI/BattleUI/UI_battleSetting/Common/UI_battleSetting_skill_default.UI_battleSetting_skill_default");
	FString Icon_skill_PS_WithYou_Path = TEXT("/Game/Assets/Art_UI/BattleUI/UI_battleSetting/Common/UI_battleSetting_background_default.UI_battleSetting_background_default");
	FString icon_checkbox_Path = TEXT("/Game/Assets/Art_UI/BattleUI/UI_battleSetting/Common/icon_checkbox.icon_checkbox");
	FString UI_battleSetting_skill_none_Path = TEXT("/Game/Assets/Art_UI/BattleUI/UI_battleSetting/Common/UI_battleSetting_background_default.UI_battleSetting_background_default");
	static ConstructorHelpers::FObjectFinder<UTexture2D> DT_UI_battleSetting_background_default(*UI_battleSetting_background_default_Path);
	static ConstructorHelpers::FObjectFinder<UTexture2D> DT_UI_battleSetting_skill_default(*UI_battleSetting_skill_default_Path);
	static ConstructorHelpers::FObjectFinder<UTexture2D> DT_Icon_skill_PS_WithYou(*Icon_skill_PS_WithYou_Path);
	static ConstructorHelpers::FObjectFinder<UTexture2D> DT_icon_checkbox(*icon_checkbox_Path);
	static ConstructorHelpers::FObjectFinder<UTexture2D> DT_UI_battleSetting_skill_none(*UI_battleSetting_skill_none_Path);
	UI_battleSetting_background_default = DT_UI_battleSetting_background_default.Object;
	UI_battleSetting_skill_default = DT_UI_battleSetting_skill_default.Object;
	Icon_skill_PS_WithYou = DT_Icon_skill_PS_WithYou.Object;
	icon_checkbox = DT_icon_checkbox.Object;
	UI_battleSetting_skill_none = DT_UI_battleSetting_skill_none.Object;
}

void SkillUIStructure::InitializeSkillStructure(FSkillStructureData SkillStructure) {
	SkillStructure.BackgroundImg = UI_battleSetting_background_default;
	SkillStructure.IconBackgroundImg = UI_battleSetting_skill_default;
	SkillStructure.SkillIcon = Icon_skill_PS_WithYou;
	SkillStructure.CheckBox = icon_checkbox;
	SkillStructure.Num = -1;
	SkillStructure.SkillName = FText::FromString("");
	SkillStructure.Energy = 0;
	SkillStructure.Stance = FText::FromString("");
	SkillStructure.CoolTime = 0;
	SkillStructure.NumVisibility = ESlateVisibility::Hidden;
	SkillStructure.Description = FText::FromString("");
}

void SkillUIStructure::InitializeSelectedSkillStructure(FSelectedSkillStructureData SelectedSkillStructure) {
	SelectedSkillStructure.BackgroundImg = UI_battleSetting_background_default;
	SelectedSkillStructure.Icon = Icon_skill_PS_WithYou;
	SelectedSkillStructure.IconVisibility = ESlateVisibility::Hidden;
	SelectedSkillStructure.CancelButton = ESlateVisibility::Hidden;
	SelectedSkillStructure.NumVisibility = ESlateVisibility::Hidden;
	SelectedSkillStructure.NumBackgroundVisibility = ESlateVisibility::Hidden;
}

void SkillUIStructure::InitializeItemStructure(FItemStructureData ItemStructure) {
	ItemStructure.BackgroundImg = UI_battleSetting_background_default;
	ItemStructure.IconBackgroundImg = UI_battleSetting_skill_default;
	ItemStructure.Icon = Icon_skill_PS_WithYou;
	ItemStructure.CheckBox = icon_checkbox;
	ItemStructure.SkillName = FText::FromString("");
	ItemStructure.Count = 0;
	ItemStructure.Description = FText::FromString("");
}