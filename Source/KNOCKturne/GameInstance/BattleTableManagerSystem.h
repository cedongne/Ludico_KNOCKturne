// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Component/StatComponent.h"
#include "Component/SpecialSkillComponent.h"
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

	FPeppySkillData() : SkillId("-1"), SkillGroupCode("Default"), SkillAcquire(0), Cost(0), SkillStance("Default"), SkillCoolTurn(0), SkillDamageDelay(0.0f),
		SkillIndex_1(0), Probability_1(0.0f), SkillTarget_1(-1), Value_1_N(0), Value_1_M(0), Value_1_T(0), BuffCode_1("-1"),
		SkillIndex_2(0), Probability_2(0.0f), SkillTarget_2(-1), Value_2_N(0), Value_2_M(0), Value_2_T(0), BuffCode_2("-1"),
		SkillIndex_3(0), Probability_3(0.0f), SkillTarget_3(-1), Value_3_N(0), Value_3_M(0), Value_3_T(0), BuffCode_3("-1"),
		SkillAnimation("-1"), SkillEffect_1("-1"), SkillEffect_2("-1"), SkillSound_1("-1"), SkillSound_2("-1"), BossEffect_1("-1"), BossEffect_2("-1"), BossSound_1("-1"), BossSound_2("-1"), SkillIcon(nullptr), SkillDescript("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillGroupCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillAcquire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillStance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillCoolTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SkillDamageDelay;
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
	int32 Value_1_T;
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
	int32 Value_2_T;
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
	int32 Value_3_T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillEffect_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillEffect_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillSound_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillSound_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossEffect_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossEffect_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossSound_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BossSound_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> SkillIcon;
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

	FBossSkillSpawnData() : SkillObjectClass(nullptr), SkillTransform(TArray<FTransform>()) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UClass* SkillObjectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FTransform> SkillTransform;

	static FBossSkillSpawnData SetBossSkillSpawnData(UClass* _SkillObjectClass, TArray<FTransform> _SkillTrnasforms);
};

USTRUCT(BlueprintType)
struct FCurEffectIndexSkillData {
	GENERATED_BODY()
	
	FCurEffectIndexSkillData() : SkillId("-1"), SkillIndex(0), Probability(0.0f), SkillTarget(0), Value_N(0.0f), Value_M(0.0f), Value_T(0.0f), BuffCode("-1"), Cost(0) {}
	
	void SetCurEffectIndexStatData(FString _SkillId, int32 _SkillIndex, float _Probability, int32 _SkillTarget, float _Value_N, float _Value_M, float _Value_T, FString _BuffCode, int32 _Cost) {
		SkillId = _SkillId;
		SkillIndex = _SkillIndex;
		Probability = _Probability;
		SkillTarget = _SkillTarget;
		Value_N = _Value_N;
		Value_M = _Value_M;
		Value_T = _Value_T;
		BuffCode = _BuffCode;
		Cost = _Cost;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SkillId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Probability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 SkillTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value_T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Cost;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase {
	GENERATED_BODY()

	FItemData() : ItemTarget(-1), TouchColumn("-1"), value1N(0), value1M(0),
		MaxCount(0), ItemIcon(nullptr), ItemDescript("-1"), 
		ItemEasterEgg("-1"), ItemEasterEgg_Character("-1") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 ItemTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString TouchColumn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float value1N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float value1M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UTexture2D> ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemDescript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemEasterEgg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemEasterEgg_Character;
};

UCLASS()
class KNOCKTURNE_API UBattleTableManagerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UBattleTableManagerSystem();
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	FBattleTableInitDelegate BattleTableInitDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* BossContactSkillTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* BossNonContactSkillTable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Table")
	class UDataTable* PeppySkillTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataStructure")
	TMap<FString, FBossSkillSpawnData> BossSkillSpawnDataMap;

	class UActorManagerSystem* ActorManagerSystem;
	class ABattleManager* BattleManager;
	class UBattleManagerSystem* BattleManagerSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PeppySkillProbabilisticSequence;

public:
	UDataTable* GetPeppySkillTable();
	TMap<FString, FPeppySkillData> GetCurPeppySkillData();

	FPeppyStatData GetPeppyStatDataOnTable(FString DataType);
	FBossStatData GetBossStatDataOnTable(FString DataType);

	UFUNCTION(BlueprintCallable)
	FName GetCurrentBlueprintClassName();

	UFUNCTION(BlueprintCallable)
	void TryUpdateCurSkillDataCost(FString BPClassName, float Value);

private:
	class UKNOCKturneGameInstance* GameInstance;
	class APeppy* PeppyActor = nullptr;

	UPROPERTY()
	class UDataTable* PeppyStatDataTable;
	UPROPERTY()
	class UDataTable* BossStatDataTable;

	void SetBossSkillSpawnDataTable();
	void AddBossSkillSpawnDataToMap(FString SkillName, TCHAR* SkillObjectPath, TArray<FVector> SpawnLocation, TArray<FRotator> SpawnRotation);

	TMap<FString, FPeppySkillData> CurPeppySkillData;

public:
	UFUNCTION(BlueprintCallable)
	bool TryUseBossSkillSequential(FBossSkillData SkillData, ABossSkillActor* RefActor);
	UFUNCTION(BlueprintCallable)
	bool TryUseBossSkillProbabilistic(FBossSkillData SkillData, ABossSkillActor* RefActor);
	UFUNCTION(BlueprintCallable)
	bool TryUsePeppySkillSequential(FPeppySkillData SkillData, APeppySkillActor* RefActor);
	UFUNCTION(BlueprintCallable)
	bool TryUsePeppySkillProbabilistic(FPeppySkillData SkillData, APeppySkillActor* RefActor);

	UFUNCTION(BlueprintCallable)
	void OperateSkillByIndex(int32 EffectSequence, AActor* TargetActor, FCurEffectIndexSkillData SkillData, class ACommonSkillActor* SkillActor);
	UFUNCTION(BlueprintCallable)
	FCurEffectIndexSkillData TryGetCurEffectIndexSpecialSkillDataSet(FSpecialSkillTable CurStatData);

private:
	// ���� ������ ȿ���� �� ��° �ε��������� ���� �� ���� 
	FCurEffectIndexSkillData CurEffectIndexBossSkillDataSet;
	FCurEffectIndexSkillData CurEffectIndexPeppySkillDataSet;

	FCurEffectIndexSkillData* TryGetCurEffectIndexBossSkillDataSet(int32 Index, FBossSkillData* CurStatData);
	FCurEffectIndexSkillData* TryGetCurEffectIndexPeppySkillDataSet(int32 Index, FPeppySkillData* CurStatData);
};