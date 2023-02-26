// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBattleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBossBattleSystemComponent::UBossBattleSystemComponent()
{
	BossSkillList.Add("SweptGarden");
}

void UBossBattleSystemComponent::SpawnRandomSkill() {
}
