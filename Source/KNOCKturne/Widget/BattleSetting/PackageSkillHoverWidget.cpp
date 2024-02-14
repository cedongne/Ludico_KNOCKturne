// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PackageSkillHoverWidget.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "PackageWidget.h"

void UPackageSkillHoverWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_Stance = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Stance"));
}

void UPackageSkillHoverWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPackageSkillHoverWidget::SetHoverWidgetUI(int RowNum, bool IsSelected)
{
	FPeppySkillData* PeppySkillData = BattleTableManagerSystem->PeppySkillTableRows[RowNum];
	FString StanceStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*PeppySkillData->SkillStance), TEXT(""))->KOR;
	FString SkillId = PeppySkillData->SkillId;
	FString NameStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SkillId.Append("_String")), TEXT(""))->KOR;
	FString DescriptionStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*PeppySkillData->SkillDescript), TEXT(""))->KOR;

	if (IsSelected)
		Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
	else
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);

	Image_Icon->SetBrushFromTexture(PeppySkillData->SkillIcon);
	TextBlock_CoolTimeSec->SetText(FText::FromString(FString::FromInt(PeppySkillData->SkillCoolTurn)));
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(PeppySkillData->Cost)));
	TextBlock_Stance->SetText(FText::FromString(StanceStr));
	TextBlock_SkillName->SetText(FText::FromString(NameStr));
	TextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));
}

FString UPackageSkillHoverWidget::CheckValueN(int SkillIndex, float ValueN)
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

FString UPackageSkillHoverWidget::CheckValueM(int SkillIndex, float ValueM)
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

FString UPackageSkillHoverWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
{
	switch (FCString::Atoi(*Num)) {
	case 0:
		return CheckValueN(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIndex_1, BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_1_N);
	case 1:
		return CheckValueM(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIndex_1, BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_1_M);
	case 2:
		return FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_1_T);
	case 3:
		return CheckProbability(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Probability_1);
	case 4:
		return CheckValueN(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIndex_2, BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_2_N);
	case 5:
		return CheckValueM(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIndex_2, BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_2_M);
	case 6:
		return FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_2_T);
	case 7:
		return CheckProbability(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Probability_2);
	case 8:
		return CheckValueN(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIndex_3, BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_3_N);
	case 9:
		return CheckValueM(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillIndex_3, BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_3_M);
	case 10:
		return FString::FromInt(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Value_3_T);
	case 11:
		return CheckProbability(BattleTableManagerSystem->PeppySkillTableRows[RowNum]->Probability_3);
	default:
		return "None";
	}
}

FString UPackageSkillHoverWidget::RedefineDescription(int RowNum)
{
	FString rowname = BattleTableManagerSystem->PeppySkillTableRows[RowNum]->SkillDescript;
	FString OriginalStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;
	FString tmp1 = "";
	FString skillindex = "";
	FString tmp2 = "";

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			if (Redefined[idx + 2] == '}') {
				tmp1 = Redefined.Mid(0, idx + 1);
				skillindex = GetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 1, 1));
				tmp2 = Redefined.Mid(idx + 2, Redefined.Len() - (idx + 2));
			}
			else {
				tmp1 = Redefined.Mid(0, idx + 2);
				skillindex = GetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 2, 1));
				tmp2 = Redefined.Mid(idx + 3, Redefined.Len() - (idx + 3));
			}

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

void UPackageSkillHoverWidget::ClickButton()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		if (PackageWidget) {
			bool isSelectSkill = PackageWidget->SelectSkill(Image_Icon->Brush.GetResourceName().ToString());
			if(isSelectSkill)
				Image_CheckBox->SetBrushFromTexture(icon_checkbox_selected);
		}
	}
	else {
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);

		if (PackageWidget)
			PackageWidget->CancelSkill(Image_Icon->Brush.GetResourceName().ToString());
	}
}

