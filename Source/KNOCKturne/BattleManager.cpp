// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"

// Sets default values
ABattleManager::ABattleManager()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	LeftCurrentTurnTime = 0;
	IsBossTurn = true;
}

// Called when the game starts or when spawned
void ABattleManager::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManager = GameInstance->GetSubsystem<UBattleManagerSystem>();

}

// Called every frame
void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// SetActorTickEnabled() 메서드가 정상적으로 작동하지 않아 임시로 조건문을 추가해 타이머 작동을 조작함. 수정해야 함.
	if (IsCalled_InitStartBossTurn) {
		RunTurnTimer(DeltaTime);
	}
}

void ABattleManager::StartBossTurn() {
	NTLOG_S(Warning);
//	SetTurnTime(BattleTableManager->GetCurBossStatReadOnly().Turn);
	SetTurnTime(3);
	BP_StartBossTurn();
}

/* 해당 메서드는 레벨 블루프린트 등에서 초기화 호출 타이밍 조절 등을 위해 최초 1회만 실행 가능합니다.이후의 Turn 시작 로직은 오직 C++ 클래스 내에서만 이루어집니다. */
void ABattleManager::BP_InitStartBossTurn() {
	if (IsCalled_InitStartBossTurn) {
		NTLOG(Error, TEXT("StartBossTurn method has already been called. This method can only be called once on blueprint."))
	}
	
//	SetActorTickEnabled(true);
	IsCalled_InitStartBossTurn = true;
	TurnChange();
}

void ABattleManager::StartPeppyTurn() {
//	SetTurnTime(BattleTableManager->GetCurPeppyStatReadOnly().Turn);
	SetTurnTime(10);
	BP_StartPeppyTurn();
}


void ABattleManager::TurnChange() {
	if (IsBossTurn) {
		StartBossTurn();
		IsBossTurn = false;
	}
	else {
		StartPeppyTurn();
		IsBossTurn = true;
	}
}

void ABattleManager::SetTurnTime(int32 TurnTime) {
	LeftCurrentTurnTime = TurnTime;
}
void ABattleManager::RunTurnTimer(float DeltaTime) {
	if (LeftCurrentTurnTime <= 0.0f) {
		TurnChange();
	}
	LeftCurrentTurnTime -= DeltaTime;
	BattleManager->LeftCurTurnTime = LeftCurrentTurnTime;

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
		BattleManager->LeftCurTurnTime = LeftCurrentTurnTime;
	}
}