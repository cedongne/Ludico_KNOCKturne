// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DialogueManager.h"
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

//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Manager")
//	UDialogueManager* DialogueManager;
};
