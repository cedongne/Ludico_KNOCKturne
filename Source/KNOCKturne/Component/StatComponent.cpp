// Fill out your copyright notice in the Description page of Project Settings.
#include "StatComponent.h"
#include "GameMode/NTBattleGameMode.h"

UStatComponent::UStatComponent()
{
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	BattleGameMode = Cast<ANTBattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	NTCHECK(BattleGameMode != nullptr);
}

void UStatComponent::InitializeComponent() {
	Super::InitializeComponent();
}

AActor* UStatComponent::GetOwnerActor(AActor* OwnerActor) {
	return OwnerActor;
}

void UStatComponent::GetDamaged(float Value) {
	auto buffComponent = GetOwner()->GetComponentByClass(UBuffComponent::StaticClass());
	if (buffComponent == nullptr) {
		return;
	}

	
	NTLOG(Warning, TEXT("GetDamaged() method must be override!"));
}

bool UStatComponent::TryUpdateCurStatData(FStatType StatType, float Value) {
	NTLOG(Warning, TEXT("TryUpdateCurStatData() method must be override!"));
	return false;
}