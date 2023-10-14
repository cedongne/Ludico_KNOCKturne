// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillDescriptionComponent.h"

USkillDescriptionComponent::USkillDescriptionComponent()
{
	FString ItemTablePath = TEXT("/Game/Assets/DataTable/ItemTable.ItemTable");
	FString SkillBuffStringTablePath = TEXT("/Game/Assets/DataTable/SkillBuffStringTable.SkillBuffStringTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*ItemTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLBUFFSTRINGTABLE(*SkillBuffStringTablePath);
	ItemTable = DT_ITEMTABLE.Object;
	SkillBuffStringTable = DT_SKILLBUFFSTRINGTABLE.Object;
	ItemTable->GetAllRows<FItemData>("GetAllRows", ItemTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);
}

FString USkillDescriptionComponent::ItemCheckValueN(float ValueN) {
	if (ValueN != -1.0) {
		return FString::SanitizeFloat(ValueN);
	}
	else {
		return "None";
	}
}

FString USkillDescriptionComponent::ItemCheckValueM(float ValueM) {
	if (ValueM != -1.0) {
		return FString::SanitizeFloat(ValueM * 100);
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
	FString Redefined;

	for (int idx = 0; idx < OriginalStr.Len(); idx++) {
		if (OriginalStr[idx] == '{') {
			const TCHAR* Keyword = *OriginalStr.Mid(idx + 1, 1);
			const TCHAR* SkillIndex = *ItemGetSkillIndexByKeyword(RowNum, Keyword);
			Redefined = OriginalStr.Replace(Keyword, SkillIndex);
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