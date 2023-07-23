// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"
#include "DialogueManagerSystem.h"

#include "Kismet/GameplayStatics.h"
#include "KNOCKturneGameInstance.h"
#include "Engine/GameInstance.h"
#include <string>

#define LOADING_STRING_NUM 12


UDialogueTableComponent::UDialogueTableComponent() {
	IsEndedDialogueRows = false;
	CurrentRowIndex = -1;
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	IsEndedDialogueRows = false;
	CurrentRowIndex = -1;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
}

void UDialogueTableComponent::BeginPlay() {
	Super::BeginPlay();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DialogueManager = GameInstance->GetSubsystem<UDialogueManagerSystem>();
}

void UDialogueTableComponent::LoadDialogueTable(FString TableName) {
	DialogueTable = DialogueManager->LoadDialogueTable(TableName, StartRowIndex);
	StartRowIndex = -1;
	CurrentRowIndex = StartRowIndex;
	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);

	NTLOG(Warning, TEXT("[%s] CurrentRow : %d, DialogueRows.Num() : %d"), *TableName, CurrentRowIndex, DialogueRows.Num());
}

FDialogueData* UDialogueTableComponent::GetDialogueTableRow(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

FString UDialogueTableComponent::GetString(FDialogueData* DataRow) {
	return DialogueManager->GetStringTable()->FindRow<FDialogueString>(*(DataRow->StringID), TEXT(""))->KOR;
}

FString UDialogueTableComponent::GetStringOnBP(FDialogueData DataRow) {
	NTLOG(Warning, TEXT("%d"), CurrentRowIndex);
	return DialogueManager->GetStringTable()->FindRow<FDialogueString>(*(DataRow.StringID), TEXT(""))->KOR;
}

FDialogueData UDialogueTableComponent::GetNextRowDialogueTable() {
	if (++CurrentRowIndex >= DialogueRows.Num() - 1) {
		IsEndedDialogueRows = true;
		NTLOG(Warning, TEXT("Reaching end to current dialogue"));
	}
	return *(DialogueRows[CurrentRowIndex]);
}

void UDialogueTableComponent::ResetDialogueRowPointer() {
	IsEndedDialogueRows = false;
	CurrentRowIndex = StartRowIndex;
}

void UDialogueTableComponent::SetCurrentRow(int rowNum) {
	CurrentRowIndex = rowNum;
}

int UDialogueTableComponent::GetCurrentRow() {
	return CurrentRowIndex;
}

int UDialogueTableComponent::GetRowSize() {
	return DialogueRows.Num() - 1;
}

void UDialogueTableComponent::GetRandomTalkIndex(FString NpcName) {
	for (int i = 0; i < DialogueRows.Num(); i++)
	{
		if (DialogueRows[i]->DialogueGroupCode == Episode ||
			DialogueRows[i]->DialogueGroupCode == "Default")
		{
			if (DialogueRows[i]->CharacterGroupCode == NpcName &&
				DialogueRows[i]->DialogueType == 1)
			{
				StartRandomNpcTalk.Add(i);
			}
		}
	}

	if (StartRandomNpcTalk.Num() != 0)
	{
		int random = rand() % StartRandomNpcTalk.Num();
		SetCurrentRow(StartRandomNpcTalk[random] - 1);
	}
}

void UDialogueTableComponent::EmptyTArray() {
	StartRandomNpcTalk.Empty();
}

bool UDialogueTableComponent::NextDialogueTypeIs1() {
	if ((CurrentRowIndex + 1) < DialogueRows.Num() && DialogueRows[CurrentRowIndex + 1] != NULL)
	{
		if (DialogueRows[CurrentRowIndex + 1]->DialogueType == 1)
			return true;
		else
			return false;
	}
	else
		return false;
}

int32 UDialogueTableComponent::GetCurrentDialogueType()
{
	return DialogueRows[CurrentRowIndex]->DialogueType;
}

void UDialogueTableComponent::SkipDialogue() {
	CurrentRowIndex = StartRowIndex + DialogueRows.Num() - 1;
	IsEndedDialogueRows = true;
}

void UDialogueTableComponent::SetIsEndedDialogueRows(bool tf) {
	IsEndedDialogueRows = tf;
}

FString UDialogueTableComponent::RandomLoadingText() {
	int random = rand() % LOADING_STRING_NUM + DialogueManager->GetStartIndexTable()->FindRow<FStartIndex>(TEXT("Loading_String"), TEXT(""))->StringIndex;
	return DialogueManager->GetString2(random);
}

void UDialogueTableComponent::SetDreamFragmentDialogueIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "DreamFragment")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

void UDialogueTableComponent::SetDreamFragmentCancelIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "DreamFragment_Cancel")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

void UDialogueTableComponent::SetAfterBattleDialogueIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "EP1_AfterBattle")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}