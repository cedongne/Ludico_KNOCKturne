// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"
#include "DialogueTableComponent.h"
#include "HubWorldLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API AHubWorldLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AHubWorldLevelScriptActor();

	UPROPERTY(VisibleAnywhere, Category = "Manager")
	UDialogueTableComponent* DialogueTableComponent;
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Manager")
//	UDialogueManager* DialogueManager;
};
