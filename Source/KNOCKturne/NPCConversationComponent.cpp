// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCConversationComponent.h"

UNPCConversationComponent::UNPCConversationComponent() {
	FString DialogueStringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");

	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DIALOGUETABLE(*DialogueStringTablePath);
	NTCHECK(DT_DIALOGUETABLE.Succeeded());

	StringTable = DT_DIALOGUETABLE.Object;

	IsEndedDialogueRows = false;
	CurrentRow = -1;
}

UNPCConversationComponent::UNPCConversationComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

}

void UNPCConversationComponent::LoadDialogueTable(FString TablePath) {
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
	if (DialogueTable != nullptr) {
		NTLOG_S(Warning);
	}

	DialogueTable->GetAllRows<FNPCConversation>("GetAllRows", DialogueRows);
	if (DialogueRows.Num() != 0) {
		NTLOG(Warning, TEXT("%d"), DialogueRows.Num());
	}
}


FNPCConversation* UNPCConversationComponent::GetDialogueTableRow(FString RowID) {
	return DialogueTable->FindRow<FNPCConversation>(*RowID, TEXT(""));
}

FNPCConversation UNPCConversationComponent::GetNextRowDialogueTable() {
	if (++CurrentRow == DialogueRows.Num() - 1) {
		IsEndedDialogueRows = true;
		NTLOG(Warning, TEXT("End"));
	}
	return *(DialogueRows[CurrentRow]);
}

void UNPCConversationComponent::ResetDialogueRowPointer() {
	IsEndedDialogueRows = false;
	CurrentRow = -1;
}