// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/DataTable.h"

#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

UENUM(BlueprintType)
enum class EBuffType : uint8 {
	AttackIncrease		UMETA(DisplayName = "AttackIncrease"),
	ReflexiveAttack		UMETA(DisplayName = "ReflexiveAttack"),
	PeriodicRecovery	UMETA(DisplayName = "PeriodicRecovery"),
	AttackDecrease		UMETA(DisplayName = "AttackDecrease"),
	PeriodicAttack		UMETA(DisplayName = "PeriodicAttack"),
	Blind				UMETA(DisplayName = "Blind"),
	SpeedDecrease		UMETA(DisplayName = "SpeedDecrease"),
	Confuse				UMETA(DisplayName = "Confuse"),
	Seal				UMETA(DisplayName = "Seal"),
	IntervalIncrease	UMETA(DisplayName = "IntervalIncrease"),
	SpecialMpIncrease	UMETA(DisplayName = "SpecialMpIncrease"),
	Shield				UMETA(DisplayName = "Shield"),
	Revive				UMETA(DisplayName = "Revive"),
	Mood				UMETA(DisplayName = "Mood"),
	Warning				UMETA(DisplayName = "Warning"),
	RecoveryEnergy		UMETA(DisplayName = "RecoveryEnergy"),
};

UENUM(BlueprintType)
enum class EBuffTermType : uint8 {
	Turn	UMETA(DisplayName = "Turn"),
	Second	UMETA(DisplayName = "Second"),
};

UENUM(BlueprintType)
enum class EBuffPositivenessType : uint8 {
	Positive	UMETA(DisplayName = "Positive"),
	Negative	UMETA(DisplayName = "Negative"),
};

USTRUCT()
struct FBuffTable : public FTableRowBase {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 BuffType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffDescript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BuffIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float defaultN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float defaultM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float defaultT;
};

USTRUCT(BlueprintType)
struct FBuffData {
	GENERATED_BODY()
	
public:
	FBuffData() : SourceId("-1"), BuffType(0), BuffTermType(EBuffTermType::Turn), Duration(0), Value_N(0), Value_M(0), Value_T(0) {}

	FBuffData(FString SourceId, int32 BuffType, EBuffTermType BuffDurationType, int32 Duration, int32 Value_N, int32 Value_M, int32 Value_T) {
		this->SourceId = SourceId;
		this->BuffType = BuffType;
		this->BuffTermType = BuffDurationType;
		this->Duration = Value_T;
		this->Value_N = Value_N;
		this->Value_M = Value_M;
		this->Value_T = Value_T;
	}
	
