// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "GameInstance/ActorManagerSystem.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FString BuffTablePath = TEXT("/Game/Assets/DataTable/BuffTable.BuffTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BuffTABLE(*BuffTablePath);
	NTCHECK(DT_BuffTABLE.Succeeded());
	BuffTable = DT_BuffTABLE.Object;
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ElapseDeltaTime(DeltaTime);
}

void UBuffComponent::RemoveBuff(EBuffType BuffType) {
	HasPositiveBuffs_PerTurn.Remove(BuffType);
	HasPositiveBuffs_PerSecond.Remove(BuffType);
	HasNegativeBuffs_PerTurn.Remove(BuffType);
	HasNegativeBuffs_PerSecond.Remove(BuffType);
}

void UBuffComponent::RemoveRandomPositiveBuff(int32 Num) {
	auto totalPositiveBuffNum = HasPositiveBuffs_PerTurn.Num() + HasPositiveBuffs_PerSecond.Num();
	if (Num < 0) {
		NTLOG(Error, TEXT("Num must be Positive!"));
	}

	if (Num > totalPositiveBuffNum) {
		Num = totalPositiveBuffNum;
	}
	while (Num--) {
		auto randIndex = rand() % totalPositiveBuffNum;
		if (randIndex >= HasPositiveBuffs_PerTurn.Num()) {
			randIndex -= HasPositiveBuffs_PerTurn.Num();
			for (auto Buff : HasPositiveBuffs_PerSecond) {
				if (randIndex-- == 0) {
					HasPositiveBuffs_PerSecond.Remove(Buff.Key);
					break;
				}
			}
		}
		else {
			for (auto Buff : HasPositiveBuffs_PerTurn) {
				if (randIndex-- == 0) {
					HasPositiveBuffs_PerTurn.Remove(Buff.Key);
					break;
				}
			}
		}
	}
}

void UBuffComponent::RemoveRandomNegativeBuff(int32 Num) {
	auto totalNegativeBuffNum = HasNegativeBuffs_PerTurn.Num() + HasNegativeBuffs_PerSecond.Num();
	if (Num < 0) {
		NTLOG(Error, TEXT("Num must be Positive!"));
	}

	if (Num > totalNegativeBuffNum) {
		Num = totalNegativeBuffNum;
	}
	while (Num--) {
		auto randIndex = rand() % totalNegativeBuffNum;
		if (randIndex >= HasNegativeBuffs_PerTurn.Num()) {
			randIndex -= HasNegativeBuffs_PerTurn.Num();
			for (auto Buff : HasNegativeBuffs_PerSecond) {
				if (randIndex-- == 0) {
					HasNegativeBuffs_PerSecond.Remove(Buff.Key);
					break;
				}
			}
		}
		else {
			for (auto Buff : HasNegativeBuffs_PerTurn) {
				if (randIndex-- == 0) {
					HasNegativeBuffs_PerTurn.Remove(Buff.Key);
					break;
				}
			}
		}
	}
}

void UBuffComponent::RemoveAllPositiveBuff() {
	HasPositiveBuffs_PerTurn.Empty();
	HasPositiveBuffs_PerSecond.Empty();
}

void UBuffComponent::RemoveAllNegativeBuff() {
	HasNegativeBuffs_PerTurn.Empty();
	HasNegativeBuffs_PerSecond.Empty();
}

void UBuffComponent::RemoveAllBuff() {
	RemoveAllPositiveBuff();
	RemoveAllNegativeBuff();
}

void UBuffComponent::AcquireBuff(EBuffType BuffType, FString SourceId) {
	auto buffTypeStr = BuffTypeToStringMap.Find(BuffType);
	if (buffTypeStr == nullptr) {
		NTLOG(Error, TEXT("BuffType is invalid!"));
		return;
	}

	auto acquiredBuff = BuffTable->FindRow<FBuffTable>(FName(*buffTypeStr), TEXT(""));
	if (acquiredBuff == nullptr) {
		NTLOG(Error, TEXT("Buff acquiration is failed!"));
		return;
	}

	// 중복된 버프 제거
	if (HasBuff(BuffType)) {
		RemoveBuff(BuffType);
	}
	
	auto buffData = new FBuffData(SourceId, acquiredBuff);

	if (acquiredBuff->BuffType == 0) {
		switch (buffData->BuffTermType) {
		case EBuffTermType::Turn:
			HasPositiveBuffs_PerTurn.Add(BuffType, *buffData);
			break;
		case EBuffTermType::Second:
			HasPositiveBuffs_PerSecond.Add(BuffType, *buffData);
			break;
		}
	}
	else if (acquiredBuff->BuffType == 1) {
		switch (buffData->BuffTermType) {
		case EBuffTermType::Turn:
			HasNegativeBuffs_PerTurn.Add(BuffType, *buffData);
			break;
		case EBuffTermType::Second:
			HasNegativeBuffs_PerSecond.Add(BuffType, *buffData);
			break;
		}
	}
}

