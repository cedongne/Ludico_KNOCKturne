// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBattleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

FBossSkillSpawningData::FBossSkillSpawningData(UClass* _SkillObjectClass, TArray<FVector> _SkillTransform) {
	SkillObjectClass = _SkillObjectClass;
	SkillTransform = _SkillTransform;
}

// Sets default values for this component's properties
UBossBattleSystemComponent::UBossBattleSystemComponent()
{
	BossSkillList.Add("SweptGarden");
	new FBossSkillSpawningData(
		Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, TEXT("/Game/Blueprints/Skills/Boss/Ep1/BP_SweptGarden2.BP_SweptGarden2_C"))),
		*(new TArray<FVector>(Initializerli))
	);
	BossSkillMap.Add("SweptGarden", NewObject<FBossSkillSpawningData>(GetTransientPackage(), 
		Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, TEXT("/Game/Blueprints/Skills/Boss/Ep1/BP_SweptGarden2.BP_SweptGarden2_C")), new FVector(0, 0, 0) ))));
	NTLOG(Warning, TEXT("%d"), BossSkillList.Num());
}

void UBossBattleSystemComponent::SpawnRandomSkill() {
}

void UBossBattleSystemComponent::BeginPlay() {
	Super::BeginPlay();

	BossSkillList.Add("SweptGarden");
	BossSkillMap.Add("SweptGarden", Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, TEXT("/Game/Blueprints/Skills/Boss/Ep1/BP_SweptGarden2.BP_SweptGarden2_C"))));
}