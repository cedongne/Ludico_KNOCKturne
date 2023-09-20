// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actor/NPC.h"
#include "Peppy.h"

#include "Lake.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API ALake : public ANPC
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	APeppy* Peppy;

public:
	UFUNCTION(BlueprintCallable)
	void LakeStartTalk();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LakeRandomTalk();
};
