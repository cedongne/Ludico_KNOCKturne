// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "Engine/DataTable.h"
#include "BattleTableManagerSystem.h"
#include "KNOCKturneGameInstance.h"

// Sets default values
ABossSkillActor::ABossSkillActor()
{
}

void ABossSkillActor::BeginPlay() {
	Super::BeginPlay();

}

void ABossSkillActor::InitSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	IsInitialized = true;
}

void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	IsInitialized = true;
	NTLOG(Warning, TEXT("Data set %lf"), SkillData.Value_1_N);
}

void ABossSkillActor::SetSkillDataWithName(FString SkillName) {
//	FBossSkillData* SkillDataPtr = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*SkillName, TEXT(""));
	IsInitialized = true;
}
void ABossSkillActor::HitPlayer() {
	NTLOG(Warning, TEXT("%lf"), SkillData.Value_1_N);
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));

	BattleTableManager->ApplySkillStatData(SkillData);
}

FVector ABossSkillActor::GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaTime) {
	return FMath::Lerp<FVector>(StartPosition, EndPosition, DeltaTime / Duration) - StartPosition;
}