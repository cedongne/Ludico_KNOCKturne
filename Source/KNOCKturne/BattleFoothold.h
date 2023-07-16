// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PooledObject.h"

#include "BattleFoothold.generated.h"

UCLASS()
class KNOCKTURNE_API ABattleFoothold : public APooledObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleFoothold();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFoothold();

	int data = 5;
};
