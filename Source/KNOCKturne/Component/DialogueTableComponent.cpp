// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"
#include "GameInstance/DialogueManagerSystem.h"
#include "GameInstance/KNOCKturneGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include <string>

#define LOADING_STRING_NUM 12


UDialogueTableComponent::UDialogueTableComponent() {
	IsEndedDialogueRows = false;
	CurrentRowIndex = -1;
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	IsEndedDialogueRows = false;
	CurrentRowIndex = -1;
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

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

void UDialogueTableComponent::SetRandomTalkIndex(ANPC* InteractingNpc, FString InteractingNpcGroupcode) {
	if (InteractingNpc->GiveFragment == false && InteractingNpc->TalkCount != 0 && InteractingNpc->TalkCount != 3) {
		int GiveFragmentPro = 0;
		int Probability = rand() % 100 + 1;

		if (InteractingNpc->TalkCount == 1) {
			GiveFragmentPro = 30;
		}
		else if (InteractingNpc->TalkCount == 2) {
			GiveFragmentPro = 50;
		}
		
		if (GiveFragmentPro > Probability) {
			GetGiveFragmentRandomTalkIndexs(InteractingNpc, InteractingNpcGroupcode);
		}
	}
	else if (InteractingNpc->TalkCount == 3) {
		GetGiveFragmentRandomTalkIndexs(InteractingNpc, InteractingNpcGroupcode);
	}
	else {
		GetNormalRandomTalkIndexs(InteractingNpc, InteractingNpcGroupcode);
	}

	if (StartRandomNpcTalk.Num() != 0)
	{
		if (StartRandomNpcTalk.Num() > 1) {
			int random = rand() % StartRandomNpcTalk.Num();
			SetCurrentRow(StartRandomNpcTalk[random] - 1);
		}
		else {
			SetCurrentRow(StartRandomNpcTalk[0] - 1);
		}
	}
}

void UDialogueTableComponent::GetNormalRandomTalkIndexs(ANPC* InteractingNpc, FString InteractingNpcGroupcode) {
	for (int i = 0; i < DialogueRows.Num(); i++)
	{
		if (DialogueRows[i]->DialogueGroupCode == Episode ||
			DialogueRows[i]->DialogueGroupCode == "Default")
		{
			if (DialogueRows[i]->CharacterGroupCode == InteractingNpcGroupcode &&
				DialogueRows[i]->DialogueType == 1)
			{
				StartRandomNpcTalk.Add(i);
			}
		}
	}

	InteractingNpc->TalkCount++;
}

void UDialogueTableComponent::GetGiveFragmentRandomTalkIndexs(ANPC* InteractingNpc, FString InteractingNpcGroupcode) {
	for (int i = 0; i < DialogueRows.Num(); i++)
	{
		if (DialogueRows[i]->DialogueGroupCode == "GiveFragment")
		{
			if (DialogueRows[i]->CharacterGroupCode == InteractingNpcGroupcode &&
				DialogueRows[i]->DialogueType == 1)
			{
				StartRandomNpcTalk.Add(i);
			}
		}
	}

	KNOCKturneGameState->DreamFragmentCount++;
	InteractingNpc->GiveFragment = true;
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

void UDialogueTableComponent::SetAfterBattleDialogueinHubworldIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "EP1_AfterBattle_Hubworld")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

void UDialogueTableComponent::SetAfterBattleFailDialogueIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "AfterBattleFail_Hubworld")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

void UDialogueTableComponent::SetBattleFailDiaryDialogueIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "AfterBattleFail_Hubworld_DreamDiary")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

void UDialogueTableComponent::SetBattleFailFragmentDialogueIndex() {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == "AfterBattleFail_Hubworld_DreamFragment")
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

void UDialogueTableComponent::SetDialogueIndexByGroupCode(FString GroupCode) {
	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (DialogueRows[index]->DialogueGroupCode == GroupCode)
		{
			if (DialogueRows[index]->DialogueType == 1)
			{
				SetCurrentRow(index - 1);
				break;
			}
		}
	}
}

bool UDialogueTableComponent::isRedefineNeededLine(FString RowName) {
	bool isRedefineNeeded = false;

	for (int index = 0; index < DialogueRows.Num(); index++)
	{
		if (RowName == "AfterBattleFail_Hubworld_2")
		{
			isRedefineNeeded = true;
			break;
		}
	}
	return isRedefineNeeded;
}