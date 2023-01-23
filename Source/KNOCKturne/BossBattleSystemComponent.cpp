// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBattleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBossBattleSystemComponent::UBossBattleSystemComponent()
{
	BattleTableComponent = CreateDefaultSubobject<UBattleTableComponent>(TEXT("BATTLE_TABLE_COMPONENT"));
}

void UBossBattleSystemComponent::SpawnRandomSkill() {
}