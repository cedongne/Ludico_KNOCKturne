// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/BattleManagerSystem.h"
#include "Component/SpecialSkillComponent.h"

USpecialSkillComponent::USpecialSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FString SpecialSkillTablePath = TEXT("/Game/Assets/DataTable/SpecialSkillTable.SpecialSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SpecialSkillTABLE(*SpecialSkillTablePath);
	NTCHECK(DT_SpecialSkillTABLE.Succeeded());
	SpecialSkillTable = DT_SpecialSkillTABLE.Object;
}

void USpecialSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();

	auto SpecialSkillTableRow = SpecialSkillTable->FindRow<FSpecialSkillTable>(FName(*BattleManagerSystem->FinalSpecialSkill), TEXT(""));
	if (SpecialSkillTableRow != nullptr) {
		SpecialSkillData = new FSpecialSkillData(SpecialSkillTableRow);
	}
}

void USpecialSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

