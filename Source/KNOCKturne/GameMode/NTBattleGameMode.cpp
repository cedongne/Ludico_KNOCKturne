// Fill out your copyright notice in the Description page of Project Settings.


#include "NTBattleGameMode.h"
#include "Actor/BattleManager.h"
#include "GameInstance/BattleManagerSystem.h"
#include "Blueprint/UserWidget.h"

ANTBattleGameMode::ANTBattleGameMode() {
	static ConstructorHelpers::FClassFinder<ABattleManager> BP_BattleManagerPath(TEXT("/Game/Blueprints/Actors/Battle/BP_BattleManager"));
	BP_BattleManagerClass = BP_BattleManagerPath.Class;

	static ConstructorHelpers::FClassFinder<ABoss> BP_BossActorPath(TEXT("/Game/Blueprints/Actors/Battle/NPC/BP_BossRose"));
	BP_BossActorClass = BP_BossActorPath.Class;
}

void ANTBattleGameMode::InitGame(const FString& MapName, const FString& Option, FString& ErrorMessage) {
	Super::InitGame(MapName, Option, ErrorMessage);
	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();
}

void ANTBattleGameMode::RestartPlayer(AController* NewPlayer) {
	Super::RestartPlayer(NewPlayer);

	BattleManager = GetWorld()->SpawnActor<ABattleManager>(BP_BattleManagerClass);
}

void ANTBattleGameMode::GameOver() {
	ActorManagerSystem->PeppyActor->Die();
	ActorManagerSystem->BossActor->ClearUseSkillTimer();
	EndBattle();
}

void ANTBattleGameMode::GameClear() {
	ActorManagerSystem->BossActor->Die();
	EndBattle();
}

void ANTBattleGameMode::SpawnHud() {
	BP_BattleHud = Cast<UUserWidget>(CreateWidget(GetWorld(), BP_BattleHudClass));
	if (BP_BattleHud != nullptr) {
		BP_BattleHud->AddToViewport();
	}
	else {
		NTLOG(Warning, TEXT("BP_BattleHud widget creating is failed!"));
	}
}

void ANTBattleGameMode::EndBattle() {
	ActorManagerSystem->PeppyActor->SetImmobile();
	BattleManager->SetActorTickEnabled(false);
}