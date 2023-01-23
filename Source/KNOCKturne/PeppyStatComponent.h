// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"
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

	int32 GetCurrentHp();
	void ChangeCurrentHp(int32 Value);

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
	struct FPeppyStatData* CurStatData = nullptr;
	FPeppyStatData* MinStatData = nullptr;
	FPeppyStatData* MaxStatData = nullptr;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHP;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentHP;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxEP;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentEP;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	float SlidingCooldown;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	float LeftSlidingCooltime;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 DamageDecrease;
};
