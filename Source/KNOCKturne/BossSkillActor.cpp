// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "PeppyStatComponent.h"
#include "Engine/DataTable.h"
#include "BattleTableManagerSystem.h"

// Sets default values
ABossSkillActor::ABossSkillActor()
{
}

void ABossSkillActor::BeginPlay() {
	Super::BeginPlay();
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();

//	BattleTableManager->BattleTableInitDelegate.AddUFunction(this, FName("InitSkillData"));

//	FBossSkillData* TempSkillData = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*(GetClass()->GetName()), TEXT(""));
//	SkillData = *TempSkillData;	// 포인터 타입의 FBossSkillData 구조체 변수를 값 타입의 FBossSkillData 변수에 포인터 연산으로 저장하는 것이 불가능함.
								// = 연산자의 정의가 되어 있지 않다는 에러.
}

void ABossSkillActor::InitSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	IsInitialized = true;
}

void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	IsInitialized = true;
	NTLOG(Warning, TEXT("Data set"));
}

void ABossSkillActor::SetSkillDataWithName(FString SkillName) {
//	FBossSkillData* SkillDataPtr = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*SkillName, TEXT(""));
	IsInitialized = true;
}
void ABossSkillActor::HitPlayer() {
	NTLOG(Warning, TEXT("%d"), SkillData.Value_1_N);
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
	Peppy->PeppyHit(SkillData.Value_1_N);
}

FVector ABossSkillActor::GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaTime) {
	return FMath::Lerp<FVector>(StartPosition, EndPosition, DeltaTime / Duration) - StartPosition;
}