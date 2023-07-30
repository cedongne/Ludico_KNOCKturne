// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"

#include "BattleTableManagerSystem.h"
#include "BattleManagerSystem.h"

#include "PeppyStatComponent.generated.h"

UENUM(BlueprintType)
enum class PeppyStatType : uint8 {
	EP,
	MaxEP,
	Energy,
	MaxEnergy,
	SlidingCooldown,
	Speed,
	DefenseDamage,
	AttackDamage,
	Avd,
	Turn
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UPeppyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPeppyStatComponent();

	void SetDefaultStat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;


private:
	class APeppy* PeppyActor;

	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UBattleManagerSystem* BattleManagerSystem;

	UPROPERTY(Transient, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FPeppyStatData CurStatData;
	FPeppyStatData MinStatData;
	FPeppyStatData MaxStatData;

public:
	UFUNCTION(BlueprintCallable)
	bool TryUpdateCurStatData(PeppyStatType StatType, float Value);
};
