// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "GameInstance/ActorManagerSystem.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Actor/BattleManager.h"

#define TARGET_PEPPY	0
#define TARGET_BOSS		1

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FString NS_PretendNotSick_2_Path = TEXT("/Game/Assets/Effects/SpecialSkillEffect/NS_PretendNotSick_2.NS_PretendNotSick_2");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_NS_PretendNotSick_2(*NS_PretendNotSick_2_Path);
	NTCHECK(DT_NS_PretendNotSick_2.Succeeded());
	NS_PretendNotSick_2 = DT_NS_PretendNotSick_2.Object;

	FString NS_ShieldBreak_Path = TEXT("/Game/Assets/Effects/SpecialSkillEffect/NS_ShieldBreak.NS_ShieldBreak");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_NS_ShieldBreak(*NS_ShieldBreak_Path);
	NTCHECK(DT_NS_ShieldBreak.Succeeded());
	NS_ShieldBreak = DT_NS_ShieldBreak.Object;

	FString NS_GatheringEnergy_Path = TEXT("/Game/Assets/Effects/SpecialSkillEffect/NS_GatheringEnergy.NS_GatheringEnergy");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_NS_GatheringEnergy(*NS_GatheringEnergy_Path);
	NTCHECK(DT_NS_GatheringEnergy.Succeeded());
	NS_GatheringEnergy = DT_NS_GatheringEnergy.Object;

	FString NS_GatheringEnergy_2_Path = TEXT("/Game/Assets/Effects/SpecialSkillEffect/NS_GatheringEnergy_2.NS_GatheringEnergy_2");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_NS_GatheringEnergy_2(*NS_GatheringEnergy_2_Path);
	NTCHECK(DT_NS_GatheringEnergy_2.Succeeded());
	NS_GatheringEnergy_2 = DT_NS_GatheringEnergy_2.Object;

	Peppy = Cast<APeppy>(GetOwner());
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();
	BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OperateBuffs_PerSecond(DeltaTime);
	ElapseDeltaTime(DeltaTime);
	TryOperatePeriodicRecovery(DeltaTime);
}

bool UBuffComponent::IsPositiveBuff(EBuffType BuffType)
{
	if (HasPositiveBuffs_PerTurn.Contains(BuffType) || HasPositiveBuffs_PerSecond.Contains(BuffType)) {
		return true;
	}
	else {
		return false;
	}
}

bool UBuffComponent::RemoveBuff(EBuffType BuffType) {
	if (BuffTempDelayTime.Contains(BuffType))
		BuffTempDelayTime[BuffType] = 0;

	if (HasPositiveBuffs_PerTurn.Contains(BuffType)) {
		EndPositiveBuffs_PerTurn(BuffType);
		HasPositiveBuffs_PerTurn.Remove(BuffType);
		return true;
	}
	else if (HasPositiveBuffs_PerSecond.Contains(BuffType)) {
		EndPositiveBuffs_PerSecond(BuffType);
		HasPositiveBuffs_PerSecond.Remove(BuffType);
		return true;
	}
	else if (HasNegativeBuffs_PerTurn.Contains(BuffType)) {
		EndNegativeBuffs_PerTurn(BuffType);
		HasNegativeBuffs_PerTurn.Remove(BuffType);
		return true;
	}
	else if (HasNegativeBuffs_PerSecond.Contains(BuffType)) {
		EndNegativeBuffs_PerSecond(BuffType);
		HasNegativeBuffs_PerSecond.Remove(BuffType);
		return true;
	}
	else {
		NTLOG(Error, TEXT("Buff is not Removed!"));
		return false;
	}
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
					RemoveBuff(Buff.Key);
					break;
				}
			}
		}
		else {
			for (auto Buff : HasPositiveBuffs_PerTurn) {
				if (randIndex-- == 0) {
					RemoveBuff(Buff.Key);
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
					RemoveBuff(Buff.Key);
					break;
				}
			}
		}
		else {
			for (auto Buff : HasNegativeBuffs_PerTurn) {
				if (randIndex-- == 0) {
					RemoveBuff(Buff.Key);
					break;
				}
			}
		}
	}
}

