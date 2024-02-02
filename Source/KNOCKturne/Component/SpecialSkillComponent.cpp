// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/BattleManagerSystem.h"
#include "GameMode/PeppyController.h"
#include "GameInstance/ActorManagerSystem.h"
#include "Component/SpecialSkillComponent.h"

#define TARGET_PEPPY	0
#define TARGET_BOSS		1

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

	PeppyController = (APeppyController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();

	CreateSpecialSkillData();
}

void USpecialSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckCanUseSpecialSkill(DeltaTime) && PeppyController->WasInputKeyJustPressed(EKeys::E))
	{
		bool UseSpecialSkill = TryUseSpecialSkill();
		if (UseSpecialSkill) {
			SpecialSkillData->CoolTime = OriginalCoolTime;
		}
	}
}

void USpecialSkillComponent::CreateSpecialSkillData()
{
	SpecialSkillData = SpecialSkillTable->FindRow<FSpecialSkillTable>(FName(*BattleManagerSystem->FinalSpecialSkill), TEXT("Fail to load SpecialSkillData"));
	OriginalCoolTime = SpecialSkillData->CoolTime;
	SpecialSkillData->CoolTime = 0;
}

bool USpecialSkillComponent::IsSatisfyUseCondition()
{
	FString SpecialSkillName = *BattleManagerSystem->FinalSpecialSkill;

	if (SpecialSkillName == "Skill_Special_Positivethinking") {
		if (ActorManagerSystem->PeppyActor->BuffComponent->GetNegativeBuffNum() > 0)
			return true;
		else
			return false;
	}
	else {
		return true;
	}
}

bool USpecialSkillComponent::CheckCanUseSpecialSkill(float DeltaSeconds)
{
	bool IsCostEnough = SpecialSkillData->EnergyCost < ActorManagerSystem->PeppyActor->StatComponent->CurStatData.Energy ? true : false;
	bool IsCoolTimeEnd = SpecialSkillData->CoolTime == 0;
	return IsCostEnough && IsCoolTimeEnd && IsSatisfyUseCondition();
}

void USpecialSkillComponent::ElapseTurn()
{
	if (SpecialSkillData->CoolTime > 0) {
		SpecialSkillData->CoolTime--;
	}
}

bool USpecialSkillComponent::TryUseSpecialSkill()
{
	if (FMath::FRand() > SpecialSkillData->Probability_1) {
		return false;
	}

	ActorManagerSystem->PeppyActor->StatComponent->TryUpdateCurStatData(FStatType::Energy, -SpecialSkillData->EnergyCost);

	AActor* TargetActor;
	if (SpecialSkillData->SpecialSkill_Target == TARGET_PEPPY) {
		TargetActor = ActorManagerSystem->PeppyActor;
	}
	else if (SpecialSkillData->SpecialSkill_Target == TARGET_BOSS) {
		TargetActor = ActorManagerSystem->BossActor;
	}
	else {
		NTLOG(Error, TEXT("Target set fail : SpecialSkillTarget is invalid value"));
		return false;
	}

	auto CurSequenceEffectSkillData = BattleTableManagerSystem->TryGetCurEffectIndexSpecialSkillDataSet(*SpecialSkillData);
	BattleTableManagerSystem->OperateSkillByIndex(0, TargetActor, CurSequenceEffectSkillData, nullptr);

	return true;
}

int32 USpecialSkillComponent::GetCurSpecialSkillCoolTime()
{
	return SpecialSkillData->CoolTime;
}
