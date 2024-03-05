// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KNOCKturneSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UKNOCKturneSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UKNOCKturneSaveGame();

	UPROPERTY()
	bool isPrologue;
	UPROPERTY()
	int32 DreamFragmentCount;
	UPROPERTY()
	int32 DreamDiaryOpenRow;
	UPROPERTY()
	bool GetDreamFragment;
	UPROPERTY()
	bool isDreamDiaryUpdated;
	UPROPERTY()
	bool isBattleFail;
	UPROPERTY()
	bool RightafterBattleClear;
	UPROPERTY()
	TArray<int32> ItemCountList;
};