void UBuffComponent::RemoveAllPositiveBuff() {
	TArray<EBuffType> PerTurnKeys;
	HasPositiveBuffs_PerTurn.GetKeys(PerTurnKeys);

	for (auto& Key : PerTurnKeys) {
		RemoveBuff(Key);
	}

	TArray<EBuffType> PerSecondKeys;
	HasPositiveBuffs_PerSecond.GetKeys(PerSecondKeys);

	for (auto& Key : PerSecondKeys) {
		RemoveBuff(Key);
	}
}

void UBuffComponent::RemoveAllNegativeBuff() {
	TArray<EBuffType> PerTurnKeys;
	HasNegativeBuffs_PerTurn.GetKeys(PerTurnKeys);

	for (auto& Key : PerTurnKeys) {
		RemoveBuff(Key);
	}

	TArray<EBuffType> PerSecondKeys;
	HasNegativeBuffs_PerSecond.GetKeys(PerSecondKeys);

	for (auto& Key : PerSecondKeys) {
		RemoveBuff(Key);
	}
}

void UBuffComponent::RemoveAllBuff() {
	RemoveAllPositiveBuff();
	RemoveAllNegativeBuff();
}

void UBuffComponent::AcquireBuff(EBuffType BuffType, FCurEffectIndexSkillData SkillData) {
	auto buffTypeStr = BuffTypeToStringMap.Find(BuffType);
	if (buffTypeStr == nullptr) {
		NTLOG(Error, TEXT("BuffType is invalid!"));
		return;
	}

	auto acquiredBuff = BattleTableManagerSystem->BuffTable->FindRow<FBuffTable>(FName(*buffTypeStr), TEXT(""));
	if (acquiredBuff == nullptr) {
		NTLOG(Error, TEXT("Buff acquiration is failed!"));
		return;
	}

	// 중복된 버프 제거
	if (HasBuff(BuffType)) {
		RemoveBuff(BuffType);
	}

	FString SourceId = SkillData.SkillId;
	auto buffData = new FBuffData(SourceId, acquiredBuff);

	AActor* TargetActor;
	if (SkillData.SkillTarget == TARGET_PEPPY) {
		TargetActor = ActorManagerSystem->PeppyActor;
	}
	else if (SkillData.SkillTarget == TARGET_BOSS) {
		TargetActor = ActorManagerSystem->BossActor;
	}
	TargetOfBuff.Add(BuffType, TargetActor);

	if (acquiredBuff->BuffType == 0) {
		switch (buffData->BuffTermType) {
		case EBuffTermType::Turn:
			HasPositiveBuffs_PerTurn.Add(BuffType, *buffData);
			TryUpdateBuffDataBySkillData(BuffType, HasPositiveBuffs_PerTurn[BuffType], SkillData.Value_N, SkillData.Value_M, SkillData.Value_T);
			OperatePositiveBuffs_PerTurn(BuffType);
			break;
		case EBuffTermType::Second:
			HasPositiveBuffs_PerSecond.Add(BuffType, *buffData);
			TryUpdateBuffDataBySkillData(BuffType, HasPositiveBuffs_PerSecond[BuffType], SkillData.Value_N, SkillData.Value_M, SkillData.Value_T);
			if (HasPositiveBuffs_PerSecond[BuffType].Value_M == 0) {
				OperatePositiveBuffs_PerSecond(BuffType, 0);
			}
			break;
		}
	}
	else if (acquiredBuff->BuffType == 1) {
		switch (buffData->BuffTermType) {
		case EBuffTermType::Turn:
			HasNegativeBuffs_PerTurn.Add(BuffType, *buffData);
			TryUpdateBuffDataBySkillData(BuffType, HasNegativeBuffs_PerTurn[BuffType], SkillData.Value_N, SkillData.Value_M, SkillData.Value_T);
			OperateNegativeBuffs_PerTurn(BuffType);
			break;
		case EBuffTermType::Second:
			HasNegativeBuffs_PerSecond.Add(BuffType, *buffData);
			TryUpdateBuffDataBySkillData(BuffType, HasNegativeBuffs_PerSecond[BuffType], SkillData.Value_N, SkillData.Value_M, SkillData.Value_T);
			if (HasNegativeBuffs_PerSecond[BuffType].Value_M == 0) {
				OperateNegativeBuffs_PerSecond(BuffType, 0);
			}
			break;
		}
	}

	OriginalDuration.Add(BuffType, buffData->Duration);

	if (SkillData.SkillTarget == TARGET_PEPPY) {
		BattleManager->AddPeppyBuffUI(BuffType);
	}
	else if (SkillData.SkillTarget == TARGET_BOSS) {
		BattleManager->AddBossBuffUI(BuffType);
	}

	NTLOG(Warning, TEXT("Aquire Buff: [%s]"), *BuffTypeToStringMap[BuffType]);
}

