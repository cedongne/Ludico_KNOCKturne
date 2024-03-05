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
}

void AKNOCKturneGameState::LoadKNOCKturneData(){
	auto KNOCKturneSaveGame = Cast<UKNOCKturneSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (KNOCKturneSaveGame == nullptr) {
		KNOCKturneSaveGame = GetMutableDefault<UKNOCKturneSaveGame>();
	}

	isPrologue = KNOCKturneSaveGame->isPrologue;
	DreamFragmentCount = KNOCKturneSaveGame->DreamFragmentCount;
	DreamDiaryOpenRow = KNOCKturneSaveGame->DreamDiaryOpenRow;
	GetDreamFragment = KNOCKturneSaveGame->GetDreamFragment;
	isDreamDiaryUpdated = KNOCKturneSaveGame->isDreamDiaryUpdated;
	isBattleFail = KNOCKturneSaveGame->isBattleFail;
	RightafterBattleClear = KNOCKturneSaveGame->RightafterBattleClear;
	ItemCountList = KNOCKturneSaveGame->ItemCountList;
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

	if (!UGameplayStatics::SaveGameToSlot(NewKNOCKturneData, SaveSlotName, 0)) {
		NTLOG(Error, TEXT("SaveGame Error!"));
	}
}