// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "Boss.h"
#include "Peppy.h"

#include "BattleManager.generated.h"

enum BattleTurnType {
	BossTurn,
	PeppySkillSelectingTurn,
	PeppySkillUsingTurn
};

UCLASS()
class KNOCKTURNE_API ABattleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABattleManager();

public:
	UWorld* world;
	FTimerHandle TurnOverTimer;
	FTimerManager LeftTurnTimeTimerManager;
	FTimerHandle LeftTurnTimeTimer;

	BattleTurnType CurrentTurnType;
	float LeftCurrentTurnTime;

	bool IsCalled_InitStartBossTurn = false;

	void Init();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ActorInit();

	void StartBossTurn();
	void StartPeppyTurn();

	void TryUseItem();
	void EndItem();

	void TurnChange();

	void RunTurnTimer(float DeltaTime);
	void DecreaseLeftCurrentTurnTime();

	void ProcessDamageBeforeStartTurn();


public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BossActorSubClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SpecialSkillClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, AActor*> SkillActorsOnField;
	
	UFUNCTION(BlueprintCallable)
	void BP_InitStartBattle();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartBossTurn();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartPeppyTurn();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UsePeppySkills();

	UFUNCTION(BlueprintCallable)
	float GetLeftCurrentTurnTime();
	UFUNCTION(BlueprintCallable)
	void SetLeftCurrentTurnTime(float TurnTime);
	UFUNCTION(BlueprintCallable)
	void EndTurn();
	UFUNCTION(BlueprintCallable)
	void EndBattle();
	UFUNCTION(BlueprintCallable)
	void SetBossAndResponseStance();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBossBuffUI();
	UFUNCTION(BlueprintImplementableEvent)
	void AddBossBuffUI(EBuffType BuffType);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePeppyBuffUI();
	UFUNCTION(BlueprintImplementableEvent)
	void AddPeppyBuffUI(EBuffType BuffType);

private:
	class TArray<UBuffComponent*> HandledBuffComponents;
	void HandleBuffsEachTurns();
	void HandleBuffsEachSeconds();

	FTimerHandle BuffBySecondsHandler;

protected:
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UBattleManagerSystem* BattleManagerSystem;
	class UActorManagerSystem* ActorManagerSystem;

	FString ItemName;
	FItemData ItemData;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
