// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Engine/LevelScriptActor.h"

#include "DialogueTableComponent.h"

#include "KNOCKturneLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API AKNOCKturneLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AKNOCKturneLevelScriptActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UDialogueTableComponent* DialogueTableComponent;
};
