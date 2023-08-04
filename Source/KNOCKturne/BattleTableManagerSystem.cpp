// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTableManagerSystem.h"
#include "BossSkillActor.h"
#include "PeppySkillActor.h"
#include "BuffComponent.h"
#include "CalcUtil.h"
#include "Peppy.h"
#include "BattleManager.h"

#define TARGET_PEPPY	0
#define TARGET_BOSS		1

void UBattleTableManagerSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
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

	CurPeppyStat = GetPeppyStatDataOnTable("Init");
	CurBossStat = GetBossStatDataOnTable("Episode1_SadnessQueen_Init");

	SetBossSkillSpawnDataTable();
}

void UBattleTableManagerSystem::SetBossSkillSpawnDataTable() {
	TArray<FVector> TempSpawnLocation;
	// 언리얼 에디터 상에선 로테이터가	Roll, Pitch, Yaw
	// C++ 스크립트 상에선 로테이터가		Pitch, Yaw, Roll	순이라는 것을 유의할 것.
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

	AddBossSkillSpawnDataToMap(
		"SweptGarden",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_SweptGarden.BP_SweptGarden_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);
	AddBossSkillSpawnDataToMap(
		"CleanUpIntruder1",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_CleanUpIntruder1.BP_CleanUpIntruder1_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);
	AddBossSkillSpawnDataToMap(
		"CleanUpIntruder2",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_CleanUpIntruder2.BP_CleanUpIntruder2_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);
	AddBossSkillSpawnDataToMap(
		"ThornOfLoveAndHatred",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/SkillActor/BP_ThornOfLoveAndHatred.BP_ThornOfLoveAndHatred_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);

	// Note : 혹시 얕은 복사로 인해 TempSpawnLocation과 TempSpawnRotation 객체가 초기화되면서 문제가 발생하는지에 대한 이슈 관리가 필요함.
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


void UBattleTableManagerSystem::UseBossSkill(FBossSkillData SkillData, ABossSkillActor* RefActor) {
	FCommonStatData* TargetStatData = nullptr;

	int32 SkillIndexes[2] = { SkillData.SkillIndex_1, SkillData.SkillIndex_2 };
	int32 SkillTargets[2] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2 };

	for (int Sequence = 0; Sequence < 2; Sequence++) {
		if (SkillTargets[Sequence] == TARGET_PEPPY) {
			TargetStatData = &CurPeppyStat;
			TargetBuffComponent = PeppyBuffComponent;
		}
		else if (SkillTargets[Sequence] == TARGET_BOSS) {
			TargetStatData = &CurBossStat;
			TargetBuffComponent = PeppyBuffComponent;
		}
		else {
//			NTLOG(Error, TEXT("Target set fail : BossSkillTargets[%d] is invalid value(%d)"), IndexCount, SkillIndexes[IndexCount]);
			break;
		}
		OperateBossSkillByIndex(Sequence, TargetStatData, TryGetCurEffectIndexBossSkillDataSet(Sequence, &SkillData), RefActor);
	}

	if (CurPeppyStat.EP <= 0) {

		BattleManager->SetActorTickEnabled(false);
		BattleManager->GetBossActor()->SetActorTickEnabled(false);
		CurPeppyStat.EP = 0;
		BattleManager->GetPeppyActor()->Die();
	}
}

void UBattleTableManagerSystem::OperateBossSkillByIndex(int32 EffectSequence, FCommonStatData* TargetStatData, FCurEffectIndexSkillData* SkillData, ABossSkillActor* RefActor) {
	if (SkillData == nullptr) {
		NTLOG(Error, TEXT("SkillData is invalid for operation!"));
		return;
	}

	if (SkillData->SkillIndex == 1) {
		RefActor->CustomSkillOperation(EffectSequence, *SkillData);
	}
	/*
	*	11 단순 공격: Target의 EP를 즉시 N만큼 깎음.
	*/
	else if (SkillData->SkillIndex == 11) {
		TargetStatData->EP -= SkillData->Value_N;
		NTLOG(Log, TEXT("[Boss 11] Attack damage %lf : %d"), SkillData->Value_N, TargetStatData->EP);
	}
	/*
	*	13 랜덤 공격: Target의 EP를 즉시 N 이상 M 이하의 랜덤한 짝수 수치만큼 깎음.
	*/
	else if (SkillData->SkillIndex == 13) {
		TargetStatData->EP -= CalcUtil::RandEvenNumberInRange(SkillData->Value_N, SkillData->Value_M);
		NTLOG(Log, TEXT("[Boss 13] Random attack damage %lf : %d"), SkillData->Value_N, TargetStatData->EP);
	}
	/*
	*	16 제한 디버프-긍정: 대상의 모든 긍정적 버프 중 랜덤으로 N개 제거
	*/
	else if (SkillData->SkillIndex == 16) {
		TargetBuffComponent->RemoveRandomPositiveBuff(SkillData->Value_N);
	}
	/*
	*	34 반사: 대상이 T턴동안 상대에게 데미지를 받을 때마다 N만큼의 데미지를 돌려줌
	*/
	else if (SkillData->SkillIndex == 34) {

	}
	/*
	*	54 지속 데미지(출혈): 대상의 HP가 각 턴마다 N만큼 T턴동안 감소
	*/
	else if (SkillData->SkillIndex == 54) {
		TArray<int32> PeriodicDamages;
		PeriodicDamages.Init(SkillData->Value_N, SkillData->Value_T);

		Cast<APeppy>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddCumulativeDamageBeforeStartTurn(SkillData->SkillId, PeriodicDamages);
		NTLOG(Log, TEXT("[Boss 54] Periodic attack damage %lf in %lf Turn : %d"), SkillData->Value_N, SkillData->Value_T, TargetStatData->EP);
	}
	else {
		NTLOG(Error, TEXT("No Boss skill index %d"), SkillData->SkillIndex);
	}

}

