// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuffComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, float> HasPositiveBuffs_PerTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, float> HasPositiveBuffs_PerSecond;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, float> HasNegativeBuffs_PerTurn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Has")
	TMap<FString, float> HasNegativeBuffs_PerSecond;

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
};
