// Fill out your copyright notice in the Description page of Project Settings.


#include "BossStatComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/KNOCKturneGameInstance.h"
#include "Actor/Boss.h"
#include "GameMode/NTBattleGameMode.h"

UBossStatComponent::UBossStatComponent()
{
}

void UBossStatComponent::InitializeComponent() {
	Super::InitializeComponent();

	BossActor = Cast<ABoss>(GetOwner());
	NTCHECK(BossActor != nullptr);
	SetDefaultStat();
}

// Called when the game starts
void UBossStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UBossStatComponent::SetDefaultStat() {
	auto KNOCKturneGameInstance = Cast<UKNOCKturneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NTCHECK(KNOCKturneGameInstance != nullptr);
	BattleTableManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleTableManagerSystem>();
	NTCHECK(BattleTableManagerSystem != nullptr);

	CurStatData = BattleTableManagerSystem->GetBossStatDataOnTable("Init");
	MinStatData = BattleTableManagerSystem->GetBossStatDataOnTable("Min");
	MaxStatData = BattleTableManagerSystem->GetBossStatDataOnTable("Max");
}

bool UBossStatComponent::TryUpdateCurStatData(FStatType StatType, float Value) {
	switch (StatType) {
	case FStatType::EP:
		CurStatData.EP = FMath::Clamp<int32>(CurStatData.EP + Value, 0, CurStatData.MaxEP);
		if (CurStatData.EP <= 0) {
			CurStatData.EP = 0;
			// 턴이 끝난 후 Die 처리를 하기 위해 Flag만 설정하고 BattleManager의 TurnChange()에서 실제 Die 메서드를 호출함.
			BossActor->IsDie = true;
		}
		break;
	default:
		NTLOG(Error, TEXT("PeppyStatType is invalid!"));
		return false;
	}
	return true;
}