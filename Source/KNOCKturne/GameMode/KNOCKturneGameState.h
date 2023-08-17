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
};
