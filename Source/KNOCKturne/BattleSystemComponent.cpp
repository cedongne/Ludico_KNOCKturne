// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystemComponent.h"

// Sets default values for this component's properties
UBattleSystemComponent::UBattleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	LeftCurrentTurnTime = 0;
	IsBossTurn = true;
}


// Called when the game starts
void UBattleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManager = GameInstance->GetSubsystem<UBattleManagerSystem>();

	StartBossTurn();
}

void UBattleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RunTurnTimer(DeltaTime);
}


void UBattleSystemComponent::StartBossTurn() {
	SetTurnTime(BattleTableManager->CurBossStat.Turn);
}

void UBattleSystemComponent::StartPeppyTurn() {
	SetTurnTime(BattleTableManager->CurPeppyStat.Turn);
}


void UBattleSystemComponent::TurnChange() {
	if (IsBossTurn) {
		StartPeppyTurn();
	}
	else {
		StartBossTurn();
	}
}

void UBattleSystemComponent::SetTurnTime(int32 TurnTime) {
	LeftCurrentTurnTime = TurnTime;
}
void UBattleSystemComponent::RunTurnTimer(float DeltaTime) {
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
void UBattleSystemComponent::DecreaseLeftCurrentTurnTime() {
	NTLOG(Warning, TEXT("Left Time : %d"), LeftCurrentTurnTime);
	if (LeftCurrentTurnTime >= 0) {
		LeftCurrentTurnTime--;
		BattleManager->LeftCurTurnTime = LeftCurrentTurnTime;
	}
}