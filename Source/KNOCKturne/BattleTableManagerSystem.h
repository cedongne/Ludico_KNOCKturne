// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"

#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "BattleTableManagerSystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FBattleTableInitDelegate);

USTRUCT()
struct FCommonStatData : public FTableRowBase {
	GENERATED_BODY()

	public:
	FCommonStatData() : EP(0), MaxEP(0), DefenseDamage(0), AttackDamage(0), Avd(0.0f), Turn(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 EP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxEP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DefenseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Avd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Turn;
};

USTRUCT(BlueprintType)
struct FPeppyStatData : public FCommonStatData {
	GENERATED_BODY()

	public:
	FPeppyStatData() : Energy(0), MaxEnergy(0), SlidingCooldown(3), speed(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxEnergy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SlidingCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float speed;
};

USTRUCT(BlueprintType)
struct FPeppySkillData : public FTableRowBase {
	GENERATED_BODY()

	FPeppySkillData() : SkillId("-1"), SkillGroupCode("Default"), SkillAcquire("1"), Cost(0), SkillStance("Default"), SkillCoolTurn(0), 
		SkillIndex_1(0), Probability_1(0.0f), SkillTarget_1(-1), Value_1_N(0), Value_1_M(0), Value_1_T(0), BuffCode_1("-1"),
		SkillIndex_2(0), Probability_2(0.0f), SkillTarget_2(-1), Value_2_N(0), Value_2_M(0), Value_2_T(0), BuffCode_2("-1"),
		SkillIndex_3(0), Probability_3(0.0f), SkillTarget_3(-1), Value_3_N(0), Value_3_M(0), Value_3_T(0), BuffCode_3("-1"),
		SkillAnimation("-1"), SkillEffect("-1"), SkillSound("-1"), BossEffect("-1"), BossAnimationDelay("-1"), BossSound("-1"), SkillIcon("-1"), SkillDescript{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillAcquire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillStance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillCoolTurn;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillIndex_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Probability_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillTarget_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_3_N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_3_M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_3_T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossAnimationDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillDescript;
};


USTRUCT()
struct FBossStatData : public FCommonStatData {
	GENERATED_BODY()

	FBossStatData() : BossMinDelay(0.0f), BossMaxDelay(0.0f), BossStanceCode("-1"), BossInitStance("-1"), BossEnergyDrop(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float BossMinDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float BossMaxDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossStanceCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossInitStance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 BossEnergyDrop;
};

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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	FBattleTableInitDelegate BattleTableInitDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* BossSkillTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Table")
	TMap<FString, FBossSkillSpawnData> BossSkillSpawnDataMap;

public:
	FPeppyStatData* GetPeppyStatData(FString DataType);
	UFUNCTION(BlueprintCallable)
	FPeppyStatData GetCurPeppyStat_BP();
	UFUNCTION(BlueprintCallable)
	FBossStatData GetCurBossStat_BP();
private:
	class UKNOCKturneGameInstance* GameInstance;

	UPROPERTY()
	class UDataTable* PeppyStatDataTable;
	UPROPERTY()
	class UDataTable* BossStatDataTable;

	FPeppyStatData CurPeppyStat;
	FBossStatData CurBossStat;

	void SetBossSkillSpawnDataTable();
	void AddBossSkillSpawnDataToMap(FString SkillName, TCHAR* SkillObjectPath, TArray<FVector> SpawnLocation, TArray<FRotator> SpawnRotation);

public:
	/* Skill System */
	UFUNCTION(BlueprintCallable)
	void ApplySkillStatData(FBossSkillData SkillIndex);

private:
	void OperateSkillByIndex(int32 SkillIndex, FCommonStatData* TargetStatData, FBossSkillData* SkillData);
	/****************/

};
