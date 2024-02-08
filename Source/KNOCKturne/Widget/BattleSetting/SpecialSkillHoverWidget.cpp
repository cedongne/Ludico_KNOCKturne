// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/SpecialSkillHoverWidget.h"
#include <GameInstance/DialogueManagerSystem.h>

void USpecialSkillHoverWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
}

void USpecialSkillHoverWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USpecialSkillHoverWidget::SetHoverWidgetUI(int RowNum, bool IsSelected)
{
	FSpecialSkillTable* SpecialSkillData = BattleTableManagerSystem->SpecialSkillTableRows[RowNum];
	FString SpecialSkillId = BattleTableManagerSystem->SpecialSkillTable->GetRowNames()[RowNum].ToString();
	FString NameStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SpecialSkillId.Append("_String")), TEXT(""))->KOR;
	FString DescriptionStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SpecialSkillData->SpecialSkillDescript), TEXT(""))->KOR;

	if (IsSelected)
		Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	else
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);

	Image_Icon->SetBrushFromTexture(SpecialSkillData->SpecialSkillIcon);
	TextBlock_CoolTimeSec->SetText(FText::FromString(FString::FromInt(SpecialSkillData->CoolTime)));
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(SpecialSkillData->EnergyCost)));
	TextBlock_SkillName->SetText(FText::FromString(NameStr));
	TextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));
}

FString USpecialSkillHoverWidget::CheckValueN(int SkillIndex, float ValueN)
{
	if (ValueN != -1.0) {
		if (SkillIndex == 72 || SkillIndex == 91) {
			return FString::FromInt(round(ValueN * 100.0));
		}
		else {
			return FString::FromInt(round(ValueN));
		}
	}
	else {
		return "None";
	}
}

FString USpecialSkillHoverWidget::CheckValueM(int SkillIndex, float ValueM)
{
	if (ValueM != -1.0) {
		if (SkillIndex == 91) {
			return FString::FromInt(round(ValueM * 100.0));
		}
		else {
			return FString::FromInt(round(ValueM));
		}
	}
	else {
		return "None";
	}
}

FString USpecialSkillHoverWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
{
	switch (FCString::Atoi(*Num)) {
	case 0:
		return CheckValueN(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Skill_Index, BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Value1N);
	case 1:
		return CheckValueM(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Skill_Index, BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Value1M);
	case 2:
		return FString::FromInt(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Value1T);
	case 3:
		return CheckProbability(BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->Probability_1);

	default:
		return "None";
	}
}

FString USpecialSkillHoverWidget::RedefineDescription(int RowNum)
{
	FString rowname = BattleTableManagerSystem->SpecialSkillTableRows[RowNum]->SpecialSkillDescript;
	FString OriginalStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			FString tmp1 = Redefined.Mid(0, idx + 1);
			FString skillindex = GetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 1, 1));
			FString tmp2 = Redefined.Mid(idx + 2, Redefined.Len() - (idx + 2));

			Redefined = (tmp1.Append(skillindex)).Append(tmp2);
		}
	}

	int count = -1;
	for (int index = 0; index < Redefined.Len(); index++) {
		if (Redefined[index] == '{' || Redefined[index] == '}') {
			count++;
			Redefined.RemoveAt(index, 1);
		}
	}

	return Redefined;
}
