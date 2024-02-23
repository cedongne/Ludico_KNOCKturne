// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"

#include "StatComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"

#include "PeppyStatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UPeppyStatComponent : public UStatComponent
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

	FPeppyStatData MinStatData;
	FPeppyStatData MaxStatData;

public:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly)
	FPeppyStatData CurStatData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanBeDamaged = true;

	UFUNCTION(BlueprintCallable)
	void GetDamaged(float Value) override;

	UFUNCTION(BlueprintCallable)
	virtual bool TryUpdateCurStatData (FStatType StatType, float Value) override;

	UFUNCTION(BlueprintCallable)
	void CreateDamageText(float Value) override;
};
