// Fill out your copyright notice in the Description page of Project Settings.


#include "NTBattleGameMode.h"
#include "Actor/BattleManager.h"

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
	EndBattle();
}

void ANTBattleGameMode::GameClear() {
	BattleManager->GetBossActor()->Die();
	EndBattle();
}

void ANTBattleGameMode::EndBattle() {
	BattleManager->GetPeppyActor()->SetImmobile();
	BattleManager->SetActorTickEnabled(false);
}