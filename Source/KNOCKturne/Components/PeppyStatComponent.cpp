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
	CurrentStatData = PeppyStatDataInstance->GetPeppyStatData("Init");
	if (CurrentStatData != nullptr) {
		NTLOG(Warning, TEXT("%d %d"), CurrentStatData->MaxHP, CurrentStatData->MaxEP);
	}

	MaxHP = CurrentStatData->MaxHP;
	CurrentHP = CurrentStatData->MaxHP;
	MaxEP = CurrentStatData->MaxEP;
	CurrentEP = CurrentStatData->MaxEP;
	SlidingCooldown = CurrentStatData->SlidingCooldown;
	LeftSlidingCooltime = CurrentStatData->SlidingCooldown;
	DamageDecrease = CurrentStatData->DamageDecrease;
}

void UPeppyStatComponent::GetDamaged(float Damage) {
	NTCHECK(CurrentStatData != nullptr);
	CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, CurrentStatData->MaxHP);
	if (CurrentHP < 0.0f) {
		OnHPIsZero.Broadcast();
	}

}
