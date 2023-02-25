// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"
#include "DialogueTableComponent.h"
#include "BattleFieldLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API ABattleFieldLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ABattleFieldLevelScriptActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UDialogueTableComponent* DialogueTableComponent;

protected:
	virtual void BeginPlay() override;
};
