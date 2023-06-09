// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTableManagerSystem.h"
#include "BossSkillActor.h"
#include "CalcUtil.h"

#define TARGET_PEPPY 0
#define TARGET_BOSS 1

void UBattleTableManagerSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

UBattleTableManagerSystem::UBattleTableManagerSystem() {
	FString BossSkilTablePath = TEXT("/Game/Assets/DataTable/Ep1BossSkillTable.Ep1BossSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSKILLTABLE(*BossSkilTablePath);
	NTCHECK(DT_BOSSKILLTABLE.Succeeded());
	BossSkillTable = DT_BOSSKILLTABLE.Object;
	SetBossSkillSpawnDataTable();

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
}

void UBattleTableManagerSystem::SetBossSkillSpawnDataTable() {
	TArray<FVector> TempSpawnLocation;
	// �𸮾� ������ �󿡼� �������Ͱ�	Roll, Pitch, Yaw
	// C++ ��ũ��Ʈ �󿡼� �������Ͱ�		Pitch, Yaw, Roll	���̶�� ���� ������ ��.
	TArray<FRotator> TempSpawnRotation;


	/// SweptGarden
	TempSpawnLocation.Empty();
	TempSpawnRotation.Empty();
	TempSpawnLocation.Push(FVector(800.0f, 330.0f, -85.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 0.0f, 0.0f));
	TempSpawnLocation.Push(FVector(1180.0f, 810.0f, -85.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 90.0f, 0.0f));
	TempSpawnLocation.Push(FVector(710.0f, 1220.0f, -85.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 180.0f, 0.0f));
	TempSpawnLocation.Push(FVector(310.0f, 740.0f, -85.0f));
	TempSpawnRotation.Push(FRotator(0.0f, 270.0f, 0.0f));

	AddBossSkillSpawnDataToMap(
		"SweptGarden",
		TEXT("/Game/Blueprints/Skills/Boss/Ep1/BP_SweptGarden.BP_SweptGarden_C"),
		TempSpawnLocation,
		TempSpawnRotation
	);

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
		NTLOG(Warning, TEXT("Parameter is invalid. Number of element in transform array is different!"));
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

	BossSkillSpawnDataMap.Add("SweptGarden", FBossSkillSpawnData::SetBossSkillSpawnData(TempSkillObjectClass, TempSkillTransform));

	NTLOG(Warning, TEXT("Skill is loaded"));
}


void UBattleTableManagerSystem::UseBossSkill(FBossSkillData SkillData) {
	FCommonStatData* TargetStatData = nullptr;

	int32 SkillIndexes[2] = { SkillData.SkillIndex_1, SkillData.SkillIndex_2 };
	int32 SkillTargets[2] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2 };

	for (int IndexCount = 0; IndexCount < 2; IndexCount++) {
		if (SkillTargets[IndexCount] == TARGET_PEPPY) {
			TargetStatData = &CurPeppyStat;
		}
		else if (SkillTargets[IndexCount] == TARGET_BOSS) {
			TargetStatData = &CurBossStat;
		}
		else {
			NTLOG(Warning, TEXT("Target set fail : BossSkillTargets[%d] is invalid value(%d)"), IndexCount, SkillIndexes[IndexCount]);
			return;
		}

		OperateBossSkillByIndex(SkillIndexes[IndexCount], TargetStatData, &SkillData);
	}
}

void UBattleTableManagerSystem::OperateBossSkillByIndex(int32 SkillIndex, FCommonStatData* TargetStatData, FBossSkillData* SkillData) {
	switch (SkillIndex) {
		/*
			11 �ܼ� ���� : Target�� EP�� ��� N��ŭ ����.
		*/
	case 11:
		TargetStatData->EP -= SkillData->Value_1_N;
		NTLOG(Warning, TEXT("[Boss 11] Attack damage : %d"), TargetStatData->EP);
		break;
		/*
			13 ���� ���� : Target�� EP�� ��� N �̻� M ������ ������ ¦�� ��ġ��ŭ ����.
		*/
	case 13:
		TargetStatData->EP -= CalcUtil::RandEvenNumberInRange(SkillData->Value_1_N, SkillData->Value_1_M);
		NTLOG(Warning, TEXT("[Boss 13] Random attack damage : %d"), TargetStatData->EP);
		break;
	default:
		NTLOG(Warning, TEXT("No Skill index %d"), SkillIndex);
	}
}

