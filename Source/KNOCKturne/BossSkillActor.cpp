// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "Engine/DataTable.h"
#include "BattleTableManagerSystem.h"
#include "KNOCKturneGameInstance.h"

// Sets default values
ABossSkillActor::ABossSkillActor()
{
	IsContactSkill = true;
}

void ABossSkillActor::BeginPlay() {
	Super::BeginPlay();

	Initialization();
}

void ABossSkillActor::Initialization() {
	auto TempSkillData = BattleTableManager->BossContarctSkillTable->FindRow<FBossSkillData>(GetCurrentBlueprintClassName(), TEXT(""));
	if (TempSkillData == nullptr) {
		TempSkillData = BattleTableManager->BossNonContarctSkillTable->FindRow<FBossSkillData>(GetCurrentBlueprintClassName(), TEXT(""));
		IsContactSkill = false;
	}

	InitSkillData(*TempSkillData);
}

void ABossSkillActor::InitSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	IsInitialized = true;
}

void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	NTLOG(Warning, TEXT("Data set %lf"), SkillData.Value_1_N);
}

void ABossSkillActor::SetSkillDataWithName(FString SkillName) {
//	FBossSkillData* SkillDataPtr = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*SkillName, TEXT(""));
	IsInitialized = true;
}
void ABossSkillActor::HitPlayer() {
	NTLOG(Warning, TEXT("%lf"), SkillData.Value_1_N);
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));

	BattleTableManager->UseBossSkill(SkillData);
}

FVector ABossSkillActor::GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaTime) {
	return FMath::Lerp<FVector>(StartPosition, EndPosition, DeltaTime / Duration) - StartPosition;
}