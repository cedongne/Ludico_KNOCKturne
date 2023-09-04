// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

UENUM(BlueprintType)
enum class EBuffType : uint8 {
	Slow				UMETA(DisplayName = "Slow"),
	Bleeding			UMETA(DisplayName = "Bleeding"),
	Blind				UMETA(DisplayName = "Blind"),
	Confuse				UMETA(DisplayName = "Confuse"),
	Reflect				UMETA(DisplayName = "Reflect"),
	IntervalIncrease	UMETA(DisplayName = "IntervalIncrease"),
	Reinforce			UMETA(DisplayName = "Reinforce"),
	Weaken				UMETA(DisplayName = "Weaken"),
	Seal				UMETA(DisplayName = "Seal"),
	Shield				UMETA(DisplayName = "Shield"),
	EnergyforRecovery	UMETA(DisplayName = "EnergyforRecovery"),
	EnergyRegen			UMETA(DisplayName = "EnergyRegen"),
	Dodge				UMETA(DisplayName = "Dodge"),
	Friction			UMETA(DisplayName = "Friction"),
	Mood				UMETA(DisplayName = "Mood"),
	Warning				UMETA(DisplayName = "Warning"),
};

UENUM(BlueprintType)
enum class EBuffDataType : uint8 {
	Positive_Turn	UMETA(DisplayName = "Positive_Turn"),
	Positive_Second	UMETA(DisplayName = "Positive_Second"),
	Negative_Turn	UMETA(DisplayName = "Negative_Turn"),
	Negative_Second	UMETA(DisplayName = "Negative_Second")
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
	TMap<FString, int32> HasPositiveBuffs_PerTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, int32> HasPositiveBuffs_PerSecond;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, int32> HasNegativeBuffs_PerTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, int32> HasNegativeBuffs_PerSecond;

public:
	/* 자신에게 적용된 BuffId를 가진 긍정적 버프를 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemovePositiveBuff(FString BuffId);
	/* 자신에게 적용된 BuffId를 가진 부정적 버프를 제거합니다.*/
	UFUNCTION(BlueprintCallable)
	void RemoveNegativeBuff(FString BuffId);
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
	void AcquireBuff(EBuffType BuffType, EBuffDataType TermType, FString BuffName, int32 Duration);

	void ElapseSecond();
	void ElapseTurn();
	
	void ExpireBuff(TMap<FString, int32>* BuffMap, FString BuffId);
};
