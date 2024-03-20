// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppySkillActor.h"

APeppySkillActor::APeppySkillActor() {
}

void APeppySkillActor::BeginPlay() {
	Super::BeginPlay();

	// 이펙트 발동 타이밍과의 조정을 위해 블루프린트 Call로 변경
	// Initialize();
	// OperateSkillEffect(CurSkillUsingType);
}

void APeppySkillActor::Initialize() {
	Super::Initialize();

	LoadSkillDataFromDataTable();
}

void APeppySkillActor::LoadSkillDataFromDataTable() {
	FString BlueprintClassName = GetClass()->GetFName().ToString();
	SkillData = *(BattleTableManagerSystem->GetPeppySkillTable()->FindRow<FPeppySkillData>(*BlueprintClassName, TEXT("Fail to load PeppySkillData")));

	if (BattleTableManagerSystem->GetPeppySkillData().Find(BlueprintClassName) != nullptr) {
		SkillData.Cost = BattleTableManagerSystem->GetPeppySkillData()[BlueprintClassName].Cost;
	}
}

bool APeppySkillActor::TryOperateSkillEffect(ESkillUsingType SkillUsingType) {
	switch (SkillUsingType) {
	case ESkillUsingType::Sequential:
		return BattleTableManagerSystem->TryUsePeppySkillSequential(SkillData, this);
	case ESkillUsingType::Probabilistic:
		return BattleTableManagerSystem->TryUsePeppySkillProbabilistic(SkillData, this);
	}

	return false;
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
