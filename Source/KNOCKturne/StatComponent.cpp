// Fill out your copyright notice in the Description page of Project Settings.
#include "StatComponent.h"
#include "NTBattleGameMode.h"

UStatComponent::UStatComponent()
{
	BattleGameMode = Cast<ANTBattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	NTCHECK(BattleGameMode != nullptr);
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

AActor* UStatComponent::GetOwnerActor(AActor* OwnerActor) {
	return OwnerActor;
}

bool UStatComponent::TryUpdateCurStatData(FStatType StatType, float Value) {
	NTLOG(Warning, TEXT("TryUpdateCurStatData() method must be override!"));
	return false;
}