void UBuffComponent::ElapseTurn() {
	TArray<EBuffType> Keys;
	HasPositiveBuffs_PerTurn.GetKeys(Keys);

	for (auto& Key : Keys) {
		if (--HasPositiveBuffs_PerTurn[Key].Duration <= 0) {
			if (RemoveBuff(Key)) {
				DeleteBuffUI(Key);
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}

	HasNegativeBuffs_PerTurn.GetKeys(Keys);
	for (auto& Key : Keys) {
		if (--HasNegativeBuffs_PerTurn[Key].Duration <= 0) {
			if (RemoveBuff(Key)) {
				DeleteBuffUI(Key);
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}
}

void UBuffComponent::ElapseDeltaTime(float DeltaTime) {
	if (!DelayWithDeltaTime(1, DeltaTime))
		return;

	TArray<EBuffType> Keys;

	HasPositiveBuffs_PerSecond.GetKeys(Keys);
	for (auto& Key : Keys) {
		HasPositiveBuffs_PerSecond[Key].Duration -= DeltaTime;

		if (HasPositiveBuffs_PerSecond[Key].Duration <= 0) {
			if (RemoveBuff(Key)) {
				DeleteBuffUI(Key);
				NTLOG(Warning, TEXT("[%s] buff is expired."), *BuffTypeToStringMap[Key]);
			}
		}
	}

	HasNegativeBuffs_PerSecond.GetKeys(Keys);
	for (auto& Key : Keys) {
		HasNegativeBuffs_PerSecond[Key].Duration -= DeltaTime;

		if (HasNegativeBuffs_PerSecond[Key].Duration <= 0) {
			if (RemoveBuff(Key)) {
				DeleteBuffUI(Key);
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

int32 UBuffComponent::GetNegativeBuffNum()
{
	int32 NegativeBuffNum = HasNegativeBuffs_PerTurn.Num() + HasNegativeBuffs_PerSecond.Num();
	return NegativeBuffNum;
}

void UBuffComponent::OperatePositiveBuffs_PerTurn(EBuffType BuffType)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	FBuffData BuffData = HasPositiveBuffs_PerTurn[BuffType];

	switch (BuffType) {
	case EBuffType::AttackIncrease:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, BuffData.Value_N);
		NTLOG(Warning, TEXT("AttackIncrease: AttackDamage +%d"), BuffData.Value_N);
		break;
	case EBuffType::EnergyDropIncrease:
		AdditionalEnergyByBuff = BuffData.Value_N;
		NTLOG(Warning, TEXT("EnergyDropIncrease: BossEnergyDrop +%d"), BuffData.Value_N);
		break;
	case EBuffType::Mood:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, BuffData.Value_N);
		NTLOG(Warning, TEXT("Mood: AttackDamage +%d"), BuffData.Value_N);
		break;
	default:
		NTLOG(Warning, TEXT("No PositiveBuffs_PerTurn Found!"));
	}
}

void UBuffComponent::EndPositiveBuffs_PerTurn(EBuffType BuffType)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	FBuffData BuffData = HasPositiveBuffs_PerTurn[BuffType];

	switch (BuffType) {
	case EBuffType::AttackIncrease:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, -BuffData.Value_N);
		NTLOG(Warning, TEXT("End AttackIncrease: AttackDamage -%d"), BuffData.Value_N);
		break;
	case EBuffType::EnergyDropIncrease:
		AdditionalEnergyByBuff = 0;
		NTLOG(Warning, TEXT("End EnergyDropIncrease: Energy -%d"), BuffData.Value_N);
		break;
	case EBuffType::Mood:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, -BuffData.Value_N);
		NTLOG(Warning, TEXT("End Mood: AttackDamage -%d"), BuffData.Value_N);
		break;
	default:
		NTLOG(Warning, TEXT("No PositiveBuffs_PerTurn Found!"));
	}
}

void UBuffComponent::OperatePositiveBuffs_PerSecond(EBuffType BuffType, float DeltaSeconds)
{
	/*AActor* TargetActor = TargetOfBuff[BuffType];
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	FBuffData BuffData = HasPositiveBuffs_PerSecond[BuffType];*/

	/*switch (BuffType) {

	default:
		NTLOG(Warning, TEXT("No PositiveBuffs_PerSecond Found!"));
	}*/
}

void UBuffComponent::EndPositiveBuffs_PerSecond(EBuffType BuffType)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	FBuffData BuffData = HasPositiveBuffs_PerSecond[BuffType];
}

void UBuffComponent::OperateNegativeBuffs_PerTurn(EBuffType BuffType)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	FBuffData BuffData = HasNegativeBuffs_PerTurn[BuffType];

	switch (BuffType) {
	case EBuffType::AttackDecrease:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, -BuffData.Value_N);
		NTLOG(Warning, TEXT("AttackDecrease: AttackDamage -%d"), BuffData.Value_N);
		break;
	default:
		NTLOG(Warning, TEXT("No NegativeBuffs_PerTurn Found!"));
	}
}

