// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KNOCKturneGameState.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API AKNOCKturneGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 DreamFragmentCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 DreamDiaryOpenRow = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool GetDreamFragment = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isDreamDiaryUpdated = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isBattleFail = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool RightafterBattleClear = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<int32> ItemCountList;

protected:
	void HandleBeginPlay() override;
};