void UBuffComponent::ElapseTurn() {
	TArray<EBuffType> Keys;
	HasPositiveBuffs_PerTurn.GetKeys(Keys);

	for (auto& Key : Keys) {
		if (--HasPositiveBuffs_PerTurn[Key].Duration == 0) {
			if (HasPositiveBuffs_PerTurn.Remove(Key)) {
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}

	HasNegativeBuffs_PerTurn.GetKeys(Keys);
	for (auto& Key : Keys) {
		if (--HasNegativeBuffs_PerTurn[Key].Duration == 0) {
			if (HasNegativeBuffs_PerTurn.Remove(Key)) {
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}
}

void UBuffComponent::ElapseDeltaTime(float DeltaTime) {
	TArray<EBuffType> Keys;

	HasPositiveBuffs_PerSecond.GetKeys(Keys);
	for (auto& Key : Keys) {
		HasPositiveBuffs_PerSecond[Key].Duration -= DeltaTime;

		if (HasPositiveBuffs_PerSecond[Key].Duration <= 0) {
			if (HasPositiveBuffs_PerSecond.Remove(Key)) {
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}

	HasNegativeBuffs_PerSecond.GetKeys(Keys);
	for (auto& Key : Keys) {
		HasNegativeBuffs_PerSecond[Key].Duration -= DeltaTime;

		if (HasNegativeBuffs_PerSecond[Key].Duration-- == 0) {
			if (HasNegativeBuffs_PerSecond.Remove(Key)) {
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}
}

void UBuffComponent::ExpireBuff(TMap<EBuffType, FBuffData>* BuffMap, EBuffType BuffType) {
	BuffMap->Remove(BuffType);
}

bool UBuffComponent::HasBuff(EBuffType BuffType) {
	return HasPositiveBuffs_PerSecond.Contains(BuffType)
		|| HasPositiveBuffs_PerTurn.Contains(BuffType)
		|| HasNegativeBuffs_PerSecond.Contains(BuffType)
		|| HasNegativeBuffs_PerTurn.Contains(BuffType)
		? true : false;
}

void UBuffComponent::OperatePositiveBuffs_PerTurn(FBuffData BuffData, EBuffType BuffType, AActor* TargetActor)
{
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));

	switch (BuffType) {
	case EBuffType::AttackIncrease:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, BuffData.Value_N);
		break;
	case EBuffType::EnergyDropIncrease:
		StatComponent->TryUpdateCurStatData(FStatType::Energy, BuffData.Value_N);
		break;
	case EBuffType::Shield:
		UPeppyStatComponent* PeppyStatComponent = Cast<UPeppyStatComponent>(ActorManagerSystem->PeppyActor->GetComponentByClass(UStatComponent::StaticClass()));
		PeppyStatComponent->CanBeDamaged = false;
		break;
	default:
		NTLOG(Warning, TEXT("No PositiveBuffs_PerTurn Found!"));
	}
}

void UBuffComponent::OperatePositiveBuffs_PerSecond(FBuffData BuffData, EBuffType BuffType, AActor* TargetActor, float DeltaSeconds)
{
	// UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));

	switch (BuffType) {
	case EBuffType::PeriodicRecovery:
		if (DelayWithDeltaTime(BuffData.Value_M, DeltaSeconds)) {
			UPeppyStatComponent* PeppyStatComponent = Cast<UPeppyStatComponent>(ActorManagerSystem->PeppyActor->GetComponentByClass(UStatComponent::StaticClass()));
			PeppyStatComponent->TryUpdateCurStatData(FStatType::EP, BuffData.Value_N);
		}
		break;
	default:
		NTLOG(Warning, TEXT("No PositiveBuffs_PerSecond Found!"));
	}
}

void UBuffComponent::OperateNegativeBuffs_PerTurn(FBuffData BuffData, EBuffType BuffType, AActor* TargetActor)
{
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));

	switch (BuffType) {
	case EBuffType::AttackDecrease:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, -BuffData.Value_N);
		break;
	default:
		NTLOG(Warning, TEXT("No NegativeBuffs_PerTurn Found!"));
	}
}

void UBuffComponent::OperateNegativeBuffs_PerSecond(FBuffData BuffData, EBuffType BuffType, AActor* TargetActor, float DeltaSeconds)
{
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));

	switch (BuffType) {
	case EBuffType::PeriodicAttack:
		if (DelayWithDeltaTime(BuffData.Value_M, DeltaSeconds)) {
			StatComponent->GetDamaged(BuffData.Value_N);
		}
		break;
	/*case EBuffType::SpeedDecrease:
		
		break;
	case EBuffType::Confuse:

		break;*/
	default:
		NTLOG(Warning, TEXT("No NegativeBuffs_PerSecond Found!"));
	}
}

