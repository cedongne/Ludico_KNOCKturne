// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleUtilManager.h"




bool UBattleUtilManager::InRangeLocation(FVector Value, FVector Min, FVector Max) {
	auto X = Value.X;
	auto Y = Value.Y;
	auto Z = Value.Z;

	if (Min.X <= X && Max.X >= X &&
		Min.Y <= Y && Max.Y >= Y &&
		Min.Z <= Z && Max.Z >= Z) {
		return true;
	}
	else {
		return false;
	}	
}

bool UBattleUtilManager::IsOverlappedAnotherSkills(FVector CurSkill, TArray<FTransform> AnotherSkills, int32 Range) {
	for (auto anotherSkill : AnotherSkills) {
		if (InRangeLocation(CurSkill, anotherSkill.GetLocation() - Range, anotherSkill.GetLocation() + Range)) {
			return true;
		}
	}
	return false;
}