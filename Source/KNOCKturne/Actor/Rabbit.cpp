// Fill out your copyright notice in the Description page of Project Settings.


#include "Rabbit.h"

// Sets default values
ARabbit::ARabbit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARabbit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARabbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

