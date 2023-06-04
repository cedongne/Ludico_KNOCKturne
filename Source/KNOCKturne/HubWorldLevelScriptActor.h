// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"

#include "KNOCKturneLevelScriptActor.h"
#include "DialogueTableComponent.h"

#include "HubWorldLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API AHubWorldLevelScriptActor : public AKNOCKturneLevelScriptActor
{
	GENERATED_BODY()
	
public:
	AHubWorldLevelScriptActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UDialogueTableComponent* DialogueTableComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UDialogueTableComponent* PrologueDialogueComponent;

protected:
	virtual void BeginPlay() override;

};
