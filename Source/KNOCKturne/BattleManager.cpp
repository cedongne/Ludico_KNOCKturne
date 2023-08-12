// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"

#include "Peppy.h"
#include "Boss.h"
#include "PeppyStatComponent.h"
#include "BossStatComponent.h"
#include "BattleTableManagerSystem.h"
#include "BattleManagerSystem.h"

// Sets default values
ABattleManager::ABattleManager()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	CurrentTurnType = BossTurn;
	LeftCurrentTurnTime = 0;

	static ConstructorHelpers::FClassFinder<ABoss> BP_BossActorClass(TEXT("/Game/Blueprints/Actors/Battle/NPC/BP_BossRose"));
	BossActorSubClass = BP_BossActorClass.Class;


//	static ConstructorHelpers::FClassFinder<AActor> BP_PS_AmbiguousEmotion(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_AmbiguousEmotion"));
//	auto AmbiguousEmotion_Ref = BP_PS_AmbiguousEmotion.Class;
}

void ABattleManager::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleTableManagerSystem->BattleManager = this;
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleManagerSystem->BattleManager = this;

	GetActors();
}

void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunTurnTimer(DeltaTime);
}

void ABattleManager::StartBossTurn() {
	NTLOG_S(Warning);

	ProcessDamageBeforeStartTurn();
	SetLeftCurrentTurnTime(BossActor->StatComponent->CurStatData.Turn);
	BP_StartBossTurn();
}

/* 해당 메서드는 레벨 블루프린트 등에서 초기화 호출 타이밍 조절 등을 위해 최초 1회만 실행 가능합니다.이후의 Turn 시작 로직은 오직 C++ 클래스 내에서만 이루어집니다. */
void ABattleManager::BP_InitStartBossTurn() {
	if (IsCalled_InitStartBossTurn) {
		NTLOG(Error, TEXT("StartBossTurn method has already been called. This method can only be called once on blueprint."));
		return;
	}
	
	SetActorTickEnabled(true);
	IsCalled_InitStartBossTurn = true;
	StartBossTurn();
}

void ABattleManager::StartPeppyTurn() {
	SetLeftCurrentTurnTime(PeppyActor->StatComponent->CurStatData.Turn);
	BP_StartPeppyTurn();
}

void ABattleManager::TurnChange() {
	for (auto SkillActor : SkillActorsOnField) {
		SkillActor.Value->Destroy();
	}
	SkillActorsOnField.Empty();

	switch (CurrentTurnType) {
	case BossTurn:
		BattleManagerSystem->UpdateRoundInfo();
		StartPeppyTurn();
		CurrentTurnType = PeppySkillSelectingTurn;
		break;
	case PeppySkillSelectingTurn:
		SetLeftCurrentTurnTime(100);	// 스킬 사용을 위한 임시 턴 타임 적용
		BP_UsePeppySkills();
		CurrentTurnType = PeppySkillUsingTurn;
		break;
	case PeppySkillUsingTurn:
		StartBossTurn();
		CurrentTurnType = BossTurn;
		break;
	}
}

void ABattleManager::RunTurnTimer(float DeltaTime) {
	if (LeftCurrentTurnTime <= 0.0f) {
		TurnChange();
	}
	LeftCurrentTurnTime -= DeltaTime;

	/*
	Timer example

	LeftTurnTimeTimerManager.SetTimer(
		LeftTurnTimeTimer,
		this,
		&UBattleSystemComponent::DecreaseLeftCurrentTurnTime,
		1.0f,
		true,
		(float)CurrentTurnTime
	);
	*/
}
void ABattleManager::DecreaseLeftCurrentTurnTime() {
	NTLOG(Warning, TEXT("Left Time : %d"), LeftCurrentTurnTime);
	if (LeftCurrentTurnTime >= 0) {
		LeftCurrentTurnTime--;
	}
}

void ABattleManager::ProcessDamageBeforeStartTurn() {
	if (GetPeppyActor()->DamageArrayEachTurn.IsEmpty()) {
		return;
	}

	TMap<FString, int32> CurrentTurnDamages = GetPeppyActor()->DamageArrayEachTurn[0];
	GetPeppyActor()->DamageArrayEachTurn.RemoveAt(0);

	int32 TotalDamage = 0;
	for (auto DamageData : CurrentTurnDamages) {
		TotalDamage += DamageData.Value;
	}

	NTLOG(Warning, TEXT("Peppy get damaged starting boss turn %d"), TotalDamage);
	PeppyActor->StatComponent->TryUpdateCurStatData(FStatType::EP, -TotalDamage);
}

float ABattleManager::GetLeftCurrentTurnTime() {
	return LeftCurrentTurnTime;
}

void ABattleManager::SetLeftCurrentTurnTime(float TurnTime) {
	LeftCurrentTurnTime = TurnTime;
}

void ABattleManager::EndTurn() {
	LeftCurrentTurnTime = 0;
}

void ABattleManager::EndBattle() {
	SetActorTickEnabled(false);
	TurnChange();
}

ABoss* ABattleManager::GetBossActor() {
	return (BossActor == nullptr) ? BossActor = Cast<ABoss>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoss::StaticClass())) : BossActor;
}

APeppy* ABattleManager::GetPeppyActor() {
	return (PeppyActor == nullptr) ? PeppyActor = Cast<APeppy>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) : PeppyActor;
}

void ABattleManager::GetActors() {
	BossActor = GetWorld()->SpawnActor<ABoss>(BossActorSubClass, FVector(1600.0f, 760.0f, -850.0f), FRotator(0.0f, 90.0f, 0.0f));
	PeppyActor = Cast<APeppy>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	BossActor->StatComponent->SetDefaultStat();
	PeppyActor->StatComponent->SetDefaultStat();
}