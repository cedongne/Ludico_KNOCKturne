// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatComponent.h"
#include "BattleTableManagerSystem.h"
#include "KNOCKturneGameInstance.h"

#include "Peppy.h"

#include "Kismet/GameplayStatics.h"

UPeppyStatComponent::UPeppyStatComponent()
{
	bWantsInitializeComponent = true;
}


void UPeppyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDefaultStat();
	PeppyActor = Cast<APeppy>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UPeppyStatComponent::InitializeComponent() {
	Super::InitializeComponent();
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

bool UPeppyStatComponent::TryUpdateCurStatData(PeppyStatType StatType, float Value) {
	switch (StatType) {
	case PeppyStatType::EP:
		CurStatData.EP = FMath::Clamp<float>(CurStatData.EP - Value, 0, CurStatData.MaxEP);
		if (CurStatData.EP == 0) {
			PeppyActor->Die();
		}
		break;
	case PeppyStatType::Energy:
		CurStatData.Energy = FMath::Clamp<float>(CurStatData.Energy - Value, 0, CurStatData.MaxEnergy);
		break;
	default:
		NTLOG(Error, TEXT("PeppyStatType is invalid!"));
		return false;
	}
	return true;
}