void UBuffComponent::OperateBuffs_PerTurn()
{
	TArray<EBuffType> Keys;
	HasPositiveBuffs_PerTurn.GetKeys(Keys);

	for (auto& Key : Keys) {
		//OperatePositiveBuffs_PerTurn(HasPositiveBuffs_PerTurn[Key], Key, );
	}

	HasNegativeBuffs_PerTurn.GetKeys(Keys);
	for (auto& Key : Keys) {
		//OperateNegativeBuffs_PerTurn(HasNegativeBuffs_PerTurn[Key], Key, );
	}
}

void UBuffComponent::OperateBuffs_PerSecond(float DeltaSeconds)
{

}

bool UBuffComponent::DelayWithDeltaTime(float DelayTime, float DeltaSeconds) {
	if (TempDelayTime > DelayTime) {
		TempDelayTime = 0;

		return true;
	}
	TempDelayTime += DeltaSeconds;
	return false;
}

void UBuffComponent::TryAttackIncrease(AActor* TargetActor, FCurEffectIndexSkillData SkillData)
{
	if (HasPositiveBuffs_PerTurn.Contains(EBuffType::AttackIncrease)) {
		AttackIncreaseTargetActor = TargetActor;
		UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, SkillData.Value_N);
	}
}

void UBuffComponent::EndAttackIncrease(FCurEffectIndexSkillData SkillData)
{
	if (HasNegativeBuffs_PerTurn.Contains(EBuffType::AttackIncrease)) {
		UStatComponent* StatComponent = Cast<UStatComponent>(AttackIncreaseTargetActor->GetComponentByClass(UStatComponent::StaticClass()));
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, -SkillData.Value_N);
	}
}

void UBuffComponent::TryAttackDecrease(AActor* TargetActor, FCurEffectIndexSkillData SkillData)
{
	if (HasNegativeBuffs_PerTurn.Contains(EBuffType::AttackDecrease)) {
		AttackDecreaseTargetActor = TargetActor;
		UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, -SkillData.Value_N);
	}
}

void UBuffComponent::EndAttackDecrease(FCurEffectIndexSkillData SkillData)
{
	if (HasNegativeBuffs_PerTurn.Contains(EBuffType::AttackDecrease)) {
		UStatComponent* StatComponent = Cast<UStatComponent>(AttackDecreaseTargetActor->GetComponentByClass(UStatComponent::StaticClass()));
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, SkillData.Value_N);
	}
}

void UBuffComponent::TryPeriodicAttack(AActor* TargetActor, FCurEffectIndexSkillData SkillData, float DeltaSeconds)
{
	if (HasNegativeBuffs_PerSecond.Contains(EBuffType::PeriodicAttack)) {
		UStatComponent* StatComponent = Cast<UStatComponent>(PeriodicAttackTargetActor->GetComponentByClass(UStatComponent::StaticClass()));
		TempDelayTime += DeltaSeconds;

		if (TempDelayTime >= SkillData.Value_M) {
			StatComponent->GetDamaged(SkillData.Value_N);
			TempDelayTime = 0;
		}
	}
}

void UBuffComponent::OperateBuffs(AActor* TargetActor, FCurEffectIndexSkillData SkillData)
{
	TryAttackIncrease(TargetActor, SkillData);
	TryAttackDecrease(TargetActor, SkillData);
}

void UBuffComponent::ReturnBeforeBuffData(FCurEffectIndexSkillData SkillData)
{
	EndAttackIncrease(SkillData);
	EndAttackDecrease(SkillData);
}
