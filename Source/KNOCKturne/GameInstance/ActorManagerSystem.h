// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Actor/Boss.h"
#include "Actor/Peppy.h"
#include "Actor/BattleManager.h"
#include "Actor/SpecialSkillActor.h"
#include "Actor/ItemActor.h"
#include "Actor/BossHitEffectActor.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "ActorManagerSystem.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UActorManagerSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABoss* BossActor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APeppy* PeppyActor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABattleManager* BattleManager = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASpecialSkillActor* SpecialSkillActor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AItemActor* ItemActor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABossHitEffectActor* BossHitEffectActor = nullptr;
};
