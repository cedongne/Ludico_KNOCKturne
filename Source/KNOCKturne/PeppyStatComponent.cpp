// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatComponent.h"
#include "PeppyStatDataInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPeppyStatComponent::UPeppyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// It makes call InitializeComponent() method
	bWantsInitializeComponent = true;
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
}

void UPeppyStatComponent::SetDefaultStat() {
	auto PeppyStatDataInstance = Cast<UPeppyStatDataInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentStatData = PeppyStatDataInstance->GetPeppyStatData("Init");
	CurrentHP = 100;
}