void UBuffComponent::EndNegativeBuffs_PerTurn(EBuffType BuffType)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	FBuffData BuffData = HasNegativeBuffs_PerTurn[BuffType];

	switch (BuffType) {
	case EBuffType::AttackDecrease:
		StatComponent->TryUpdateCurStatData(FStatType::AttackDamage, BuffData.Value_N);
		NTLOG(Warning, TEXT("End AttackDecrease: AttackDamage +%d"), BuffData.Value_N);
		break;
	default:
		NTLOG(Warning, TEXT("No NegativeBuffs_PerTurn Found!"));
	}
}

void UBuffComponent::OperateNegativeBuffs_PerSecond(EBuffType BuffType, float DeltaSeconds)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	FBuffData BuffData = HasNegativeBuffs_PerSecond[BuffType];

	switch (BuffType) {
	case EBuffType::PeriodicAttack:
		if (BuffDelayWithDeltaTime(EBuffType::PeriodicAttack, BuffData.Value_M, DeltaSeconds)) {
			StatComponent->GetDamaged(BuffData.Value_N);
			NTLOG(Warning, TEXT("PeriodicAttack: GetDamaged -%d"), BuffData.Value_N);
		}
		break;
	case EBuffType::SpeedDecrease: {
		ActorManagerSystem->PeppyActor->GetCharacterMovement()->MaxWalkSpeed *= 1 - BuffData.Value_N;
		break;
	}
	default:
		NTLOG(Warning, TEXT("No NegativeBuffs_PerSecond Found!"));
	}
}

void UBuffComponent::EndNegativeBuffs_PerSecond(EBuffType BuffType)
{
	AActor* TargetActor = TargetOfBuff[BuffType];
	FBuffData BuffData = HasNegativeBuffs_PerSecond[BuffType];

	switch (BuffType) {
	case EBuffType::SpeedDecrease: {
		ActorManagerSystem->PeppyActor->GetCharacterMovement()->MaxWalkSpeed /= 1 - BuffData.Value_N;
		NTLOG(Warning, TEXT("End SpeedDecrease"));
		break;
	}
	default:
		NTLOG(Warning, TEXT("No NegativeBuffs_PerSecond Found!"));
	}
}

