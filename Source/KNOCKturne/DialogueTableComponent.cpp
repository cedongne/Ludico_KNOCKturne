// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"

UDialogueTableComponent::UDialogueTableComponent() {
	FString DialogueStringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");

	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DIALOGUETABLE(*DialogueStringTablePath);
	NTCHECK(DT_DIALOGUETABLE.Succeeded());

	StringTable = DT_DIALOGUETABLE.Object;

	isEndedDialogueRows = false;
	CurrentRow = 0;
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

}

void UDialogueTableComponent::LoadDialogueTable(FString TablePath) {
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);
	NTLOG_S(Warning);
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

int32 UDialogueTableComponent::GetDialogueTableRowSize() {
	return DialogueTable->GetRowMap().Num();
}

FDialogueData UDialogueTableComponent::GetNextRowDialogueTable() {
	if (++CurrentRow == DialogueRows.Num() - 1) {
		isEndedDialogueRows = true;
	}
	return *DialogueRows[CurrentRow];
}

void UDialogueTableComponent::ResetDialogueRowPointer() {
	isEndedDialogueRows = false;
	CurrentRow = 0;
}