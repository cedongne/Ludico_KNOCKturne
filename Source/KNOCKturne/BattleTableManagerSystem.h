// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattleTableManagerSystem.generated.h"


USTRUCT(BlueprintType)
struct FBossSkillData : public FTableRowBase {
	GENERATED_BODY()

	FBossSkillData() : BossSkillID("-1"), SkillStance("Default"), SkillCoolTurn(0), SprayEnergy(0), SkillDelayTime(0.0f), SkillCastTime(0.0f), ObjectSpeed(0.0f),
		SkillIndex_1(0), Probability_1(0.0f), SkillTarget_1(-1), Value_1_N(0), Value_1_M(0), Value_1_T(0), BuffCode_1("-1"),
		SkillIndex_2(0), Probability_2(0.0f), SkillTarget_2(-1), Value_2_N(0), Value_2_M(0), Value_2_T(0), BuffCode_2("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossSkillID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillStance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillCoolTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SprayEnergy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SkillDelayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SkillCastTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ObjectSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillIndex_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Probability_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillTarget_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_1_N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_1_M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_1_T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillIndex_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Probability_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillTarget_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_2_N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_2_M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_2_T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode_2;
};

USTRUCT(BlueprintType)
struct FBossSkillSpawnData {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UClass* SkillObjectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FTransform> SkillTransform;

	static FBossSkillSpawnData SetBossSkillSpawnData(UClass* _SkillObjectClass, TArray<FTransform> _SkillTrnasforms);
};

UCLASS()
class KNOCKTURNE_API UBattleTableManagerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UBattleTableManagerSystem();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* BossSkillTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Table")
	TMap<FString, FBossSkillSpawnData> BossSkillSpawnDataMap;

private:
	void SetBossSkillSpawnDataTable();
	void AddBossSkillSpawnDataToMap(FString SkillName, TCHAR* SkillObjectPath, TArray<FVector> SpawnLocation, TArray<FRotator> SpawnRotation);
};
