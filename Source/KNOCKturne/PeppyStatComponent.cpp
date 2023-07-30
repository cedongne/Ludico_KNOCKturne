// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatComponent.h"
#include "BattleTableManagerSystem.h"
#include "KNOCKturneGameInstance.h"

#include "Kismet/GameplayStatics.h"

UPeppyStatComponent::UPeppyStatComponent()
{
	bWantsInitializeComponent = true;
	CurrentEP = 0;
}


void UPeppyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDefaultStat();
	
}

void UPeppyStatComponent::InitializeComponent() {
	Super::InitializeComponent();
}

void UPeppyStatComponent::SetDefaultStat() {
	auto KNOCKturneGameInstance = Cast<UKNOCKturneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NTCHECK(KNOCKturneGameInstance != nullptr);
	BattleTableManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleTableManagerSystem>();
	NTCHECK(BattleTableManagerSystem != nullptr);
	
	CurStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Init");
	MinStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Min");
	MaxStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Max");

	MaxEP = CurStatData.MaxEP;
	CurrentEP = CurStatData.MaxEP;
	MaxEnergy = CurStatData.MaxEnergy;
	CurrentEnergy = CurStatData.MaxEnergy;
	SlidingCooldown = CurStatData.SlidingCooldown;
	LeftSlidingCooltime = CurStatData.SlidingCooldown;
	DefenseDamage = CurStatData.DefenseDamage;
}

void UPeppyStatComponent::GetDamaged(float Value) {
	CurrentEP = FMath::Clamp<float>(CurrentEP - Value, MinStatData.MaxEP, MaxStatData.MaxEP);
	if (CurrentEP == MinStatData.MaxEP) {
		OnHPIsZero.Broadcast();
	}
	NTLOG(Warning, TEXT("Spend HP %lf"), Value);
}

void UPeppyStatComponent::Heal(float Value) {
	CurrentEP = FMath::Clamp<float>(CurrentEP + Value, MinStatData.MaxEP, MaxStatData.MaxEP);
	NTLOG(Warning, TEXT("Gain HP %lf"), Value);
}

void UPeppyStatComponent::GainEnergy(float Value) {
	BattleTableManagerSystem->CurPeppyStat.Energy = FMath::Clamp<float>(BattleTableManagerSystem->CurPeppyStat.Energy + Value, MinStatData.Energy, MaxStatData.Energy);
	NTLOG(Warning, TEXT("Gain energy %lf"), Value);
}

void UPeppyStatComponent::SpendEnergy(float Value) {
	CurrentEP = FMath::Clamp<float>(CurrentEP - Value, MinStatData.MaxEP, MaxStatData.MaxEP);
	NTLOG(Warning, TEXT("Spend energy %lf"), Value);
}

int32 UPeppyStatComponent::GetCurrentEP() {
	return CurrentEP;
}

void UPeppyStatComponent::ChangeCurrentEP(int32 Value) {
	CurrentEP += Value;
}