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
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	NTLOG_S(Error);
}

void ANTBattleGameMode::GameOver() {
	BattleManager->GetPeppyActor()->Die();
	GetDreamFragment();
	EndBattle();
}

void ANTBattleGameMode::GameClear() {
	BattleManager->GetBossActor()->Die();
	EndBattle();
	KNOCKturneGameState->DreamFragmentCount += 1;
}

void ANTBattleGameMode::EndBattle() {
	BattleManager->SetActorTickEnabled(false);
	BattleManager->EndBattle();
}

void ANTBattleGameMode::GetDreamFragment() {
	float ReducedEP = 1 - (BattleManager->GetBossActor()->StatComponent->CurStatData.EP * 100);

	if (ReducedEP >= 80) {
		KNOCKturneGameState->DreamFragmentCount += 1;
	}
}