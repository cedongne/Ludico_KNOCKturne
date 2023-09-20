// Fill out your copyright notice in the Description page of Project Settings.


#include "Lake.h"

void ALake::BeginPlay()
{
	Super::BeginPlay();

	Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ALake::LakeStartTalk() {
	if (Peppy->OverlappedActor == this) {
		Peppy->InteractionCameraMove(this);
		LakeRandomTalk();
	}
}