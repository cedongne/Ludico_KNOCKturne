// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"

#include "BattleTableManagerSystem.h"

#include "PeppyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UPeppyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPeppyStatComponent();

	void SetDefaultStat();
	FOnHPIsZeroDelegate OnHPIsZero;

	int32 GetCurrentEP();
	void ChangeCurrentEP(int32 Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable)
	void GetDamaged(float Value);
	UFUNCTION(BlueprintCallable)
	void Heal(float Value);
	UFUNCTION(BlueprintCallable)
	void GainEnergy(float Value);
	UFUNCTION(BlueprintCallable)
	void SpendEnergy(float Value);

private:
	class UBattleTableManagerSystem* BattleTableManagerSystem;

	FPeppyStatData CurStatData;
	FPeppyStatData MinStatData;
	FPeppyStatData MaxStatData;


	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentEP;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxEP;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 DefenseDamage;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 AttackDamage;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Avd;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Turn;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentEnergy;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxEnergy;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 SlidingCooldown;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	float LeftSlidingCooltime;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	float speed;

};
