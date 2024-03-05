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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isPrologue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DreamFragmentCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DreamDiaryOpenRow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool GetDreamFragment;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isDreamDiaryUpdated;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isBattleFail;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool RightafterBattleClear;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> ItemCountList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString SaveSlotName;

	UFUNCTION(BlueprintCallable)
	void LoadKNOCKturneData();
	UFUNCTION(BlueprintCallable)
	void SaveKNOCKturneData();

protected:
	void HandleBeginPlay() override;
};
