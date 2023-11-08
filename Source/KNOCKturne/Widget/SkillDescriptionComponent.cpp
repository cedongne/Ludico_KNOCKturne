// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillDescriptionComponent.h"
#include <Blueprint/SlateBlueprintLibrary.h>

USkillDescriptionComponent::USkillDescriptionComponent()
{
	FString PeppySkillTablePath = TEXT("/Game/Assets/DataTable/PeppySkillTable.PeppySkillTable");
	FString SpecialSkillTablePath = TEXT("/Game/Assets/DataTable/SpecialSkillTable.SpecialSkillTable");
	FString ItemTablePath = TEXT("/Game/Assets/DataTable/ItemTable.ItemTable");
	FString SkillBuffStringTablePath = TEXT("/Game/Assets/DataTable/SkillBuffStringTable.SkillBuffStringTable");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSKILLTABLE(*PeppySkillTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SPECIALSKILLTABLE(*SpecialSkillTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*ItemTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLBUFFSTRINGTABLE(*SkillBuffStringTablePath);

	PeppySkillTable = DT_PEPPYSKILLTABLE.Object;
	SpecialSkillTable = DT_SPECIALSKILLTABLE.Object;
	ItemTable = DT_ITEMTABLE.Object;
	SkillBuffStringTable = DT_SKILLBUFFSTRINGTABLE.Object;

	PeppySkillTable->GetAllRows<FPeppySkillData>("GetAllRows", PeppySkillTableRows);
	SpecialSkillTable->GetAllRows<FSpecialSkillData>("GetAllRows", SpecialSkillTableRows);
	ItemTable->GetAllRows<FItemData>("GetAllRows", ItemTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);
}

/*Skill*/

FString USkillDescriptionComponent::SkillSpecialtyCheckValueN(int SkillIndex, float ValueN) {
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

FString USkillDescriptionComponent::SkillSpecialtyCheckValueM(int SkillIndex, float ValueM) {
	if (ValueM != -1.0) {
		if (SkillIndex == 91) {
			return FString::FromInt(round(ValueM * 100.0));
		}
		else {
			return FString::FromInt(round(ValueM * 100));
		}
	}
	else {
		return "None";
	}
}

FString USkillDescriptionComponent::CheckProbability(float Probability)
{
	if (Probability != -1.0) {
		return FString::FromInt(round(Probability * 100.0));
	}
	else {
		return "None";
	}
}



FString USkillDescriptionComponent::SkillGetSkillIndexByKeyword(int RowNum, FString Num) {
	switch (FCString::Atoi(*Num)) {
	case 0:
		return SkillSpecialtyCheckValueN(PeppySkillTableRows[RowNum]->SkillIndex_1, PeppySkillTableRows[RowNum]->Value_1_N);
	case 1:
		return SkillSpecialtyCheckValueM(PeppySkillTableRows[RowNum]->SkillIndex_1, PeppySkillTableRows[RowNum]->Value_1_M);
	case 2:
		return FString::FromInt(PeppySkillTableRows[RowNum]->Value_1_T);
	case 3:
		return CheckProbability(PeppySkillTableRows[RowNum]->Probability_1);
	case 4:
		return SkillSpecialtyCheckValueN(PeppySkillTableRows[RowNum]->SkillIndex_2, PeppySkillTableRows[RowNum]->Value_2_N);
	case 5:
		return SkillSpecialtyCheckValueM(PeppySkillTableRows[RowNum]->SkillIndex_2, PeppySkillTableRows[RowNum]->Value_2_M);
	case 6:
		return FString::FromInt(PeppySkillTableRows[RowNum]->Value_2_T);
	case 7:
		return CheckProbability(PeppySkillTableRows[RowNum]->Probability_2);
	case 8:
		return SkillSpecialtyCheckValueN(PeppySkillTableRows[RowNum]->SkillIndex_3, PeppySkillTableRows[RowNum]->Value_3_N);
	case 9:
		return SkillSpecialtyCheckValueM(PeppySkillTableRows[RowNum]->SkillIndex_3, PeppySkillTableRows[RowNum]->Value_3_M);
	case 10:
		return FString::FromInt(PeppySkillTableRows[RowNum]->Value_3_T);
	case 11:
		return CheckProbability(PeppySkillTableRows[RowNum]->Probability_3);
	default:
		return "None";
	}
}

FString USkillDescriptionComponent::SkillRedefineDescription(int RowNum) {
	FString rowname = PeppySkillTableRows[RowNum]->SkillDescript;
	FString OriginalStr = SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;
	FString tmp1 = "";
	FString skillindex = "";
	FString tmp2 = "";

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			if (Redefined[idx + 2] == '}') {
				tmp1 = Redefined.Mid(0, idx + 1);
				skillindex = SkillGetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 1, 1));
				tmp2 = Redefined.Mid(idx + 2, Redefined.Len() - (idx + 2));
			}
			else {
				tmp1 = Redefined.Mid(0, idx + 2);
				skillindex = SkillGetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 2, 1));
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

/*SpecialSkill*/

FString USkillDescriptionComponent::SpecialtyGetSkillIndexByKeyword(int RowNum, FString Num) {
	switch (FCString::Atoi(*Num)) {
	case 0:
		return SkillSpecialtyCheckValueN(SpecialSkillTableRows[RowNum]->Skill_Index, SpecialSkillTableRows[RowNum]->value1N);
	case 1:
		return SkillSpecialtyCheckValueM(SpecialSkillTableRows[RowNum]->Skill_Index, SpecialSkillTableRows[RowNum]->value1M);
	case 2:
		return FString::FromInt(PeppySkillTableRows[RowNum]->Value_1_T);
	case 3:
		return CheckProbability(SpecialSkillTableRows[RowNum]->Probability_1);

	default:
		return "None";
	}
}

FString USkillDescriptionComponent::SpecialtyRedefineDescription(int RowNum) {
	FString rowname = SpecialSkillTableRows[RowNum]->SpecialSkillDescript;
	FString OriginalStr = SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			FString tmp1 = Redefined.Mid(0, idx + 1);
			FString skillindex = SpecialtyGetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 1, 1));
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

