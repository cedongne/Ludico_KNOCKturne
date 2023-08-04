// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "Boss.h"
#include "Peppy.h"
#include "BattleTableManagerSystem.h"

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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABoss* BossActor = nullptr;
	APeppy* PeppyActor = nullptr;

	UWorld* world;
	FTimerHandle TurnOverTimer;
	FTimerManager LeftTurnTimeTimerManager;
	FTimerHandle LeftTurnTimeTimer;

	BattleTurnType CurrentTurnType;
	float LeftCurrentTurnTime;

	bool IsCalled_InitStartBossTurn = false;

	void StartBossTurn();
	void StartPeppyTurn();

	void TurnChange();

	void RunTurnTimer(float DeltaTime);
	void DecreaseLeftCurrentTurnTime();

	void ProcessDamageBeforeStartTurn();

	void UpdateRoundInfo();

public:
	UFUNCTION(BlueprintCallable)
	ABoss* GetBossActor();
	UFUNCTION(BlueprintCallable)
	APeppy* GetPeppyActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, AActor*> SkillActorsOnField;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Round = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LastRoundBossHpRatio;
	
	UFUNCTION(BlueprintCallable)
	void BP_InitStartBossTurn();

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

protected:
	class UBattleTableManagerSystem* BattleTableManager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
