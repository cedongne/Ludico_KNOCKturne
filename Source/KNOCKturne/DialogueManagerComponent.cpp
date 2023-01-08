// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManagerComponent.h"

// Sets default values for this component's properties
UDialogueManagerComponent::UDialogueManagerComponent()
{
	FString StringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");
	FString DialogueStartIndexTablePath = TEXT("/Game/Assets/DataTable/StartIndexTable.StartIndexTable");
	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STRINGTABLE(*StringTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STARTINDEXTABLE(*DialogueStartIndexTablePath);
	NTCHECK(DT_STRINGTABLE.Succeeded());
	NTCHECK(DT_STARTINDEXTABLE.Succeeded());

	StringTable = DT_STRINGTABLE.Object;
	StartIndexTable = DT_STARTINDEXTABLE.Object;
	NTCHECK(StringTable != nullptr);
	NTCHECK(StartIndexTable != nullptr);
	DialogueMap.Add({ "Dialogue_Prologue", "/Game/Assets/DataTable/Dialogue_Prologue.Dialogue_Prologue" });
	DialogueMap.Add({ "Dialogue_Npc", "/Game/Assets/DataTable/Dialogue_Npc.Dialogue_Npc" });

	NTLOG_S(Warning);
//	FString temp = "Dialogue_Prologue";
//	NTLOG(Warning, TEXT("%d"), StringTable->FindRow<FStartIndex>(*temp, TEXT(""))->StringIndex);
}

UDataTable* UDialogueManagerComponent::GetStringTable() {
	return StringTable;
}

FString UDialogueManagerComponent::GetString(int index) {
	return *(DialogueStrings[index])->KOR;
}

UDataTable* UDialogueManagerComponent::LoadDialogueTable(FString TableName, int CurrentIndex) {
	FStartIndex* StartIndexTableRow = StartIndexTable->FindRow<FStartIndex>(*TableName, TEXT(""));

	FString TablePath = DialogueMap[TableName];

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	UDataTable* DialogueTable = DT_TABLE.Object;
	if (DialogueTable != nullptr) {
		NTLOG(Warning, TEXT("DialogueTable is not null"));
	}

	StringTable->GetAllRows<FDialogueString>("GetAllRows", DialogueStrings);

	CurrentIndex = StartIndexTableRow->StringIndex - 1;
	NTLOG(Warning, TEXT("CurrentRow is %d"), CurrentIndex);

	return DialogueTable;
}