// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/GameModeBase.h"
#include "Actor/BattleManager.h"
#include "GameMode/KNOCKturneGameState.h"
#include "GameInstance/ActorManagerSystem.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<UUserWidget> BP_BattleHudClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BP")
	class UUserWidget* BP_BattleHud;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASpecialSkillActor> BP_SpecialSkillActorClass;

	void InitGame(const FString& MapName, const FString& Option, FString& ErrorMessage) override;
	void RestartPlayer(AController* NewPlayer) override;

private:
	TSubclassOf<class ABattleManager> BP_BattleManagerClass;
	TSubclassOf<class ABoss> BP_BossActorClass;

	class ABattleManager* BattleManager;
	class UActorManagerSystem* ActorManagerSystem;
	class UBattleManagerSystem* BattleManagerSystem;

public:
	UFUNCTION(BlueprintCallable)
	void SpawnHud();
	UFUNCTION(BlueprintCallable)
	void EndBattle();

	UFUNCTION(BlueprintCallable)
	void GameOver();
	UFUNCTION(BlueprintCallable)
	void GameClear();

};
