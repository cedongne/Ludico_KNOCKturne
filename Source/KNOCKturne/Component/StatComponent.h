// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"

#include "StatComponent.generated.h"

UENUM(BlueprintType)
enum class FStatType : uint8 {
	EP,
	MaxEP,
	DefenseDamage,
	AttackDamage,
	Avd,
	Turn,
	Energy,
	MaxEnergy,
	SlidingCooldown,
	Speed,
	BossMinDelay,
	BossMaxDelay,
	BossStanceCode,
	BossInitStance,
	BossEnergyDrop,
	Cost
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	class ANTBattleGameMode* BattleGameMode = nullptr;


public:
	AActor* GetOwnerActor(AActor* OwnerActor);

	virtual void GetDamaged(float Value);
	virtual bool TryUpdateCurStatData(FStatType StatType, float Value);
	virtual bool TryUpdateMaxStatData(FStatType StatType, float Value);
	virtual void CreateDamageText(float Value);
};
