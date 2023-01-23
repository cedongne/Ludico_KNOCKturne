// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "PeppyStatComponent.h"

// Sets default values
ABossSkillActor::ABossSkillActor()
{

}

void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;

	
	IsInitialized = true;
}

void ABossSkillActor::HitPlayer() {
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
	UPeppyStatComponent* PeppyStatComponent = Peppy->PeppyStat;
	PeppyStatComponent->ChangeCurrentHp(-SkillData.Value_1_N);
}