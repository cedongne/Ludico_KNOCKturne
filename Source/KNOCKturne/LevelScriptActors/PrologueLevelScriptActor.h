// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DialogueTableComponent.h"
#include "PrologueLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API APrologueLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
	APrologueLevelScriptActor();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDialogueTableComponent* DialogueTableComponent;
};
