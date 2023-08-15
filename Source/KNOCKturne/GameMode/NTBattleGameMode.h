// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/GameModeBase.h"

#include "Actor/BattleManager.h"
#include "GameMode/KNOCKturneGameState.h"

#include "NTBattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API ANTBattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANTBattleGameMode();

protected:
	void InitGame(const FString& MapName, const FString& Option, FString& ErrorMessage) override;

private:
	TSubclassOf<class ABattleManager> BP_BattleManagerClass;
	AKNOCKturneGameState* KNOCKturneGameState;

	void EndBattle();

	void GetDreamFragment();

protected:
	class UBattleManagerSystem* BattleManagerSystem;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	ABattleManager* BattleManager;

	UFUNCTION(BlueprintCallable)
	void GameOver();
	UFUNCTION(BlueprintCallable)
	void GameClear();




};
