// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "Engine/DataTable.h"
#include "KNOCKturneGameInstance.h"

#define SKILL_DESTROTY_TIME 1

ABossSkillActor::ABossSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;
	IsContactSkill = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	SkillActor = CreateDefaultSubobject<USceneComponent>(TEXT("ActorPivot"));
	SkillActor->SetupAttachment(DefaultSceneRoot);

	MeshPivot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPivot"));
	MeshPivot->SetupAttachment(SkillActor);

	AttackRange = CreateDefaultSubobject<UWidgetComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(SkillActor);
}

void ABossSkillActor::BeginPlay() {
	Super::BeginPlay();

	Initialize();
}

void ABossSkillActor::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	EvaluateCurrentLifeCycleStep(DeltaSeconds);
}

void ABossSkillActor::EvaluateCurrentLifeCycleStep(float DeltaSeconds) {
	DeltaTime = DeltaSeconds;
	CurrentLifeTime += DeltaSeconds;

	switch (CurrentStep)
	{
	case ESkillActorLifeCycleStep::DelayTime:
		if (CurrentLifeTime >= SkillData.SkillDelayTime) {
			CurrentStep = ESkillActorLifeCycleStep::CastTime;
			AttackRange->DestroyComponent();
			BattleManager->CurBossSkillHitArea.Remove(AttackRange);
		}
		break;
	case ESkillActorLifeCycleStep::CastTime:
		if (CurrentLifeTime >= SkillData.SkillDelayTime + SkillData.SkillCastTime) {
			CurrentStep = ESkillActorLifeCycleStep::DestroyTime;
		}
		break;
	case ESkillActorLifeCycleStep::DestroyTime:
		if (CurrentLifeTime >= SkillData.SkillDelayTime + SkillData.SkillCastTime + SKILL_DESTROTY_TIME) {
			Destroy();
		}
		break;
	default:
		NTLOG(Warning, TEXT("SkillActorLifeCycleStep enum is invalid!"));
	}
}

void ABossSkillActor::Initialize() {
	InitSkillData();
}

void ABossSkillActor::InitSkillData() {
	if (IsInitialized) {
		return;
	}

	auto TempSkillData = BattleTableManager->BossContactSkillTable->FindRow<FBossSkillData>(GetCurrentBlueprintClassName(), TEXT(""));
	if (TempSkillData == nullptr) {
		TempSkillData = BattleTableManager->BossNonContactSkillTable->FindRow<FBossSkillData>(GetCurrentBlueprintClassName(), TEXT(""));
		IsContactSkill = false;
	}

	if (TempSkillData == nullptr) {
		NTLOG(Error, TEXT("Can't find %s on BossSkillTable"), *(GetClass()->GetName()));
		Destroy();
	}
	else {
		SkillData = *TempSkillData;
		IsInitialized = true;
	}
}

FBossSkillData ABossSkillActor::GetSkillData() {
	if (!IsInitialized) {
		InitSkillData();
	}
	return SkillData;
}
void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	NTLOG(Warning, TEXT("Data set %lf"), SkillData.Value_1_N);
}

void ABossSkillActor::HitPlayer() {
	NTLOG(Warning, TEXT("%lf"), SkillData.Value_1_N);
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));

	BattleTableManager->UseBossSkill(SkillData);
}

FVector ABossSkillActor::GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float _DeltaTime) {
	return FMath::Lerp<FVector>(StartPosition, EndPosition, _DeltaTime / Duration) - StartPosition;
}