// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTableManagerSystem.h"
#include "Actor/Peppy.h"
#include "Actor/BattleManager.h"
#include "Actor/BossSkillActor.h"
#include "Actor/PeppySkillActor.h"
#include "Actor/CommonSkillActor.h"
#include "Component/BuffComponent.h"
#include "Util/CalcUtil.h"
#include "GameInstance/ActorManagerSystem.h"

#define TARGET_PEPPY	0
#define TARGET_BOSS		1

void UBattleTableManagerSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();
	BattleManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBattleManagerSystem>();
}

UBattleTableManagerSystem::UBattleTableManagerSystem() {
	FString BossContactSkillTablePath = TEXT("/Game/Assets/DataTable/Ep1BossContactSkillTable.Ep1BossContactSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSCONTACTSKILLTABLE(*BossContactSkillTablePath);
	NTCHECK(DT_BOSSCONTACTSKILLTABLE.Succeeded());
	BossContactSkillTable = DT_BOSSCONTACTSKILLTABLE.Object;

	FString BossNonContactSkillTablePath = TEXT("/Game/Assets/DataTable/Ep1BossNonContactSkillTable.Ep1BossNonContactSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSNONCONTACTSKILLTABLE(*BossNonContactSkillTablePath);
	NTCHECK(DT_BOSSNONCONTACTSKILLTABLE.Succeeded());
	BossNonContactSkillTable = DT_BOSSNONCONTACTSKILLTABLE.Object;

	FString BossStatDataPath = TEXT("/Game/Assets/DataTable/BossStatTable.BossStatTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSSTATDATATABLE(*BossStatDataPath);
	NTCHECK(DT_BOSSSTATDATATABLE.Succeeded());
	BossStatDataTable = DT_BOSSSTATDATATABLE.Object;

	FString PeppySkilTablePath = TEXT("/Game/Assets/DataTable/PeppySkillTable.PeppySkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSKILLTABLE(*PeppySkilTablePath);
	NTCHECK(DT_PEPPYSKILLTABLE.Succeeded());
	PeppySkillTable = DT_PEPPYSKILLTABLE.Object;

	FString PeppyStatDataPath = TEXT("/Game/Assets/DataTable/PeppyStatTable.PeppyStatTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSTATDATATABLE(*PeppyStatDataPath);
	NTCHECK(DT_PEPPYSTATDATATABLE.Succeeded());
	PeppyStatDataTable = DT_PEPPYSTATDATATABLE.Object;

	
	SetBossSkillSpawnDataTable();
	CurPeppySkillData.Add("BP_PS_Starlight_C", *(GetPeppySkillTable()->FindRow<FPeppySkillData>(TEXT("BP_PS_Starlight_C"), TEXT("Fail to load PeppySkillData"))));
}

void UBattleTableManagerSystem::SetBossSkillSpawnDataTable() {
	TArray<FVector> TempSpawnLocation;
	// �𸮾� ������ �󿡼� �������Ͱ�	Roll, Pitch, Yaw
	// C++ ��ũ��Ʈ �󿡼� �������Ͱ�		Pitch, Yaw, Roll	���̶�� ���� ������ ��.
	TArray<FRotator> TempSpawnRotation;


	/// SweptGarden
	TempSpawnLocation.Empty();
	TempSpawnRotation.Empty();
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 0.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 90.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 180.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));
	TempSpawnLocation.Push(FVector(755.0f, 771.0f, -86.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));

	/*AddBossSkillSpawnDataToMap(
		"SweptGarden",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_SweptGarden.BP_SweptGarden_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"CleanUpIntruder1",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_CleanUpIntruder1.BP_CleanUpIntruder1_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"CleanUpIntruder2",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_CleanUpIntruder2.BP_CleanUpIntruder2_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	AddBossSkillSpawnDataToMap(
		"ThornOfLoveAndHatred",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_ThornOfLoveAndHatred.BP_ThornOfLoveAndHatred_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);
	/*AddBossSkillSpawnDataToMap(
		"ChasePeppy",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_ChasePeppy.BP_ChasePeppy_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"GoBackMoment",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_GoBackMoment.BP_GoBackMoment_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	 /*AddBossSkillSpawnDataToMap(
		"MixedFeeling",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_MixedFeeling.BP_MixedFeeling_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"BindPeppy",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_BindPeppy.BP_BindPeppy_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"HeightenedLonging",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_HeightenedLonging.BP_HeightenedLonging_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"BloodColoredFlower",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_BloodColoredFlower.BP_BloodColoredFlower_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/
	/*AddBossSkillSpawnDataToMap(
		"ExtendedRoot",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_ExtendedRoot.BP_ExtendedRoot_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);*/

	// Note : Ȥ�� ���� ����� ���� TempSpawnLocation�� TempSpawnRotation ��ü�� �ʱ�ȭ�Ǹ鼭 ������ �߻��ϴ����� ���� �̽� ������ �ʿ���.
}

FBossSkillSpawnData FBossSkillSpawnData::SetBossSkillSpawnData(UClass* _SkillObjectClass, TArray<FTransform> _SkillTrnasforms) {
	FBossSkillSpawnData SkillSpawnData;
	SkillSpawnData.SkillObjectClass = _SkillObjectClass;
	SkillSpawnData.SkillTransform = _SkillTrnasforms;

	return SkillSpawnData;
}

void UBattleTableManagerSystem::AddBossSkillSpawnDataToMap(FString SkillName, TCHAR* SkillObjectPath, TArray<FVector> SpawnLocation, TArray<FRotator> SpawnRotation) {
	UClass* TempSkillObjectClass;
	TArray<FTransform> TempSkillTransform;

	TempSkillObjectClass = LoadClass<AActor>(NULL, SkillObjectPath, NULL, LOAD_None, NULL);
	TempSkillTransform.Empty();
	if (SpawnLocation.Num() != SpawnRotation.Num()) {
		NTLOG(Error, TEXT("Parameter is invalid. Number of element in transform array is different!"));
		return;
	}
	FVector TempLocation;
	FRotator TempRotator;

	for (int index = 0; index < SpawnLocation.Num(); index++) {
		TempLocation = SpawnLocation[index];
		TempRotator = SpawnRotation[index];
		FTransform TempTransform{
			TempRotator,
			TempLocation
		};
		TempSkillTransform.Add(TempTransform);
	}

	BossSkillSpawnDataMap.Add(SkillName, FBossSkillSpawnData::SetBossSkillSpawnData(TempSkillObjectClass, TempSkillTransform));

	NTLOG(Log, TEXT("[BossSkillSpawnData] %s is loaded!"), *SkillName);
}

bool UBattleTableManagerSystem::TryUseBossSkillSequential(FBossSkillData SkillData, ABossSkillActor* RefActor) {
	int32 SkillTarget[2] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2 };

	AActor* TargetActor;

	for (int Sequence = 0; Sequence < 2; Sequence++) {
		if (SkillTarget[Sequence] == TARGET_PEPPY) {
			TargetActor = ActorManagerSystem->PeppyActor;
		}
		else if (SkillTarget[Sequence] == TARGET_BOSS) {
			TargetActor = ActorManagerSystem->BossActor;
		}
		else {
//			NTLOG(Error, TEXT("Target set fail : BossSkillTargets[%d] is invalid value(%d)"), IndexCount, SkillIndexes[IndexCount]);
			break;
		}

		auto CurSequenceEffectSkillData = *TryGetCurEffectIndexBossSkillDataSet(Sequence, &SkillData);
		if (CurSequenceEffectSkillData.SkillId == "-1") {
			NTLOG(Error, TEXT("SkillData is invalid!"));
			return false;
		}

		if (FMath::FRand() > CurSequenceEffectSkillData.Probability) {
			return false;
		}
		OperateSkillByIndex(Sequence, TargetActor, CurSequenceEffectSkillData, RefActor);
	}

	return true;
}

bool UBattleTableManagerSystem::TryUseBossSkillProbabilistic(FBossSkillData SkillData, ABossSkillActor* RefActor) {
	auto Probability = FMath::FRand();
	int32 Sequence;
	int32 SkillTarget;
	bool SkillSucceed = Probability < SkillData.Probability_1;

	if (SkillSucceed) {
		Sequence = 0;
		SkillTarget = SkillData.SkillTarget_1;
	}
	else {
		Sequence = 1;
		SkillTarget = SkillData.SkillTarget_2;
	}

	AActor* TargetActor;

	if (SkillTarget == TARGET_PEPPY) {
		TargetActor = ActorManagerSystem->PeppyActor;
	}
	else if (SkillTarget == TARGET_BOSS) {
		TargetActor = ActorManagerSystem->BossActor;
	}
	else {
		NTLOG(Error, TEXT("Target set fail : PeppySkillTarget is invalid value"));
		return false;
	}
	OperateSkillByIndex(Sequence, TargetActor, *TryGetCurEffectIndexBossSkillDataSet(Sequence, &SkillData), RefActor);

	return SkillSucceed;
}

bool UBattleTableManagerSystem::TryUsePeppySkillSequential(FPeppySkillData SkillData, APeppySkillActor* RefActor) {
	ActorManagerSystem->PeppyActor->StatComponent->TryUpdateCurStatData(FStatType::Energy, -SkillData.Cost);

	int32 SkillTarget[3] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2, SkillData.SkillTarget_3 };

	AActor* TargetActor;

	for (int Sequence = 0; Sequence < 3; Sequence++) {
		if (SkillTarget[Sequence] == TARGET_PEPPY) {
			TargetActor = ActorManagerSystem->PeppyActor;
		}
		else if (SkillTarget[Sequence] == TARGET_BOSS) {
			TargetActor = ActorManagerSystem->BossActor;
		}
		else {
			NTLOG(Error, TEXT("Target set fail : PeppySkillTarget is invalid value"));
			break;
		}
		NTLOG(Error, TEXT("%d"), SkillTarget[Sequence]);
		
		auto CurSequenceEffectSkillData = *TryGetCurEffectIndexPeppySkillDataSet(Sequence, &SkillData);
		if (CurSequenceEffectSkillData.SkillId == "-1") {
			NTLOG(Error, TEXT("SkillData is invalid!"));
			return false;
		}

		if (FMath::FRand() > CurSequenceEffectSkillData.Probability) {
			return false;
		}
		OperateSkillByIndex(Sequence, TargetActor, CurSequenceEffectSkillData, RefActor);
	}

	return true;
}

bool UBattleTableManagerSystem::TryUsePeppySkillProbabilistic(FPeppySkillData SkillData, APeppySkillActor* RefActor) {
	ActorManagerSystem->PeppyActor->StatComponent->TryUpdateCurStatData(FStatType::Energy, -SkillData.Cost);

	auto Probability = FMath::FRand();
	int32 SkillTarget;
	bool SkillSucceed = Probability < SkillData.Probability_1;

	// ���� ��ų�� EffectSequence�� 3���� ������, Ȯ���� ���� �ϳ��� ȿ���� �����ϴ� ó���� EffectSequence 2������ �����ϹǷ� �̿� ���� �ӽ� ����.
	if (SkillSucceed) {
		PeppySkillProbabilisticSequence = 0;
		SkillTarget = SkillData.SkillTarget_1;
	}
	else {
		PeppySkillProbabilisticSequence = 1;
		SkillTarget = SkillData.SkillTarget_2;
	}

	AActor* TargetActor;

	if (SkillTarget == TARGET_PEPPY) {
		TargetActor = ActorManagerSystem->PeppyActor;
	}
	else if (SkillTarget == TARGET_BOSS) {
		TargetActor = ActorManagerSystem->BossActor;
	}
	else {
		NTLOG(Error, TEXT("Target set fail : PeppySkillTarget is invalid value"));
		return false;
	}
	OperateSkillByIndex(PeppySkillProbabilisticSequence, TargetActor, *TryGetCurEffectIndexPeppySkillDataSet(PeppySkillProbabilisticSequence, &SkillData), RefActor);

	return SkillSucceed;
}

void UBattleTableManagerSystem::OperateSkillByIndex(int32 EffectSequence, AActor* TargetActor, FCurEffectIndexSkillData SkillData, ACommonSkillActor* SkillActor) {
	if (SkillData.SkillId == "-1" || TargetActor == nullptr) {
		NTLOG(Error, TEXT("Skill operate is failed!"));
		return;
	}

	UStatComponent* StatComponent = Cast<UStatComponent>(TargetActor->GetComponentByClass(UStatComponent::StaticClass()));
	UBuffComponent* BuffComponent = Cast<UBuffComponent>(TargetActor->GetComponentByClass(UBuffComponent::StaticClass()));

	if (SkillData.SkillIndex == 1) {
		SkillActor->CustomSkillOperation(EffectSequence, TargetActor, SkillData, SkillActor);
	}
	/*
	*	11 �ܼ� ����: ����� EP�� ��� N��ŭ ����.
	*/
	else if (SkillData.SkillIndex == 11) {
		StatComponent->GetDamaged(SkillData.Value_N);
		NTLOG(Log, TEXT("[%s : SkillIndex 11] Attack damage %lf"), *SkillData.SkillId, SkillData.Value_N);
	}
	else if (SkillData.SkillIndex == 12) {
		StatComponent->TryUpdateCurStatData(FStatType::EP, SkillData.Value_N);
	}
	/*
	*	13 ���� ����: ����� EP�� ��� N �̻� M ������ ������ ¦�� ��ġ��ŭ ����.
	*/
	else if (SkillData.SkillIndex == 13) {
		StatComponent->GetDamaged(CalcUtil::RandEvenNumberInRange(SkillData.Value_N, SkillData.Value_M));
		NTLOG(Log, TEXT("[%s : SkillIndex 13] Random attack damage %lf"), *SkillData.SkillId, SkillData.Value_N);
	}
	/*
	*	16 ���� �����-����: ����� ��� ������ ���� �� �������� N�� ����
	*/
	else if (SkillData.SkillIndex == 16) {
		BuffComponent->RemoveRandomPositiveBuff(SkillData.Value_N);
	}
	else if (SkillData.SkillIndex == 17) {
		BuffComponent->RemoveRandomNegativeBuff(SkillData.Value_N);
	}
	/*
	*	32 ���ݷ� ���: T�ϵ��� ����� ���ϴ� ���� �������� N��ŭ ����
	*/
	else if (SkillData.SkillIndex == 32) {
		BuffComponent->AcquireBuff(EBuffType::AttackIncrease, SkillData);
	}
	/*
	*	34 �ݻ�: ��󿡰� T�ϵ��� ��뿡�� �������� ���� ������ N��ŭ�� �������� �����ִ� ���ݻ�(ReflexiveAttack)�� ������ �ο�
	*/
	else if (SkillData.SkillIndex == 34) {
		BuffComponent->AcquireBuff(EBuffType::ReflexiveAttack, SkillData);
	}
	else if (SkillData.SkillIndex == 36) {
		BuffComponent->AcquireBuff(EBuffType::PeriodicRecovery, SkillData);
	}
	else if (SkillData.SkillIndex == 39) {
		BuffComponent->AcquireBuff(EBuffType::Shield, SkillData);
	}
	/*
	*	52
	*/
	else if (SkillData.SkillIndex == 52) {
		BuffComponent->AcquireBuff(EBuffType::AttackDecrease, SkillData);
	}
	/*
	*	54 ���� ������: ����� HP�� �� �ϸ��� N��ŭ T�ϵ��� ����
	*/
	else if (SkillData.SkillIndex == 54) {
		/*TArray<int32> PeriodicDamages;
		PeriodicDamages.Init(SkillData.Value_N, SkillData.Value_T);*/
		auto Probability = FMath::FRand();
		if (Probability < 100) {
			BuffComponent->AcquireBuff(EBuffType::PeriodicAttack, SkillData);
		}

		//		Cast<APeppy>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddCumulativeDamageBeforeStartTurn(SkillData.SkillId, PeriodicDamages);
		NTLOG(Log, TEXT("[%s : SkillIndex 54] Periodic attack damage %lf in %lf Turns"), *SkillData.SkillId, SkillData.Value_N, SkillData.Value_T);
	}
	else if (SkillData.SkillIndex == 72) {
		BuffComponent->AcquireBuff(EBuffType::SpeedDecrease, SkillData);
	}
	else if (SkillData.SkillIndex == 73) {
		BuffComponent->AcquireBuff(EBuffType::Confuse, SkillData);
	}
	/*
	*	92 ���: ��󿡰� T�ϵ��� �����Ǵ� �����(Warning)�� ������ �ο�
	*/
	else if (SkillData.SkillIndex == 92) {
		BuffComponent->AcquireBuff(EBuffType::Warning, SkillData);
	}
	else {
		NTLOG(Error, TEXT("No Boss skill index %d"), SkillData.SkillIndex);
	}
}

FPeppyStatData UBattleTableManagerSystem::GetPeppyStatDataOnTable(FString DataType) {
	FPeppyStatData* statData = PeppyStatDataTable->FindRow<FPeppyStatData>(*DataType, TEXT(""));
	if (statData == nullptr) {
		NTLOG(Error, TEXT("Load fail"));
		return FPeppyStatData::FPeppyStatData();
	}
	return *statData;
}

FBossStatData UBattleTableManagerSystem::GetBossStatDataOnTable(FString DataType) {
	FBossStatData* statData = BossStatDataTable->FindRow<FBossStatData>(*DataType, TEXT(""));
	if (statData == nullptr) {
		NTLOG(Error, TEXT("Load fail"));
		return FBossStatData::FBossStatData();
	}
	return *statData;
}

UDataTable* UBattleTableManagerSystem::GetPeppySkillTable() {
	return PeppySkillTable;
}

TMap<FString, FPeppySkillData> UBattleTableManagerSystem::GetCurPeppySkillData()
{
	return CurPeppySkillData;
}

FName UBattleTableManagerSystem::GetCurrentBlueprintClassName() {
	return *(GetClass()->GetFName().ToString());
}

void UBattleTableManagerSystem::TryUpdateCurSkillDataCost(FString BPClassName, float Value)
{
	if (CurPeppySkillData.Find(BPClassName) == nullptr)
		return;

	CurPeppySkillData[BPClassName].Cost += Value;
}

FCurEffectIndexSkillData* UBattleTableManagerSystem::TryGetCurEffectIndexBossSkillDataSet(int32 Sequence, FBossSkillData* CurStatData) {
	FCurEffectIndexSkillData* ResultStatData = new FCurEffectIndexSkillData();

	switch (Sequence) {
	case 0:
		ResultStatData->SetCurEffectIndexStatData(
			CurStatData->BossSkillID,
			CurStatData->SkillIndex_1,
			CurStatData->Probability_1,
			CurStatData->SkillTarget_1,
			CurStatData->Value_1_N,
			CurStatData->Value_1_M,
			CurStatData->Value_1_T,
			CurStatData->BuffCode_1,
			0	// Cost
		);
		break;
	case 1:
		ResultStatData->SetCurEffectIndexStatData(
			CurStatData->BossSkillID,
			CurStatData->SkillIndex_2,
			CurStatData->Probability_2,
			CurStatData->SkillTarget_2,
			CurStatData->Value_2_N,
			CurStatData->Value_2_M,
			CurStatData->Value_2_T,
			CurStatData->BuffCode_2,
			0	// Cost
		);
		break;
	default:
		NTLOG(Error, TEXT("BossSkillData index [%d] is invalid to load!"), Sequence);
		return nullptr;
	}

	return ResultStatData;
}

FCurEffectIndexSkillData* UBattleTableManagerSystem::TryGetCurEffectIndexPeppySkillDataSet(int32 Sequence, FPeppySkillData* CurStatData) {
	FCurEffectIndexSkillData* ResultStatData = new FCurEffectIndexSkillData();

	switch (Sequence) {
	case 0:
		ResultStatData->SetCurEffectIndexStatData(
			CurStatData->SkillId,
			CurStatData->SkillIndex_1,
			CurStatData->Probability_1,
			CurStatData->SkillTarget_1,
			CurStatData->Value_1_N,
			CurStatData->Value_1_M,
			CurStatData->Value_1_T,
			CurStatData->BuffCode_1,
			CurStatData->Cost
		);
		break;
	case 1:
		ResultStatData->SetCurEffectIndexStatData(
			CurStatData->SkillId,
			CurStatData->SkillIndex_2,
			CurStatData->Probability_2,
			CurStatData->SkillTarget_2,
			CurStatData->Value_2_N,
			CurStatData->Value_2_M,
			CurStatData->Value_2_T,
			CurStatData->BuffCode_2,
			CurStatData->Cost
		);
		break;
	case 2:
		ResultStatData->SetCurEffectIndexStatData(
			CurStatData->SkillId,
			CurStatData->SkillIndex_3,
			CurStatData->Probability_3,
			CurStatData->SkillTarget_3,
			CurStatData->Value_3_N,
			CurStatData->Value_3_M,
			CurStatData->Value_3_T,
			CurStatData->BuffCode_3,
			CurStatData->Cost
		);
		break;
	default:
		NTLOG(Error, TEXT("PeppySkillData index [%d] is invalid to load!"), Sequence);
		return nullptr;
	}

	return ResultStatData;
}

FCurEffectIndexSkillData UBattleTableManagerSystem::TryGetCurEffectIndexSpecialSkillDataSet(FSpecialSkillTable CurStatData)
{
	FCurEffectIndexSkillData* ResultStatData = new FCurEffectIndexSkillData();

	ResultStatData->SetCurEffectIndexStatData(
			BattleManagerSystem->FinalSpecialSkill,
			CurStatData.Skill_Index,
			CurStatData.Probability_1,
			CurStatData.SpecialSkill_Target,
			CurStatData.Value1N,
			CurStatData.Value1M,
			CurStatData.Value1T,
			CurStatData.BuffCode,
			CurStatData.EnergyCost
	);

	return *ResultStatData;
}
