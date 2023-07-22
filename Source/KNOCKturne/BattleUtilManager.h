// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattleUtilManager.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UBattleUtilManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	bool InRangeLocation(FVector Value, FVector Min, FVector Max);

	UFUNCTION(BlueprintCallable)
	bool IsOverlappedAnotherSkills(FVector CurSkill, TArray<FTransform> AnotherSkills, int32 Range);
};
