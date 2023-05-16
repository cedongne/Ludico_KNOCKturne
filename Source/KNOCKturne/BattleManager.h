// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "BattleManagerSystem.h"
#include "BattleTableManagerSystem.h"

#include "BattleManager.generated.h"

UCLASS()
class KNOCKTURNE_API ABattleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABattleManager();

private:
	UWorld* world;
	FTimerHandle TurnOverTimer;
	FTimerManager LeftTurnTimeTimerManager;
	FTimerHandle LeftTurnTimeTimer;

	bool IsBossTurn;
	float LeftCurrentTurnTime;

	bool IsCalled_InitStartBossTurn = false;

	void StartBossTurn();
	void StartPeppyTurn();

	void TurnChange();
	void SetTurnTime(int32 TurnTime);

	void RunTurnTimer(float DeltaTime);
	void DecreaseLeftCurrentTurnTime();

public:
	UFUNCTION(BlueprintCallable)
	void BP_InitStartBossTurn();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartBossTurn();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartPeppyTurn();

protected:
	class UBattleTableManagerSystem* BattleTableManager;
	class UBattleManagerSystem* BattleManager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