void UBattleTableManagerSystem::UsePeppySkill(FPeppySkillData SkillData) {
	FCommonStatData* TargetStatData = nullptr;

	int32 SkillIndexes[2] = { SkillData.SkillIndex_1, SkillData.SkillIndex_2 };
	int32 SkillTargets[2] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2 };

	for (int IndexCount = 0; IndexCount < 2; IndexCount++) {
		if (SkillTargets[IndexCount] == TARGET_PEPPY) {
			TargetStatData = &CurPeppyStat;
		}
		else if (SkillTargets[IndexCount] == TARGET_BOSS) {
			TargetStatData = &CurBossStat;
		}
		else {
			NTLOG(Warning, TEXT("Target set fail : PeppySkillTargets[%d] is invalid value(%d)"), IndexCount, SkillIndexes[IndexCount]);
			return;
		}

		OperatePeppySkillByIndex(SkillIndexes[IndexCount], TargetStatData, &SkillData);
	}
}

void UBattleTableManagerSystem::OperatePeppySkillByIndex(int32 SkillIndex, FCommonStatData* TargetStatData, FPeppySkillData* SkillData) {
	switch (SkillIndex) {
		/*
			11 �ܼ� ���� : Target�� EP�� ��� N��ŭ ����.
		*/
	case 11:
		TargetStatData->EP -= SkillData->Value_1_N;
		NTLOG(Warning, TEXT("[Peppy 11] Attack damage : %d"), TargetStatData->EP);
		break;
		/*
			13 ���� ���� : Target�� EP�� ��� N �̻� M ������ ������ ¦�� ��ġ��ŭ ����.
		*/
	case 13:
		TargetStatData->EP -= CalcUtil::RandEvenNumberInRange(SkillData->Value_1_N, SkillData->Value_1_M);
		CurPeppyStat.Energy -= SkillData->Cost;
		NTLOG(Warning, TEXT("[Peppy 13] Random attack damage : %d"), TargetStatData->EP);
		break;
	default:
		NTLOG(Warning, TEXT("No Skill index %d"), SkillIndex);
	}
}

FPeppyStatData UBattleTableManagerSystem::GetPeppyStatDataOnTable(FString DataType) {
	FPeppyStatData* statData = PeppyStatDataTable->FindRow<FPeppyStatData>(*DataType, TEXT(""));
	if (statData == nullptr) {
		NTLOG(Warning, TEXT("Load fail"));
		return FPeppyStatData::FPeppyStatData();
	}
	return *statData;
}

FBossStatData UBattleTableManagerSystem::GetBossStatDataOnTable(FString DataType) {
	FBossStatData* statData = BossStatDataTable->FindRow<FBossStatData>(*DataType, TEXT(""));
	if (statData == nullptr) {
		NTLOG(Warning, TEXT("Load fail"));
		return FBossStatData::FBossStatData();
	}
	return *statData;
}

UDataTable* UBattleTableManagerSystem::GetPeppySkillTable() {
	return PeppySkillTable;
}

FPeppyStatData UBattleTableManagerSystem::GetCurPeppyStatReadOnly() {
	return CurPeppyStat;
}

FBossStatData UBattleTableManagerSystem::GetCurBossStatReadOnly() {
	return CurBossStat;
}

FPeppyStatData* UBattleTableManagerSystem::GetCurPeppyStatRef() {
	return &CurPeppyStat;
}

FBossStatData* UBattleTableManagerSystem::GetCurBossStatRef() {
	return &CurBossStat;
}