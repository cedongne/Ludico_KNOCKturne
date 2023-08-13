// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"

#include "KNOCKturneLevelScriptActor.h"

#include "BattleFieldLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API ABattleFieldLevelScriptActor : public AKNOCKturneLevelScriptActor
{
	GENERATED_BODY()
	
public:
	ABattleFieldLevelScriptActor();


protected:
	virtual void BeginPlay() override;
};
