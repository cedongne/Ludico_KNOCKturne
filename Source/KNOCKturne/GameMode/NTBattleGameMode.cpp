// Fill out your copyright notice in the Description page of Project Settings.


#include "NTBattleGameMode.h"
#include "Actor/BattleManager.h"
#include "GameInstance/BattleManagerSystem.h"

ANTBattleGameMode::ANTBattleGameMode() {
	static ConstructorHelpers::FClassFinder<ABattleManager> BP_BattleManagerPath(TEXT("/Game/Blueprints/Actors/Battle/BP_BattleManager"));
	BP_BattleManagerClass = BP_BattleManagerPath.Class;
}

void ANTBattleGameMode::InitGame(const FString& MapName, const FString& Option, FString& ErrorMessage) {
	Super::InitGame(MapName, Option, ErrorMessage);

	BattleManager = GetWorld()->SpawnActor<ABattleManager>(BP_BattleManagerClass);
}

void ANTBattleGameMode::GameOver() {
	BattleManager->GetPeppyActor()->Die();
	GetDreamFragment();
	EndBattle();
}

void ANTBattleGameMode::GameClear() {
	BattleManager->GetBossActor()->Die();
	GetDreamFragment();
	EndBattle();
}

void ANTBattleGameMode::EndBattle() {
	BattleManager->GetPeppyActor()->SetImmobile();
	BattleManager->SetActorTickEnabled(false);
}

void ANTBattleGameMode::GetDreamFragment() {
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	float ReducedEP = BattleManagerSystem->LastRoundBossHpRatio;
	KNOCKturneGameState->DreamFragmentCount += 1;
	if (ReducedEP >= 80) {
		KNOCKturneGameState->DreamFragmentCount += 1;
	}

	if (KNOCKturneGameState == nullptr) {
		NTLOG(Warning, TEXT("%d"), ReducedEP);
	}
	// NTLOG(Warning, TEXT("%d"), ReducedEP);
}