void UBuffComponent::TryOperatePeriodicRecovery(float DeltaSeconds)
{
	if (!HasPositiveBuffs_PerTurn.Contains(EBuffType::PeriodicRecovery) || BattleManager->isPeppyTurn || isRecoveringEP) {
		return;
	}

	isPeppyMove = Peppy->GetMovementComponent()->Velocity.Size() > 0 ? true : false;
	NTLOG(Warning, TEXT("%s"), isPeppyMove ? TEXT("true") : TEXT("false"));

	if (isPeppyMove) {
		ActorManagerSystem->SpecialSkillActor->Effect->SetActive(false);
		return;
	}
	else {
		ActorManagerSystem->SpecialSkillActor->Effect->SetActive(true);
	}

	AActor* TargetActor = TargetOfBuff[EBuffType::PeriodicRecovery];
	FBuffData BuffData = HasPositiveBuffs_PerTurn[EBuffType::PeriodicRecovery];

	if (!BuffTempDelayTime.Contains(EBuffType::PeriodicRecovery))
		BuffTempDelayTime.Add(EBuffType::PeriodicRecovery, 0);

	if (BuffTempDelayTime[EBuffType::PeriodicRecovery] == 0) {
		PrePeppyLocation = ActorManagerSystem->PeppyActor->GetActorLocation();
	}

	// 페피 위치가 M초 후에도 동일한지 확인
	if (BuffDelayWithDeltaTime(EBuffType::PeriodicRecovery, BuffData.Value_M, DeltaSeconds)) {
		FVector CurPeppyLocation = ActorManagerSystem->PeppyActor->GetActorLocation();

		if (PrePeppyLocation == CurPeppyLocation) {
			isRecoveringEP = true;
			UPeppyStatComponent* PeppyStatComponent = Cast<UPeppyStatComponent>(ActorManagerSystem->PeppyActor->GetComponentByClass(UStatComponent::StaticClass()));
			PeppyStatComponent->TryUpdateCurStatData(FStatType::EP, BuffData.Value_N);
			ActorManagerSystem->SpecialSkillActor->Effect->SetAsset(NS_GatheringEnergy_2, true);
			NTLOG(Warning, TEXT("PeriodicRecovery: EP +%d"), BuffData.Value_N);

			GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateLambda([&]()
				{
					isRecoveringEP = false;

					GetWorld()->GetTimerManager().ClearTimer(EffectHandle);
				}), 2.38, false);
		}
	}
	else {
		ActorManagerSystem->SpecialSkillActor->Effect->SetAsset(NS_GatheringEnergy, true);
	}
}

void UBuffComponent::OperateBuffs_PerSecond(float DeltaSeconds)
{
	TArray<EBuffType> PositiveBuffKeys;
	HasPositiveBuffs_PerSecond.GetKeys(PositiveBuffKeys);
	TArray<EBuffType> NegativeBuffKeys;
	HasNegativeBuffs_PerSecond.GetKeys(NegativeBuffKeys);

	for (auto& Key : PositiveBuffKeys) {
		if (HasPositiveBuffs_PerSecond[Key].Value_M != 0) {
			OperatePositiveBuffs_PerSecond(Key, DeltaSeconds);
		}
	}
	
	for (auto& Key : NegativeBuffKeys) {
		if (HasNegativeBuffs_PerSecond[Key].Value_M != 0) {
			OperateNegativeBuffs_PerSecond(Key, DeltaSeconds);
		}
	}
}

FString UBuffComponent::BuffTypeToString(EBuffType BuffType)
{
	return BuffTypeToStringMap[BuffType];
}

int32 UBuffComponent::BuffIconNameToRowNum(FString BuffIconName)
{
	if (!BuffIconNameToRowNumMap.Contains(BuffIconName))
		return -1;
	return BuffIconNameToRowNumMap[BuffIconName];
}

bool UBuffComponent::BuffDelayWithDeltaTime(EBuffType BuffType, float DelayTime, float DeltaSeconds) {
	if (!BuffTempDelayTime.Contains(BuffType))
		BuffTempDelayTime.Add(BuffType, 0);

	if (BuffTempDelayTime[BuffType] > DelayTime) {
		BuffTempDelayTime[BuffType] = 0;

		return true;
	}
	BuffTempDelayTime[BuffType] += DeltaSeconds;
	return false;
}

bool UBuffComponent::DelayWithDeltaTime(float DelayTime, float DeltaSeconds)
{
	if (TempDelayTime > DelayTime) {
		TempDelayTime = 0;

		return true;
	}
	TempDelayTime += DeltaSeconds;
	return false;
}

FBuffData UBuffComponent::GetBuffData(EBuffType BuffType)
{
	FBuffData BuffData;

	if (HasPositiveBuffs_PerTurn.Contains(BuffType))
		BuffData = HasPositiveBuffs_PerTurn[BuffType];
	else if(HasPositiveBuffs_PerSecond.Contains(BuffType))
		BuffData = HasPositiveBuffs_PerSecond[BuffType];
	else if (HasNegativeBuffs_PerTurn.Contains(BuffType))
		BuffData = HasNegativeBuffs_PerTurn[BuffType];
	else
		BuffData = HasNegativeBuffs_PerSecond[BuffType];

	return BuffData;
}

