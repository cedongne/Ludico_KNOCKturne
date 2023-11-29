// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "Engine/DataTable.h"
#include "GameInstance/KNOCKturneGameInstance.h"

#define SKILL_DESTROTY_TIME 1

ABossSkillActor::ABossSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetActorTickEnabled(false);
	IsContactSkill = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ActorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ActorPivot"));
	ActorPivot->SetupAttachment(RootComponent);

	SkillMeshPivot = CreateDefaultSubobject<USceneComponent>(TEXT("SkillMeshPivot"));
	SkillMeshPivot->SetupAttachment(ActorPivot);
	SkillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkillMesh"));
	SkillMesh->SetupAttachment(SkillMeshPivot);
	SkillMesh->bHiddenInGame = true;

	AttackRange = CreateDefaultSubobject<UWidgetComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(ActorPivot);
}

void ABossSkillActor::BeginPlay() {
	Super::BeginPlay();
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
			auto owner = Cast<class ABoss>(GetOwner());
			if (owner != nullptr) {
				NTLOG(Warning, TEXT("%s's owner is %s"), *GetName(), *(owner->GetName()));
//				owner->UseSkill();
			}
			Destroy();
		}
		break;
	default:
		NTLOG(Warning, TEXT("SkillActorLifeCycleStep enum is invalid!"));
	}
}

void ABossSkillActor::Initialize() {
	Super::Initialize();
	InitSkillData();

	ActivateActorTickAfterDelay(ShowAttackRangeTime_PreSpawnActor);
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
		ShowAttackRangeTime_PreSpawnActor = ShowAttackRangeTime_Total - SkillData.SkillDelayTime;
	}
}

void ABossSkillActor::ActivateActorTickAfterDelay(float DelayTime) {
	GetWorld()->GetTimerManager().SetTimer(
		ActivateActorTickTimerHandler,
		this,
		&ABossSkillActor::ActivateActorTick,
		DelayTime,
		false);
}

void ABossSkillActor::ActivateActorTick() {
	SkillMesh->bHiddenInGame = false;
	SetActorTickEnabled(true);
}

FBossSkillData ABossSkillActor::GetSkillData() {
	if (!IsInitialized) {
		Initialize();
	}
	return SkillData;
}
void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
}

bool ABossSkillActor::TryOperateSkillEffect(ESkillUsingType SkillUsingType) {
	switch (SkillUsingType) {
	case ESkillUsingType::Sequential:
		return BattleTableManagerSystem->TryUseBossSkillSequential(SkillData, this);
	case ESkillUsingType::Probabilistic:
		return BattleTableManagerSystem->TryUseBossSkillProbabilistic(SkillData, this);
	}

	return false;
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

void ABossSkillActor::EndCurBossSkill()
{
	CurrentStep = ESkillActorLifeCycleStep::DestroyTime;
}
