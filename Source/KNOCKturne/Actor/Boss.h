// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "Component/BossStatComponent.h"
#include "Component/BuffComponent.h"
#include "Component/KNOCKturneObjectPool.h"
#include "GameInstance/BattleTableManagerSystem.h"

#include "Boss.generated.h"

UCLASS()
class KNOCKTURNE_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:
	ABoss();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	class UBossStatComponent* StatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	class UBuffComponent* BuffComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UKNOCKturneObjectPool* EnergySpawner;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	UBattleTableManagerSystem* BattleTableManagerSystem;

	FTimerHandle UseSkillTimerHandler;

	void SpawnBossSkill();
	
public:
	bool IsDie = false;

	void SpawnBossSkillWhenStartBossTurn();
	void ClearUseSkillTimer();

	void Die();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Die();
};