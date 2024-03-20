// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BattleSetting/PeppyTurnSkillHoverWidget.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "PeppyTurnUIWidget.h"
#include "PeppyTurnUIWidget.h"

void UPeppyTurnSkillHoverWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_CoolTimeSec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_CoolTimeSec"));
	TextBlock_Energy = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Energy"));
	TextBlock_Stance = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Stance"));
	TextBlock_Num = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Num"));
}

void UPeppyTurnSkillHoverWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UPeppyTurnSkillHoverWidget::SetHoverWidgetUI(int RowNum, bool IsSelected)
{
	TArray<FString> Keys;
	BattleTableManagerSystem->PeppySkillData.GetKeys(Keys);
	FString ClassName = Keys[RowNum];

	FPeppySkillData PeppySkillData = BattleTableManagerSystem->PeppySkillData[ClassName];
	FString StanceStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(PeppySkillData.SkillStance), TEXT(""))->KOR;
	FString SkillId = PeppySkillData.SkillId;
	FString NameStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*SkillId.Append("_String")), TEXT(""))->KOR;
	FString DescriptionStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(PeppySkillData.SkillDescript), TEXT(""))->KOR;

	Image_Icon->SetBrushFromTexture(PeppySkillData.SkillIcon);
	TextBlock_CoolTimeSec->SetText(FText::FromString(FString::FromInt(PeppySkillData.SkillCoolTurn)));
	TextBlock_Energy->SetText(FText::FromString(FString::FromInt(PeppySkillData.Cost)));
	TextBlock_Stance->SetText(FText::FromString(StanceStr));
	TextBlock_SkillName->SetText(FText::FromString(NameStr));
	TextBlock_Description->SetText(FText::FromString(RedefineDescription(RowNum)));

	if (IsSelected) {
		Image_CheckBox->SetBrushFromTexture(icon_checkbox_numbering);
		TextBlock_Num->SetVisibility(ESlateVisibility::Visible);
		int SequenceNum = PeppyTurnWidget->IconSequenceRowMap[Image_Icon->Brush.GetResourceName().ToString()];
		TextBlock_Num->SetText(FText::FromString(FString::FromInt(SequenceNum)));
	}
	else
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);
}

FString UPeppyTurnSkillHoverWidget::CheckValueN(int SkillIndex, float ValueN)
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

FString UPeppyTurnSkillHoverWidget::CheckValueM(int SkillIndex, float ValueM)
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

FString UPeppyTurnSkillHoverWidget::GetSkillIndexByKeyword(int RowNum, FString Num)
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

FString UPeppyTurnSkillHoverWidget::RedefineDescription(int RowNum)
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

	for (int index = 0; index < Redefined.Len(); index++) {
		if (Redefined[index] == '{' || Redefined[index] == '}') {
			Redefined.RemoveAt(index, 1);
		}
	}

	return Redefined;
}

void UPeppyTurnSkillHoverWidget::ClickButton()
{
	if (Image_CheckBox->Brush.GetResourceName() == "icon_checkbox") {
		if (PeppyTurnWidget) {
			bool isSelectSkill = PeppyTurnWidget->SelectSkill(Image_Icon->Brush.GetResourceName().ToString());

			if (isSelectSkill) {
				Image_CheckBox->SetBrushFromTexture(icon_checkbox_numbering);
				TextBlock_Num->SetVisibility(ESlateVisibility::Visible);

				int SequenceNum = PeppyTurnWidget->IconSequenceRowMap[Image_Icon->Brush.GetResourceName().ToString()];
				TextBlock_Num->SetText(FText::FromString(FString::FromInt(SequenceNum)));
			}
		}
	}
	else {
		Image_CheckBox->SetBrushFromTexture(icon_checkbox);
		TextBlock_Num->SetVisibility(ESlateVisibility::Hidden);

		if (PeppyTurnWidget)
			PeppyTurnWidget->CancelSkill(Image_Icon->Brush.GetResourceName().ToString());
	}
}