/*Item*/

FString USkillDescriptionComponent::ItemCheckValueN(float ValueN) {
	if (ValueN != -1.0) {
		return FString::FromInt(round(ValueN));
	}
	else {
		return "None";
	}
}

FString USkillDescriptionComponent::ItemCheckValueM(float ValueM) {
	if (ValueM != -1.0) {
		return FString::FromInt(round(ValueM * 100));
	}
	else {
		return "None";
	}
}

FString USkillDescriptionComponent::ItemGetSkillIndexByKeyword(int RowNum, FString Num) {
	switch (FCString::Atoi(*Num)) {
	case 0:
		return ItemCheckValueN(ItemTableRows[RowNum]->value1N);
	case 1:
		return ItemCheckValueM(ItemTableRows[RowNum]->value1M);
	default:
		return "None";
	}
}

FString USkillDescriptionComponent::ItemRedefineDescription(int RowNum) {
	FString rowname = ItemTableRows[RowNum]->ItemDescript;
	FString OriginalStr = SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			FString tmp1 = Redefined.Mid(0, idx + 1);
			FString skillindex = ItemGetSkillIndexByKeyword(RowNum, Redefined.Mid(idx + 1, 1));
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

void USkillDescriptionComponent::SetHoverWidgetPos(UUserWidget* hoverwidget, UButton* backgroundBtn)
{
	FVector2D pos;
	pos.X = backgroundBtn->GetCachedGeometry().GetAbsolutePosition().X;
	pos.Y = backgroundBtn->GetCachedGeometry().GetAbsolutePosition().Y - (backgroundBtn->GetDesiredSize().Y) / 2 + (hoverwidget->GetDesiredSize().Y) / 2;
	hoverwidget->SetPositionInViewport(pos);
}