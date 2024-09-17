// Fill out your copyright notice in the Description page of Project Settings.


#include "KNOCKturneGameState.h"
#include "GameInstance/BattleManagerSystem.h"
#include "Containers/Array.h"
#include "KNOCKturneSaveGame.h"

void AKNOCKturneGameState::HandleBeginPlay() {
	Super::HandleBeginPlay();

	BattleManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBattleManagerSystem>();
	BattleManagerSystem->LoadGameState(this);
}

AKNOCKturneGameState::AKNOCKturneGameState() {
	SaveSlotName = TEXT("KNOCKturne");
	UserIndex = 0;
}

void AKNOCKturneGameState::LoadKNOCKturneData(){
	UKNOCKturneSaveGame* KNOCKturneSaveGame = Cast<UKNOCKturneSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (KNOCKturneSaveGame == nullptr) {
		KNOCKturneSaveGame = GetMutableDefault<UKNOCKturneSaveGame>();
	}

	BattleManagerSystem->isPrologue = KNOCKturneSaveGame->isPrologue;
	BattleManagerSystem->isSkippedBeforeBattleSequence = KNOCKturneSaveGame->isSkippedBeforeBattleSequence;
	BattleManagerSystem->CanSkipBeforeBattleSequence = KNOCKturneSaveGame->CanSkipBeforeBattleSequence;
	BattleManagerSystem->DreamFragmentCount = KNOCKturneSaveGame->DreamFragmentCount;
	BattleManagerSystem->DreamDiaryOpenRow = KNOCKturneSaveGame->DreamDiaryOpenRow;
	BattleManagerSystem->GetDreamFragment = KNOCKturneSaveGame->GetDreamFragment;
	BattleManagerSystem->isDreamDiaryUpdated = KNOCKturneSaveGame->isDreamDiaryUpdated;
	BattleManagerSystem->isBattleFail = KNOCKturneSaveGame->isBattleFail;
	BattleManagerSystem->RightafterBattleClear = KNOCKturneSaveGame->RightafterBattleClear;
	BattleManagerSystem->ItemCountList = KNOCKturneSaveGame->ItemCountList;
	BattleManagerSystem->TryBattleCount = KNOCKturneSaveGame->TryBattleCount;
	BattleManagerSystem->TotalPlayTime = KNOCKturneSaveGame->TotalPlayTime;
	BattleManagerSystem->BattleClearTime = KNOCKturneSaveGame->BattleClearTime;
	BattleManagerSystem->isAfterCredit = KNOCKturneSaveGame->isAfterCredit;
	BattleManagerSystem->SelectedSkillCodeList = KNOCKturneSaveGame->SelectedSkillCodeList;
	BattleManagerSystem->FinalSpecialSkill = KNOCKturneSaveGame->FinalSpecialSkill;
	BattleManagerSystem->FinalItem = KNOCKturneSaveGame->FinalItem;
	BattleManagerSystem->isNpcGiveDreamFragment = KNOCKturneSaveGame->isNpcGiveDreamFragment;
	BattleManagerSystem->NpcNormalTalkCount = KNOCKturneSaveGame->NpcNormalTalkCount;
}

void AKNOCKturneGameState::SaveKNOCKturneData()
{
	UKNOCKturneSaveGame* NewKNOCKturneData = NewObject<UKNOCKturneSaveGame>();
	NewKNOCKturneData->isPrologue = BattleManagerSystem->isPrologue;
	NewKNOCKturneData->isSkippedBeforeBattleSequence = BattleManagerSystem->isSkippedBeforeBattleSequence;
	NewKNOCKturneData->CanSkipBeforeBattleSequence = BattleManagerSystem->CanSkipBeforeBattleSequence;
	NewKNOCKturneData->DreamFragmentCount = BattleManagerSystem->DreamFragmentCount;
	NewKNOCKturneData->DreamDiaryOpenRow = BattleManagerSystem->DreamDiaryOpenRow;
	NewKNOCKturneData->GetDreamFragment = BattleManagerSystem->GetDreamFragment;
	NewKNOCKturneData->isDreamDiaryUpdated = BattleManagerSystem->isDreamDiaryUpdated;
	NewKNOCKturneData->isBattleFail = BattleManagerSystem->isBattleFail;
	NewKNOCKturneData->RightafterBattleClear = BattleManagerSystem->RightafterBattleClear;
	NewKNOCKturneData->ItemCountList = BattleManagerSystem->ItemCountList;
	NewKNOCKturneData->TryBattleCount = BattleManagerSystem->TryBattleCount;
	NewKNOCKturneData->TotalPlayTime = BattleManagerSystem->TotalPlayTime;
	NewKNOCKturneData->BattleClearTime = BattleManagerSystem->BattleClearTime;
	NewKNOCKturneData->isAfterCredit = BattleManagerSystem->isAfterCredit;
	NewKNOCKturneData->SelectedSkillCodeList = BattleManagerSystem->SelectedSkillCodeList;
	NewKNOCKturneData->FinalSpecialSkill = BattleManagerSystem->FinalSpecialSkill;
	NewKNOCKturneData->FinalItem = BattleManagerSystem->FinalItem;
	NewKNOCKturneData->isNpcGiveDreamFragment = BattleManagerSystem->isNpcGiveDreamFragment;
	NewKNOCKturneData->NpcNormalTalkCount = BattleManagerSystem->NpcNormalTalkCount;

	if (!UGameplayStatics::SaveGameToSlot(NewKNOCKturneData, SaveSlotName, UserIndex)) {
		NTLOG(Error, TEXT("SaveGame Error!"));
	}

	FDateTime SaveTime = FDateTime::Now();
	BattleManagerSystem->TotalPlayTime += SaveTime - BattleManagerSystem->StartPlayTime;
	BattleManagerSystem->StartPlayTime = FDateTime::Now();
}

bool AKNOCKturneGameState::IsSaveDataExist()
{
	UKNOCKturneSaveGame* KNOCKturneSaveGame = Cast<UKNOCKturneSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (KNOCKturneSaveGame == nullptr) {
		return false;
	}
	else {
		return true;
	}
}
