// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBattleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBossBattleSystemComponent::UBossBattleSystemComponent()
{
	BossSkillList.Add("SweptGarden");
	NTLOG(Warning, TEXT("%d"), BossSkillList.Num());
}

void UBossBattleSystemComponent::SpawnRandomSkill() {
}

void UBossBattleSystemComponent::BeginPlay() {
	Super::BeginPlay();

	BossSkillList.Add("SweptGarden");
}