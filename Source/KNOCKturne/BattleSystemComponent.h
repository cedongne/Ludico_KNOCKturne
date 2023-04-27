// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "iostream"
#include "Components/ActorComponent.h"

#include "BattleManagerSystem.h"
#include "BattleTableManagerSystem.h"

#include "BattleSystemComponent.generated.h"

DECLARE_DELEGATE(NextTurnDelegate)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UBattleSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleSystemComponent();

private:
	UWorld* world;
	FTimerHandle TurnOverTimer;
	FTimerManager LeftTurnTimeTimerManager;
	FTimerHandle LeftTurnTimeTimer;

	NextTurnDelegate NextTurnDele;

	bool IsBossTurn;
	float LeftCurrentTurnTime;

	void StartBossTurn();
	void StartPeppyTurn();

	void TurnChange();

	void RunTurnTimer(float DeltaTime);
	void DecreaseLeftCurrentTurnTime();
//	void SetTimerToChangeNextTurn(void (UBattleSystemComponent::*TimerCallback)(), int32 CurTurnTime);

protected:
	class UBattleTableManagerSystem* BattleTableManager;
	class UBattleManagerSystem* BattleManager;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
