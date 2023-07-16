// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"

// Sets default values
ABattleManager::ABattleManager()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	CurrentTurnType = BossTurn;
	LeftCurrentTurnTime = 0;

	static ConstructorHelpers::FClassFinder<AActor> BP_PS_AmbiguousEmotion(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_AmbiguousEmotion"));
	auto AmbiguousEmotion_Ref = BP_PS_AmbiguousEmotion.Class;
}

void ABattleManager::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManager = GameInstance->GetSubsystem<UBattleManagerSystem>();

}

void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunTurnTimer(DeltaTime);
}

void ABattleManager::StartBossTurn() {
	NTLOG_S(Warning);
	SetLeftCurrentTurnTime(10);
	BP_StartBossTurn();
}

/* �ش� �޼���� ���� �������Ʈ ��� �ʱ�ȭ ȣ�� Ÿ�̹� ���� ���� ���� ���� 1ȸ�� ���� �����մϴ�.������ Turn ���� ������ ���� C++ Ŭ���� �������� �̷�����ϴ�. */
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
	SetLeftCurrentTurnTime(10);
	BP_StartPeppyTurn();
}

void ABattleManager::TurnChange() {
	switch (CurrentTurnType) {
	case BossTurn:
		StartPeppyTurn();
		CurrentTurnType = PeppySkillSelectingTurn;
		break;
	case PeppySkillSelectingTurn:
		SetLeftCurrentTurnTime(100);	// ��ų ����� ���� �ӽ� �� Ÿ�� ����
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

float ABattleManager::GetLeftCurrentTurnTime() {
	return LeftCurrentTurnTime;
}

void ABattleManager::SetLeftCurrentTurnTime(float TurnTime) {
	LeftCurrentTurnTime = TurnTime;
}

void ABattleManager::EndTurn() {
	LeftCurrentTurnTime = 0;
}