// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "Component/BossStatComponent.h"
#include "Component/KNOCKturneObjectPool.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "Component/BuffComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DamageTextWidgetClass;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	TSubclassOf<AActor> BP_EnergySpawnerClass;
	UBattleTableManagerSystem* BattleTableManagerSystem;
	class UBattleManagerSystem* BattleManagerSystem;

	FTimerHandle UseSkillTimerHandler;
	bool isFirstSkill = true;

	TMap<FString, int32> BossSkillNameCoolTimeMap;
	
public:
	bool IsDie = false;

	void SpawnBossSkillWhenStartBossTurn();
	void ClearUseSkillTimer();
	void ElapseCoolTime();

	void SpawnBossSkill();
	TArray<FString> GetSpawnableBossSkills(TArray<FString> BossSkillKeyArray, FString CurBossSkillStance);

	void PauseAndClearUseSkillTimer();

	void Die();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Die();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAttackMontage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAttackedMontage();
};