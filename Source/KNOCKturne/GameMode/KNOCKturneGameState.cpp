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
	BattleManagerSystem->DreamFragmentCount = KNOCKturneSaveGame->DreamFragmentCount;
	BattleManagerSystem->DreamDiaryOpenRow = KNOCKturneSaveGame->DreamDiaryOpenRow;
	BattleManagerSystem->GetDreamFragment = KNOCKturneSaveGame->GetDreamFragment;
	BattleManagerSystem->isDreamDiaryUpdated = KNOCKturneSaveGame->isDreamDiaryUpdated;
	BattleManagerSystem->isBattleFail = KNOCKturneSaveGame->isBattleFail;
	BattleManagerSystem->RightafterBattleClear = KNOCKturneSaveGame->RightafterBattleClear;
	BattleManagerSystem->ItemCountList = KNOCKturneSaveGame->ItemCountList;
}

void AKNOCKturneGameState::SaveKNOCKturneData()
{
	UKNOCKturneSaveGame* NewKNOCKturneData = NewObject<UKNOCKturneSaveGame>();
	NewKNOCKturneData->isPrologue = BattleManagerSystem->isPrologue;
	NewKNOCKturneData->DreamFragmentCount = BattleManagerSystem->DreamFragmentCount;
	NewKNOCKturneData->DreamDiaryOpenRow = BattleManagerSystem->DreamDiaryOpenRow;
	NewKNOCKturneData->GetDreamFragment = BattleManagerSystem->GetDreamFragment;
	NewKNOCKturneData->isDreamDiaryUpdated = BattleManagerSystem->isDreamDiaryUpdated;
	NewKNOCKturneData->isBattleFail = BattleManagerSystem->isBattleFail;
	NewKNOCKturneData->RightafterBattleClear = BattleManagerSystem->RightafterBattleClear;
	NewKNOCKturneData->ItemCountList = BattleManagerSystem->ItemCountList;

	if (!UGameplayStatics::SaveGameToSlot(NewKNOCKturneData, SaveSlotName, UserIndex)) {
		NTLOG(Error, TEXT("SaveGame Error!"));
	}
}