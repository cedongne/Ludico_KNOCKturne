// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppySkillActor.h"

APeppySkillActor::APeppySkillActor() {
}

void APeppySkillActor::BeginPlay() {
	Super::BeginPlay();

	LoadSkillDataFromDataTable();
	UseSkill();
}

void APeppySkillActor::LoadSkillDataFromDataTable() {
	FString BlueprintClassName = GetClass()->GetFName().ToString();
	SkillData = *(BattleTableManager->GetPeppySkillTable()->FindRow<FPeppySkillData>(*BlueprintClassName, TEXT("Fail to load PeppySkillData")));
}

void APeppySkillActor::UseSkill() {
	BattleTableManager->UsePeppySkill(SkillData);
}