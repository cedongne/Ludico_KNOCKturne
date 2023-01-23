// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleTableComponent.h"
#include "BossSkillActor.generated.h"

UCLASS()
class KNOCKTURNE_API ABossSkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSkillActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flag")
	bool IsHitPlayer = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flag")
	bool IsInitialized = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	struct FBossSkillData SkillData;

public:
	UFUNCTION(BlueprintCallable)
	void SetSkillData(FBossSkillData NewSkillData);

	UFUNCTION(BlueprintCallable)
	void HitPlayer();
};
