// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergySpawner.generated.h"

UCLASS()
class KNOCKTURNE_API AEnergySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnergySpawner();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void EnergySpawn();
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Actor")
	UObject* EnergyBP;

};
