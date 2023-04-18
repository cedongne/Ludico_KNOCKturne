// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppySkillComponent.h"

// Sets default values for this component's properties
UPeppySkillComponent::UPeppySkillComponent()
{
	SkillTableIndex = 0;
}


// Called when the game starts
void UPeppySkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPeppySkillComponent::EnterBattleLevel() {
	LoadGameInstances();
	LoadCanUsePeppySkillList();
}

void UPeppySkillComponent::LoadGameInstances() {
	GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
}

void UPeppySkillComponent::LoadCanUsePeppySkillList() {
	FString CurrentLevelName = GetWorld()->GetMapName();
	AddCanUsePeppySkillWithLevelName("Tutorial");
	if (CurrentLevelName == "UEDPIE_0_LV_Tutorial") {
		return;
	}
	AddCanUsePeppySkillWithLevelName("Episode1");
	if (CurrentLevelName == "UEDPIE_0_LV_Battle") {
		return;
	}
}

void UPeppySkillComponent::AddCanUsePeppySkillWithLevelName(FString LevelName) {
	UDataTable* PeppySkillTable = BattleTableManager->GetPeppySkillTable();

	TArray<FPeppySkillData*> PeppySkillRows;
	PeppySkillTable->GetAllRows<FPeppySkillData>("Get all rows of PeppySkillData", PeppySkillRows);
	if (PeppySkillRows.Num() == 0) {
		NTLOG(Error, TEXT("Failed to load PeppySkillTable"));
		return;
	}
	else {
		NTLOG(Warning, TEXT("PeppySkillTable number of rows is %d"), PeppySkillRows.Num());
	}

	while (SkillTableIndex < PeppySkillRows.Num() && PeppySkillRows[SkillTableIndex]->SkillGroupCode == LevelName) {
		CanUsePeppySkillList.Add(*PeppySkillRows[SkillTableIndex]);
		NTLOG(Warning, TEXT("%s"), *CanUsePeppySkillList[SkillTableIndex].SkillId);
		SkillTableIndex++;
	}
}
