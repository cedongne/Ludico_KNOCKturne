// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KNOCKturneGameInstance.h"
#include "Engine/GameInstance.h"

#include "DialogueManagerSystem.h"

UDialogueTableComponent::UDialogueTableComponent() {
	FString StringTablePath = TEXT("/Game/Assets/DataTable/StringTable.StringTable");
	FString DialogueStartIndexTablePath = TEXT("/Game/Assets/DataTable/StartIndexTable.StartIndexTable");
	//Load StringTable
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STRINGTABLE(*StringTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STARTINDEXTABLE(*DialogueStartIndexTablePath);
	NTCHECK(DT_STRINGTABLE.Succeeded());
	NTCHECK(DT_STARTINDEXTABLE.Succeeded());

	StringTable = DT_STRINGTABLE.Object;
	StartIndexTable = DT_STARTINDEXTABLE.Object;
	DialogueMap.Add({ "Dialogue_Prologue", "/Game/Assets/DataTable/Dialogue_Prologue.Dialogue_Prologue" });
	DialogueMap.Add({ "Dialogue_Npc", "/Game/Assets/DataTable/Dialogue_Npc.Dialogue_Npc" });

	IsEndedDialogueRows = false;
	CurrentRow = -1;
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	IsEndedDialogueRows = false;
	CurrentRow = -1;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
}

void UDialogueTableComponent::BeginPlay() {
	Super::BeginPlay();
}

void UDialogueTableComponent::LoadDialogueTable(FString TableName) {
//	DialogueTable = DialogueManager->LoadDialogueTable(TableName, CurrentRow);

	FStartIndex* StartIndexTableRow = StartIndexTable->FindRow<FStartIndex>(*TableName, TEXT(""));

	FString TablePath = DialogueMap[TableName];

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
	if (DialogueTable != nullptr) {
		NTLOG(Warning, TEXT("DialogueTable is not null"));
	}
	StringTable->GetAllRows<FDialogueString>("GetAllRows", DialogueStrings);
	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);
	

	CurrentRow = StartIndexTableRow->StringIndex - 1;
	NTLOG(Warning, TEXT("CurrentRow is %d"), CurrentRow);
	NTLOG(Warning, TEXT("DialogueSize is %d"), DialogueRows.Num());
}

FDialogueData* UDialogueTableComponent::GetDialogueTableRow(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

FString UDialogueTableComponent::GetString(FDialogueData* DataRow) {
//	return DialogueManager->GetStringTable()->FindRow<FDialogueString>(*(DataRow->StringID), TEXT(""))->KOR;
	return StringTable->FindRow<FDialogueString>(*(DataRow->StringID), TEXT(""))->KOR;
}

FString UDialogueTableComponent::GetStringOnBP(FDialogueData DataRow) {
	NTLOG(Warning, TEXT("%d"), CurrentRow);
//	return DialogueManager->GetStringTable()->FindRow<FDialogueString>(*(DataRow.StringID), TEXT(""))->KOR;
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

void UDialogueTableComponent::SetCurrentRow(int rowNum) {
	CurrentRow = rowNum;
}

int UDialogueTableComponent::GetCurrentRow() {
	return CurrentRow;
}

int UDialogueTableComponent::GetRowSize() {
	return DialogueRows.Num() - 1;
}

void UDialogueTableComponent::GetRandomTalkIndex() {
	for (int i = 0; i < DialogueRows.Num(); i++)
	{
		if (DialogueRows[i]->DialogueGroupCode == Episode ||
			DialogueRows[i]->DialogueGroupCode == "Default")
		{
			if (DialogueRows[i]->CharacterGroupCode == NpcName &&
				DialogueRows[i]->DialogueType == "1")
			{
				// 조건을 충족하는 인덱스만 StartRandomNpcTalk에 추가
				StartRandomNpcTalk.Add(i);
			}
		}
	}
	// 0 ~ StartRandomNpcTalk 크기 - 1사이의 숫자를 랜덤으로 
	int random = rand() % StartRandomNpcTalk.Num();
	SetCurrentRow(StartRandomNpcTalk[random]);
}

void UDialogueTableComponent::EmptyTArray() {
	StartRandomNpcTalk.Empty();
}