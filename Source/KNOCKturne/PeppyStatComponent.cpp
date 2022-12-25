// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatComponent.h"
#include "KNOCKturneGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPeppyStatComponent::UPeppyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// It makes call InitializeComponent() method
	bWantsInitializeComponent = true;
	CurrentHP = 0;
}


// Called when the game starts
void UPeppyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPeppyStatComponent::InitializeComponent() {
	Super::InitializeComponent();

	SetDefaultStat();
//	NTLOG(Warning, TEXT("%lf"), CurrentHP);
}

void UPeppyStatComponent::SetDefaultStat() {
	auto PeppyStatDataInstance = Cast<UKNOCKturneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NTCHECK(PeppyStatDataInstance != nullptr);
	
	CurStatData = PeppyStatDataInstance->GetPeppyStatData("Init");
	MinStatData = PeppyStatDataInstance->GetPeppyStatData("Min");
	MaxStatData = PeppyStatDataInstance->GetPeppyStatData("Max");

	NTCHECK(CurStatData != nullptr);

	MaxHP = CurStatData->MaxHP;
	CurrentHP = CurStatData->MaxHP;
	MaxEP = CurStatData->MaxEP;
	CurrentEP = CurStatData->MaxEP;
	SlidingCooldown = CurStatData->SlidingCooldown;
	LeftSlidingCooltime = CurStatData->SlidingCooldown;
	DamageDecrease = CurStatData->DamageDecrease;
}

void UPeppyStatComponent::GetDamaged(float Value) {
	NTCHECK(CurStatData != nullptr);
	CurrentHP = FMath::Clamp<float>(CurrentHP - Value, MinStatData->MaxHP, MaxStatData->MaxHP);
	if (CurrentHP == MinStatData->MaxHP) {
		OnHPIsZero.Broadcast();
	}
	NTLOG(Warning, TEXT("Spend HP %lf"), Value);
}

void UPeppyStatComponent::Heal(float Value) {
	NTCHECK(CurStatData != nullptr);
	CurrentHP = FMath::Clamp<float>(CurrentHP + Value, MinStatData->MaxHP, MaxStatData->MaxHP);
	NTLOG(Warning, TEXT("Gain HP %lf"), Value);
}

void UPeppyStatComponent::GainEnergy(float Value) {
	NTCHECK(CurStatData != nullptr);

	CurrentEP = FMath::Clamp<float>(CurrentEP + Value, MinStatData->MaxEP, MaxStatData->MaxEP);
	NTLOG(Warning, TEXT("Gain energy %lf"), Value);
}

void UPeppyStatComponent::SpendEnergy(float Value) {
	NTCHECK(CurStatData != nullptr);

	CurrentEP = FMath::Clamp<float>(CurrentEP - Value, MinStatData->MaxEP, MaxStatData->MaxEP);
	NTLOG(Warning, TEXT("Spend energy %lf"), Value);
}
