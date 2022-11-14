// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"

UDialogueTableComponent::UDialogueTableComponent() {
	FString DialogueStringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");

	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DIALOGUETABLE(*DialogueStringTablePath);
	NTCHECK(DT_DIALOGUETABLE.Succeeded());

	StringTable = DT_DIALOGUETABLE.Object;
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

}

void UDialogueTableComponent::LoadDialogueTable(FString TablePath) {
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
}

FDialogueData* UDialogueTableComponent::GetDialogueTableRow(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

FString UDialogueTableComponent::GetString(FDialogueData* DataRow) {
	return StringTable->FindRow<FDialogueString>(*(DataRow->StringID), TEXT(""))->KOR;

}