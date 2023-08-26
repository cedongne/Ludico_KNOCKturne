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
	/* �ڽſ��� ����� BuffId�� ���� ������ ������ �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemovePositiveBuff(FString BuffId);
	/* �ڽſ��� ����� BuffId�� ���� ������ ������ �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemoveNegativeBuff(FString BuffId);
	/* �ڽſ��� ����� ������ ������ ������ Num�� �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemoveRandomPositiveBuff(int32 Num);
	/* �ڽſ��� ����� ������ ������ ������ Num�� �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemoveRandomNegativeBuff(int32 Num);
	/* �ڽſ��� ����� ��� ������ ������ �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemoveAllPositiveBuff();
	/* �ڽſ��� ����� ��� ������ ������ �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemoveAllNegativeBuff();
	/* �ڽſ��� ����� ��� ������ �����մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void RemoveAllBuff();
};
