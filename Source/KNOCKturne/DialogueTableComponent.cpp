// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"
#include "DialogueManagerSystem.h"

#include "Kismet/GameplayStatics.h"
#include "KNOCKturneGameInstance.h"
#include "Engine/GameInstance.h"
#include <string>


UDialogueTableComponent::UDialogueTableComponent() {
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

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DialogueManager = GameInstance->GetSubsystem<UDialogueManagerSystem>();
}

void UDialogueTableComponent::LoadDialogueTable(FString TableName) {
	DialogueTable = DialogueManager->LoadDialogueTable(TableName, CurrentRow);
	DialogueTable->GetAllRows<FDialogueData>("GetAllRows", DialogueRows);

	NTLOG(Warning, TEXT("CurrentRow is %d"), CurrentRow);
	NTLOG(Warning, TEXT("DialogueSize is %d"), DialogueRows.Num());
}

FDialogueData* UDialogueTableComponent::GetDialogueTableRow(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

FString UDialogueTableComponent::GetString(FDialogueData* DataRow) {
	return DialogueManager->GetStringTable()->FindRow<FDialogueString>(*(DataRow->StringID), TEXT(""))->KOR;
}

FString UDialogueTableComponent::GetStringOnBP(FDialogueData DataRow) {
	NTLOG(Warning, TEXT("%d"), CurrentRow);
	return DialogueManager->GetStringTable()->FindRow<FDialogueString>(*(DataRow.StringID), TEXT(""))->KOR;
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
				// ������ �����ϴ� �ε����� StartRandomNpcTalk�� �߰�
				StartRandomNpcTalk.Add(i);
			}
		}
	}
	// 0 ~ StartRandomNpcTalk ũ�� - 1������ ���ڸ� �������� 
	int random = rand() % StartRandomNpcTalk.Num();
	SetCurrentRow(StartRandomNpcTalk[random] - 1);
}

void UDialogueTableComponent::EmptyTArray() {
	StartRandomNpcTalk.Empty();
}

bool UDialogueTableComponent::NextDialogueTypeIs1() {
	if (DialogueRows[CurrentRow + 1]->DialogueType == "1")
		return true;
	else
		return false;
}

FString UDialogueTableComponent::GetCurrentDialogueType()
{
	return DialogueRows[CurrentRow]->DialogueType;
}

void UDialogueTableComponent::SkipDialogue() {
	while (++CurrentRow != DialogueRows.Num() - 1);
	IsEndedDialogueRows = true;
}

void UDialogueTableComponent::SetIsEndedDialogueRows(bool tf) {
	IsEndedDialogueRows = tf;
}

FString UDialogueTableComponent::RandomLoadingText() {
	int random = rand() % 12 + 66;
	return DialogueManager->GetString2(random);
}