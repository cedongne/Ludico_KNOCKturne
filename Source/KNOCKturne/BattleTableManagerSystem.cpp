// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTableManagerSystem.h"
#include "BossSkillActor.h"

void UBattleTableManagerSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

UBattleTableManagerSystem::UBattleTableManagerSystem() {
	FString BossSkilTablePath = TEXT("/Game/Assets/DataTable/Ep1BossSkillTable.Ep1BossSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSKILLTABLE(*BossSkilTablePath);
	NTCHECK(DT_BOSSKILLTABLE.Succeeded());
	BossSkillTable = DT_BOSSKILLTABLE.Object;
	SetBossSkillSpawnDataTable();

	FString PeppySkilTablePath = TEXT("/Game/Assets/DataTable/PeppySkillTable.PeppySkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSKILLTABLE(*PeppySkilTablePath);
	NTCHECK(DT_PEPPYSKILLTABLE.Succeeded());
	PeppySkillTable = DT_PEPPYSKILLTABLE.Object;

	FString PeppyStatDataPath = TEXT("/Game/Assets/DataTable/PeppyStatTable.PeppyStatTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSTATDATATABLE(*PeppyStatDataPath);
	NTCHECK(DT_PEPPYSTATDATATABLE.Succeeded());
	PeppyStatDataTable = DT_PEPPYSTATDATATABLE.Object;

	auto InitPeppyStatData = GetPeppyStatData("Init");
	if (InitPeppyStatData == nullptr) {
		NTLOG(Warning, TEXT("Load fail"));
	}
	else {
		CurPeppyStat = *GetPeppyStatData("Init");
	}
}

void UBattleTableManagerSystem::SetBossSkillSpawnDataTable() {
	TArray<FVector> TempSpawnLocation;
	// 언리얼 에디터 상에선 로테이터가	Roll, Pitch, Yaw
	// C++ 스크립트 상에선 로테이터가		Pitch, Yaw, Roll	순이라는 것을 유의할 것.
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


void UBattleTableManagerSystem::ApplySkillStatData(FBossSkillData SkillData) {
	FCommonStatData* TargetStatData = nullptr;

	int32 SkillIndexes[2] = { SkillData.SkillIndex_1, SkillData.SkillIndex_2 };
	int32 SkillTargets[2] = { SkillData.SkillTarget_1, SkillData.SkillTarget_2 };

	for (int IndexCount = 0; IndexCount < 2; IndexCount++) {
		if (SkillTargets[IndexCount] == 0) {
			TargetStatData = &CurPeppyStat;
		}
		else if (SkillTargets[IndexCount] == 1) {
			TargetStatData = &CurPeppyStat;
			//			TargetStatData = &curboss
		}
		else {
			NTLOG(Warning, TEXT("Target set fail : SkillTargets[%d] is invalid value(%d)"), IndexCount, SkillIndexes[IndexCount]);
			return;
		}

		OperateSkillByIndex(SkillIndexes[IndexCount], TargetStatData, &SkillData);
	}
}

void UBattleTableManagerSystem::OperateSkillByIndex(int32 SkillIndex, FCommonStatData* TargetStatData, FBossSkillData* SkillData) {
	switch (SkillIndex) {
	/*
		11 단순 공격 : Target의 EP를 즉시 N만큼 깎음.
	*/
	case 11:
		TargetStatData->EP -= SkillData->Value_1_N;
	}
}

FPeppyStatData* UBattleTableManagerSystem::GetPeppyStatData(FString DataType) {
	FPeppyStatData* statData = PeppyStatDataTable->FindRow<FPeppyStatData>(*DataType, TEXT(""));
	if (statData == nullptr) {
		return nullptr;
	}
	return statData;
}

UDataTable* UBattleTableManagerSystem::GetPeppySkillTable() {
	return PeppySkillTable;
}

FPeppyStatData UBattleTableManagerSystem::GetCurPeppyStat_BP() {
	return CurPeppyStat;
}

FBossStatData UBattleTableManagerSystem::GetCurBossStat_BP() {
	return CurBossStat;
}