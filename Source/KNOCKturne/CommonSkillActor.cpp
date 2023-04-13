// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSkillActor.h"

// Sets default values
ACommonSkillActor::ACommonSkillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommonSkillActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommonSkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

