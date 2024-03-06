// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KNOCKturneSaveGame.h"
#include "KNOCKturneGameState.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API AKNOCKturneGameState : public AGameStateBase
{
	GENERATED_BODY()
	AKNOCKturneGameState();
	class UBattleManagerSystem* BattleManagerSystem;

public:
	/*UPROPERTY(Transient)
	bool isPrologue;
	UPROPERTY(Transient)
	int32 DreamFragmentCount;
	UPROPERTY(Transient)
	int32 DreamDiaryOpenRow;
	UPROPERTY(Transient)
	bool GetDreamFragment;
	UPROPERTY(Transient)
	bool isDreamDiaryUpdated;
	UPROPERTY(Transient)
	bool isBattleFail;
	UPROPERTY(Transient)
	bool RightafterBattleClear;
	UPROPERTY(Transient)
	TArray<int32> ItemCountList;*/
	UPROPERTY(Transient)
	FString SaveSlotName;
	UPROPERTY(Transient)
	int32 UserIndex = 0;

	UFUNCTION(BlueprintCallable)
	void LoadKNOCKturneData();
	UFUNCTION(BlueprintCallable)
	void SaveKNOCKturneData();

protected:
	void HandleBeginPlay() override;
};
