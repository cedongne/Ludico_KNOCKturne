// Fill out your copyright notice in the Description page of Project Settings.


#include "Rabbit.h"

ARabbit::ARabbit()
{

}


void ARabbit::BeginPlay()
{
	Super::BeginPlay();
	
	Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ARabbit::RabbitStartTalk() {
	if (Peppy->OverlappedActor == this) {
		Peppy->InteractionCameraMove(this);
		RabbitRandomTalk();
	}
}