void UBattleTableManagerSystem::UsePeppySkill(FPeppySkillData SkillData, APeppySkillActor* RefActor) {
	FCommonStatData* TargetStatData = nullptr;

	CurPeppyStat.Energy -= SkillData.Cost;

	int32 SkillIndexes[3] = { SkillData.SkillIndex_1, SkillData.SkillIndex_2, SkillData.SkillIndex_3 };
	int32 SkillTargets[3] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2, SkillData.SkillTarget_3 };

	for (int Sequence = 0; Sequence < 3; Sequence++) {
		if (SkillTargets[Sequence] == TARGET_PEPPY) {
			TargetStatData = &CurPeppyStat;
		}
		else if (SkillTargets[Sequence] == TARGET_BOSS) {
			TargetStatData = &CurBossStat;
		}
		else {
//			NTLOG(Error, TEXT("Target set fail : PeppySkillTargets[%d] is invalid value(%d)"), IndexCount, SkillIndexes[IndexCount]);
			break;;
		}

		OperatePeppySkillByIndex(Sequence, TargetStatData, TryGetCurEffectIndexPeppySkillDataSet(Sequence, &SkillData), RefActor);
	}

	if (CurBossStat.EP <= 0) {
		NTLOG(Error, TEXT("Boss die"));
		CurBossStat.EP = 0;
		
		BattleManager->SetActorTickEnabled(false);
		BattleManager->EndBattle();
		BattleManager->GetBossActor()->Die();
	}
}

void UBattleTableManagerSystem::OperatePeppySkillByIndex(int32 EffectSequence, FCommonStatData* TargetStatData, FCurEffectIndexSkillData* SkillData, APeppySkillActor* RefActor) {
	if (SkillData == nullptr) {
		NTLOG(Error, TEXT("SkillData is invalid for operation!"));
		return;
	}

	if (SkillData->SkillIndex == 1) {
		RefActor->CustomSkillOperation(EffectSequence, *SkillData);
	}
	/*
	*	11 단순 공격: Target의 EP를 즉시 N만큼 깎음.
	*/
	else if (SkillData->SkillIndex == 11) {
		TargetStatData->EP -= SkillData->Value_N;
		NTLOG(Log, TEXT("[Boss 11] Attack damage %lf : %d"), SkillData->Value_N, TargetStatData->EP);
	}
	/*
	*	13 랜덤 공격: Target의 EP를 즉시 N 이상 M 이하의 랜덤한 짝수 수치만큼 깎음.
	*/
	else if (SkillData->SkillIndex == 13) {
		TargetStatData->EP -= CalcUtil::RandEvenNumberInRange(SkillData->Value_N, SkillData->Value_M);
		NTLOG(Log, TEXT("[Boss 13] Random attack damage %lf : %d"), SkillData->Value_N, TargetStatData->EP);
	}
	/*
	*	54 지속 데미지(출혈): 대상의 HP가 각 턴마다 N만큼 T턴동안 감소
	*/
	else if (SkillData->SkillIndex == 54) {
		// Boss에게 CumulativeDamage 필드를 만들어야 함.
		/*
		TArray<int32> PeriodicDamages;
		PeriodicDamages.Init(SkillData->Value_N, SkillData->Value_T);

		Cast<APeppy>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddCumulativeDamageBeforeStartTurn(SkillData->SkillId, PeriodicDamages);

		CurPeppyStat.Energy -= SkillData->Cost;
		NTLOG(Log, TEXT("[Boss 54] Periodic attack damage %lf in %lf Turn : %d"), SkillData->Value_N, SkillData->Value_T, TargetStatData->EP);
		*/
		NTLOG(Error, TEXT("Not implement. See description in script"));
	}
	else {
		NTLOG(Error, TEXT("No Peppy skill index %d"), EffectSequence);
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

FPeppyStatData* UBattleTableManagerSystem::GetCurPeppyStatRef() {
	return &CurPeppyStat;
}

FBossStatData* UBattleTableManagerSystem::GetCurBossStatRef() {
	return &CurBossStat;
}

FName UBattleTableManagerSystem::GetCurrentBlueprintClassName() {
	return *(GetClass()->GetFName().ToString());
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