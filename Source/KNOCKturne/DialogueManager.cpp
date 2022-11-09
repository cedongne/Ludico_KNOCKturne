// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"

UDialogueManager::UDialogueManager() {
	FString PrologueDialogueTablePath = TEXT("/Game/Assets/DataTable/Dialog_Prologue.Dialog_Prologue");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PROLOGUEDIALOGUETABLE(*PrologueDialogueTablePath);
	PrologueDialogueTable = DT_PROLOGUEDIALOGUETABLE.Object;

	NTLOG(Warning, TEXT("DialogueManager is created %s"), *(GetPrologueDialogueData("Prologue_1")->GroupCode));
}

FDialogueData* UDialogueManager::GetPrologueDialogueData(FString RowID) {
	return PrologueDialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}
