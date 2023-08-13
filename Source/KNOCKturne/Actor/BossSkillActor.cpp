// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "Engine/DataTable.h"
#include "GameInstance/KNOCKturneGameInstance.h"

#define SKILL_DESTROTY_TIME 1

ABossSkillActor::ABossSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;
	IsContactSkill = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ActorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ActorPivot"));
	ActorPivot->SetupAttachment(RootComponent);

	SkillMeshPivot = CreateDefaultSubobject<USceneComponent>(TEXT("SkillMeshPivot"));
	SkillMeshPivot->SetupAttachment(ActorPivot);
	SkillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkillMesh"));
	SkillMesh->SetupAttachment(SkillMeshPivot);

	AttackRange = CreateDefaultSubobject<UWidgetComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(ActorPivot);
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
			TempDelayTime = SkillData.SkillDelayTime;

			CurrentStep = ESkillActorLifeCycleStep::CastTime;
			AttackRange->DestroyComponent();
			BattleManagerSystem->CurBossSkillHitArea.Remove(AttackRange);
		}
		break;
	case ESkillActorLifeCycleStep::CastTime:
		if (CurrentLifeTime >= SkillData.SkillDelayTime + SkillData.SkillCastTime) {
			CurrentStep = ESkillActorLifeCycleStep::DestroyTime;
		}
		break;
	case ESkillActorLifeCycleStep::DestroyTime:
		if (CurrentLifeTime >= SkillData.SkillDelayTime + SkillData.SkillCastTime + SKILL_DESTROTY_TIME) {
			BattleManager->SkillActorsOnField.Remove(this->GetFName().ToString());
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

	auto TempSkillData = BattleTableManagerSystem->BossContactSkillTable->FindRow<FBossSkillData>(GetCurrentBlueprintClassName(), TEXT(""));
	if (TempSkillData == nullptr) {
		TempSkillData = BattleTableManagerSystem->BossNonContactSkillTable->FindRow<FBossSkillData>(GetCurrentBlueprintClassName(), TEXT(""));
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

void ABossSkillActor::AttackPlayer() {
	NTLOG(Warning, TEXT("%lf"), SkillData.Value_1_N);
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));

	BattleTableManagerSystem->UseBossSkill(SkillData, this);
}

FVector ABossSkillActor::GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaSeconds) {
	return FMath::Lerp<FVector>(StartPosition, EndPosition, DeltaSeconds / Duration) - StartPosition;
}

bool ABossSkillActor::DelayWithDeltaTime(float DelayTime, float DeltaSeconds) {
	if (TempDelayTime > DelayTime) {
		TempDelayTime = 0;

		return true;
	}
	TempDelayTime += DeltaSeconds;

	return false;
}