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
	void GetDamaged(float Damage);

	FOnHPIsZeroDelegate OnHPIsZero;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

private:
	struct FPeppyStatData* CurrentStatData = nullptr;

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