void UBuffComponent::TryUpdateBuffDataBySkillData(EBuffType BuffType, FBuffData BuffData, float ValueN, float ValueM, float ValueT) {
	FString BuffID = BuffTypeToStringMap[BuffType];
	FBuffTable* BuffTableData = BattleTableManagerSystem->BuffTable->FindRow<FBuffTable>(*BuffID, TEXT(""));

	BuffTableData->defaultN = ValueN;
	BuffTableData->defaultM = ValueM;
	BuffTableData->defaultT = ValueT;

	BuffData.Value_N = BuffTableData->defaultN;
	BuffData.Value_M = BuffTableData->defaultM;
	BuffData.Value_T = BuffTableData->defaultT;
}

int UBuffComponent::GetShieldNum()
{
	if (HasPositiveBuffs_PerTurn.Contains(EBuffType::Shield)) {
		return HasPositiveBuffs_PerTurn[EBuffType::Shield].Value_N;
	}
	else {
		return 0;
	}
}

void UBuffComponent::ReduceOneShield()
{
	if (HasPositiveBuffs_PerTurn.Contains(EBuffType::Shield)) {
		HasPositiveBuffs_PerTurn[EBuffType::Shield].Value_N--;
		if (HasPositiveBuffs_PerTurn[EBuffType::Shield].Value_N == 0) {
			ActorManagerSystem->SpecialSkillActor->Effect->SetAsset(NS_ShieldBreak, true);
			RemoveBuff(EBuffType::Shield);
			DeleteBuffUI(EBuffType::Shield);
		}
		else {
			ActorManagerSystem->SpecialSkillActor->Effect->SetAsset(NS_PretendNotSick_2, true);
		}
	}
}

bool UBuffComponent::HasConfuseBuff()
{
	if (HasNegativeBuffs_PerSecond.Contains(EBuffType::Confuse))
		return true;
	else
		return false;
}

void UBuffComponent::DeleteBuffUI(EBuffType BuffType)
{
	if (!TargetOfBuff[BuffType])
		return;

	if (TargetOfBuff[BuffType] == ActorManagerSystem->BossActor) {
		HasBossBuff.Remove(BuffTypeToStringMap[BuffType]);
		BattleManager->UpdateBossBuffUI();
	}
	else if (TargetOfBuff[BuffType] == ActorManagerSystem->PeppyActor) {
		HasPeppyBuff.Remove(BuffTypeToStringMap[BuffType]);
		BattleManager->UpdatePeppyBuffUI();
	}
}

int32 UBuffComponent::GetCurDuration(EBuffType BuffType)
{
	if (!HasBuff(BuffType))
		return 0;

	FBuffData BuffData;
	if (HasPositiveBuffs_PerTurn.Contains(BuffType))
		BuffData = HasPositiveBuffs_PerTurn[BuffType];
	else if (HasPositiveBuffs_PerSecond.Contains(BuffType))
		BuffData = HasPositiveBuffs_PerSecond[BuffType];
	else if (HasNegativeBuffs_PerTurn.Contains(BuffType))
		BuffData = HasNegativeBuffs_PerTurn[BuffType];
	else
		BuffData = HasNegativeBuffs_PerSecond[BuffType];

	return BuffData.Duration;
}

bool UBuffComponent::isTermTypeTurn(EBuffType BuffType)
{
	if (!HasBuff(BuffType)) {
		NTLOG(Warning, TEXT("Can't Get TermType!"));
		return true;
	}

	FBuffData BuffData;
	if (HasPositiveBuffs_PerTurn.Contains(BuffType))
		BuffData = HasPositiveBuffs_PerTurn[BuffType];
	else if (HasPositiveBuffs_PerSecond.Contains(BuffType))
		BuffData = HasPositiveBuffs_PerSecond[BuffType];
	else if (HasNegativeBuffs_PerTurn.Contains(BuffType))
		BuffData = HasNegativeBuffs_PerTurn[BuffType];
	else
		BuffData = HasNegativeBuffs_PerSecond[BuffType];

	if (BuffData.BuffTermType == EBuffTermType::Turn)
		return true;
	else
		return false;
}
