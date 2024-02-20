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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UKNOCKturneObjectPool* EnergySpawner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NextSkillDelayTime;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	TSubclassOf<AActor> BP_EnergySpawnerClass;
	UBattleTableManagerSystem* BattleTableManagerSystem;

	FTimerHandle UseSkillTimerHandler;
	bool isFirstSkill = true;
	
public:
	bool IsDie = false;

	void SpawnBossSkillWhenStartBossTurn();
	void ClearUseSkillTimer();

	void SpawnBossSkill();

	void Die();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Die();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAttackMontage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAttackedMontage();
};