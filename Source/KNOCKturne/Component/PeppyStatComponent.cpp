// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/KNOCKturneGameInstance.h"
#include "Actor/Peppy.h"
#include "GameMode/NTBattleGameMode.h"

#include "Kismet/GameplayStatics.h"

UPeppyStatComponent::UPeppyStatComponent()
{
	bWantsInitializeComponent = true;
	PeppyActor = Cast<APeppy>(GetOwner());

}


void UPeppyStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPeppyStatComponent::InitializeComponent() {
	Super::InitializeComponent();
	SetDefaultStat();
}

void UPeppyStatComponent::SetDefaultStat() {
	auto KNOCKturneGameInstance = Cast<UKNOCKturneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NTCHECK(KNOCKturneGameInstance != nullptr);
	BattleTableManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleTableManagerSystem>();
	NTCHECK(BattleTableManagerSystem != nullptr);
	BattleManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleManagerSystem>();
	NTCHECK(BattleManagerSystem != nullptr);

	CurStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Init");
	MinStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Min");
	MaxStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Max");
}

void UPeppyStatComponent::GetDamaged(float Value) {
	if (CanBeDamaged) {
		TryUpdateCurStatData(FStatType::EP, -Value);
	}
}

bool UPeppyStatComponent::TryUpdateCurStatData(FStatType StatType, float Value) {
	switch (StatType) {
	case FStatType::EP:
		CurStatData.EP = FMath::Clamp<int32>(CurStatData.EP + Value, 0, CurStatData.MaxEP);
		if (CurStatData.EP <= 0) {
			CurStatData.EP = 0;

			BattleGameMode->GameOver();
		}
		break;
	case FStatType::Energy:
		CurStatData.Energy = FMath::Clamp<int32>(CurStatData.Energy + Value, 0, CurStatData.MaxEnergy);
		break;
	default:
		NTLOG(Error, TEXT("PeppyStatType is invalid!"));
		return false;
	}
	return true;
}