	FBuffData(FString SourceId, FBuffTable* BuffTableData) {
		this->SourceId = SourceId;

		bool isTurnType = false;
		for (auto Buff : BuffListPerTurn) {
			if (int32(Buff) == int32(BuffTableData->BuffType)) {
				isTurnType = true;
				break;
			}
		}

		this->BuffType = BuffTableData->BuffType;
		this->BuffTermType = isTurnType ? EBuffTermType::Turn : EBuffTermType::Second;
		this->Duration = BuffTableData->defaultT;
		this->Value_N = BuffTableData->defaultN;
		this->Value_M = BuffTableData->defaultM;
		this->Value_T = BuffTableData->defaultT;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString SourceId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 BuffType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EBuffTermType BuffTermType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Value_N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Value_M;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Value_T;

	FBuffData* CreateBuffData(FString _SourceId, FBuffTable* BuffTableData) {
		// TArray<EBuffType>의 Contains 메서드로 간단하게 구현할 수 있을 줄 알았는데, uenum이 == operator를 지원하지 않음.
		// 해당 연산자 오버로딩을 하려 했지만, enum class 안에 메서드 구현도 불가능함. 
		// 그래서 어쩔 수 없이 아래와 같이 배열 전체를 순회하며 uint32 타입으로의 강제 캐스팅을 통해 비교함.
		bool isTurnTypeBuff = false;
		for (auto Buff : BuffListPerTurn) {
			if (int32(Buff) == int32(BuffTableData->BuffType)) {
				isTurnTypeBuff = true;
				break;
			}
		}

		return new FBuffData(_SourceId, BuffTableData->BuffType, isTurnTypeBuff ? EBuffTermType::Turn : EBuffTermType::Second,
			BuffTableData->defaultT, BuffTableData->defaultN, BuffTableData->defaultM, BuffTableData->defaultT);
	}

	TArray<EBuffType> BuffListPerTurn = {
		EBuffType::AttackIncrease,
		EBuffType::ReflexiveAttack,
		EBuffType::PeriodicRecovery,
		EBuffType::AttackDecrease,
		EBuffType::PeriodicAttack,
		EBuffType::SpeedDecrease,
		EBuffType::Seal,
		EBuffType::IntervalIncrease,
		EBuffType::SpecialMpIncrease,
		EBuffType::Shield,
		EBuffType::Revive,
		EBuffType::Mood,
		EBuffType::Warning,
		EBuffType::RecoveryEnergy
	};

	TArray<EBuffType> BuffListPerSecond = {
		EBuffType::PeriodicRecovery,
		EBuffType::Blind,
		EBuffType::Confuse
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuffComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
		TMap<EBuffType, FBuffData> HasPositiveBuffs_PerTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
		TMap<EBuffType, FBuffData> HasPositiveBuffs_PerSecond;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
		TMap<EBuffType, FBuffData> HasNegativeBuffs_PerTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
		TMap<EBuffType, FBuffData> HasNegativeBuffs_PerSecond;

private:
	const TMap<EBuffType, FString> BuffTypeToStringMap = {
		{ EBuffType::AttackIncrease,	"AttackIncrease" },
		{ EBuffType::ReflexiveAttack,	"ReflexiveAttack"},
		{ EBuffType::PeriodicRecovery,	"PeriodicRecovery"},
		{ EBuffType::AttackDecrease,	"AttackDecrease" },
		{ EBuffType::PeriodicAttack,	"PeriodicAttack"},
		{ EBuffType::Blind,				"Blind" },
		{ EBuffType::SpeedDecrease,		"SpeedDecrease" },
		{ EBuffType::Confuse,			"Confuse" },
		{ EBuffType::Seal,				"Seal" },
		{ EBuffType::IntervalIncrease,	"IntervalIncrease" },
		{ EBuffType::SpecialMpIncrease,	"SpecialMpIncrease" },
		{ EBuffType::Shield,			"Shield" },
		{ EBuffType::Revive,			"Revive" },
		{ EBuffType::Mood,				"Mood" },
		{ EBuffType::Warning,			"Warning" },
		{ EBuffType::RecoveryEnergy,	"RecoveryEnergy" }
	};

	UPROPERTY()
	class UDataTable* BuffTable;

public:
	/* 자신에게 적용된 BuffTyp의 버프를 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemoveBuff(EBuffType BuffType);
	/* 자신에게 적용된 랜덤한 긍정적 버프를 Num개 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemoveRandomPositiveBuff(int32 Num);
	/* 자신에게 적용된 랜덤한 부정적 버프를 Num개 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemoveRandomNegativeBuff(int32 Num);
	/* 자신에게 적용된 모든 긍정적 버프를 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemoveAllPositiveBuff();
	/* 자신에게 적용된 모든 부정적 버프를 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemoveAllNegativeBuff();
	/* 자신에게 적용된 모든 버프를 제거합니다.*/
	UFUNCTION(BlueprintCallable)	
	void RemoveAllBuff();
	/* 자신에게 TermType을 주기로 Duration만큼의 지속하는 BuffType의 버프를 부여합니다.*/
	UFUNCTION(BlueprintCallable) 
	void AcquireBuff(EBuffType BuffType, FString Source);

	void ElapseSecond();
	void ElapseTurn();
	
	void ExpireBuff(TMap<EBuffType, FBuffData>* BuffMap, EBuffType BuffType);

	bool HasBuff(EBuffType BuffType);
};
