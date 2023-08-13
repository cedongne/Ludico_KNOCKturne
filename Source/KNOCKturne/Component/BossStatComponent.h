// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"

#include "StatComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "Components/ActorComponent.h"

#include "BossStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UBossStatComponent : public UStatComponent
{
	GENERATED_BODY()

public:
	UBossStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class UBattleTableManagerSystem* BattleTableManagerSystem = nullptr;

	class ABoss* BossActor;

	FBossStatData MinStatData;
	FBossStatData MaxStatData;

public:
	UPROPERTY(Transient, BlueprintReadOnly)
	FBossStatData CurStatData;

	UFUNCTION(BlueprintCallable)
	virtual bool TryUpdateCurStatData(FStatType StatType, float Value) override;

	void SetDefaultStat();
};
