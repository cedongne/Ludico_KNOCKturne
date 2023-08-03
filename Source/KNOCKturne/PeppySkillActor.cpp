// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppySkillActor.h"

APeppySkillActor::APeppySkillActor() {
}

void APeppySkillActor::BeginPlay() {
	Super::BeginPlay();
	RegistSkillActorOnBattleManager();
	LoadSkillDataFromDataTable();
	UseSkill();

}

void APeppySkillActor::LoadSkillDataFromDataTable() {
	FString BlueprintClassName = GetClass()->GetFName().ToString();
	SkillData = *(BattleTableManagerSystem->GetPeppySkillTable()->FindRow<FPeppySkillData>(*BlueprintClassName, TEXT("Fail to load PeppySkillData")));
}

void APeppySkillActor::UseSkill() {
	BattleTableManagerSystem->UsePeppySkill(SkillData, this);
}

/*
UAnimMontage* APeppySkillActor::FindAnimMontageAsset() {
	FString MontageAssetReference = "/Game/Assets/Art_3D/Animation/Peppy_animation/" + SkillData.SkillAnimation + "." + SkillData.SkillAnimation;
	NTLOG(Warning, TEXT("%s"), *MontageAssetReference);
//	SkillAnimMontage = LoadObject<UAnimMontage>(NULL, *MontageAssetReference, NULL, LOAD_None, NULL);
//	return SkillAnimMontage;
	return LoadObject<UAnimMontage>(NULL, *MontageAssetReference, NULL, LOAD_None, NULL);
}
*/


void APeppySkillActor::RegistSkillActorOnBattleManager() {
	BattleManager->SkillActorsOnField.Add(this);
}