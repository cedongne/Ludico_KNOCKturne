// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergySpawner.h"

// Sets default values
AEnergySpawner::AEnergySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnergySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnergySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnergySpawner::EnergySpawn() {

}