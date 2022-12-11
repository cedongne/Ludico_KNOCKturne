// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"

UDialogueTableComponent::UDialogueTableComponent() {
	FString DialogueStringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");

	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DIALOGUETABLE(*DialogueStringTablePath);
	NTCHECK(DT_DIALOGUETABLE.Succeeded());

	StringTable = DT_DIALOGUETABLE.Object;

	IsEndedDialogueRows = false;
	CurrentRow = -1;
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

}

void UDialogueTableComponent::LoadDialogueTable(FString TablePath) {
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
	if (DialogueTable != nullptr) {
		NTLOG_S(Warning);
	}

	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);
	if (DialogueRows.Num() != 0) {
		NTLOG(Warning, TEXT("%d"), DialogueRows.Num());
	}
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
