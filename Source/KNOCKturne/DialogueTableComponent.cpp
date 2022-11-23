// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"

UDialogueTableComponent::UDialogueTableComponent() {
	NTLOG(Warning, TEXT("UDialogueTableComponent is created."));
}

// Sets default values for this component's properties
UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

	// ...
}


void UDialogueTableComponent::LoadDialogueTable(FString TablePath) {
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
<<<<<<< Updated upstream
=======
	NTCHECK(DialogueTable == nullptr);
	NTLOG_S(Warning);
	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);
	NTCHECK(DialogueRows.IsValidIndex(0));
	NTLOG_S(Warning);
>>>>>>> Stashed changes
}

FDialogueData* UDialogueTableComponent::GetData(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

<<<<<<< Updated upstream
=======
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
		IsEndedDialogueRows = true;
	}
	return *(DialogueRows[CurrentRow]);
}

void UDialogueTableComponent::ResetDialogueRowPointer() {
	IsEndedDialogueRows = false;
	CurrentRow = 0;
}
>>>>>>> Stashed changes
