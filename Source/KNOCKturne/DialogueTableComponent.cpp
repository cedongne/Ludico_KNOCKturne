// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"

UDialogueTableComponent::UDialogueTableComponent() {
	FString DialogueStringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");
	FString DialogueStartIndexTablePath = TEXT("/Game/Assets/DataTable/StartIndexTable.StartIndexTable");
	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DIALOGUETABLE(*DialogueStringTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STARTINDEXTABLE(*DialogueStartIndexTablePath);
	NTCHECK(DT_DIALOGUETABLE.Succeeded());
	NTCHECK(DT_STARTINDEXTABLE.Succeeded());

	StringTable = DT_DIALOGUETABLE.Object;
	StartIndexTable = DT_STARTINDEXTABLE.Object;

	IsEndedDialogueRows = false;
	CurrentRow = -1;
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
}

void UDialogueTableComponent::LoadDialogueTable(FString TableName) {
	FStartIndex* StartIndexTableRow = StartIndexTable->FindRow<FStartIndex>(*TableName, TEXT(""));

	FString TablePath = "";
	if (TableName == "Dialogue_Npc") {
		TablePath = DialogueTables.Dialogue_Npc;
	}
	else if (TableName == "Dialogue_Prologue") {
		TablePath = DialogueTables.Dialogue_Prologue;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
	if (DialogueTable != nullptr) {
		NTLOG_S(Warning);
	}

	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);
	if (DialogueRows.Num() != 0) {
		NTLOG(Warning, TEXT("%d"), DialogueRows.Num());
	}

	CurrentRow = StartIndexTableRow->StringIndex - 1;
	NTLOG(Warning, TEXT("%d"), CurrentRow);
}

FDialogueData* UDialogueTableComponent::GetDialogueTableRow(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

FString UDialogueTableComponent::GetString(FDialogueData* DataRow) {
	return StringTable->FindRow<FDialogueString>(*(DataRow->StringID), TEXT(""))->KOR;
}

FString UDialogueTableComponent::GetStringOnBP(FDialogueData DataRow) {
	NTLOG(Warning, TEXT("%d"), CurrentRow);
	return StringTable->FindRow<FDialogueString>(*(DataRow.StringID), TEXT(""))->KOR;
}

FDialogueData UDialogueTableComponent::GetNextRowDialogueTable() {
	if (++CurrentRow == DialogueRows.Num() - 1) {
		IsEndedDialogueRows = true;
		NTLOG(Warning, TEXT("End"));
	}
	return *(DialogueRows[CurrentRow]);
}

void UDialogueTableComponent::ResetDialogueRowPointer() {
	IsEndedDialogueRows = false;
	CurrentRow = -1;
}

int UDialogueTableComponent::GetCurrentRow() {
	return CurrentRow;
}