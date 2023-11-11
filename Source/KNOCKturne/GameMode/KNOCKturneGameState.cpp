// Fill out your copyright notice in the Description page of Project Settings.


#include "KNOCKturneGameState.h"
#include "GameInstance/BattleManagerSystem.h"
#include "Containers/Array.h"

void AKNOCKturneGameState::HandleBeginPlay() {
	Super::HandleBeginPlay();

	auto BattleManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBattleManagerSystem>();
	BattleManagerSystem->LoadGameState(this);
}

AKNOCKturneGameState::AKNOCKturneGameState() {
	ItemCountList.Init(1, 6);
}