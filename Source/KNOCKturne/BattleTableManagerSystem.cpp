// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTableManagerSystem.h"
#include "Kismet/KismetMathLibrary.h"

UBattleTableManagerSystem::UBattleTableManagerSystem() {
	FString BossSkilTablePath = TEXT("/Game/Assets/DataTable/Ep1BossSkillTable.Ep1BossSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BOSSKILLTABLE(*BossSkilTablePath);
	NTCHECK(DT_BOSSKILLTABLE.Succeeded());

	BossSkillTable = DT_BOSSKILLTABLE.Object;

	SetBossSkillSpawnDataTable();
}

void UBattleTableManagerSystem::SetBossSkillSpawnDataTable() {
	TArray<FVector> TempSpawnLocation;
	TArray<FRotator> TempSpawnRotation;

	// �𸮾� ������ �󿡼� �������Ͱ�	Roll, Pitch, Yaw
	// C++ ��ũ��Ʈ �󿡼� �������Ͱ�		Pitch, Yaw, Roll	���̶�� ���� ������ ��.

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