// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"

UBuffComponent::UBuffComponent()
{
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuffComponent::RemovePositiveBuff(FString BuffId) {
	HasPositiveBuffs_PerTurn.Remove(BuffId);
	HasPositiveBuffs_PerSecond.Remove(BuffId);
}

void UBuffComponent::RemoveNegativeBuff(FString BuffId) {
	HasNegativeBuffs_PerTurn.Remove(BuffId);
	HasNegativeBuffs_PerSecond.Remove(BuffId);
}

void UBuffComponent::RemoveRandomPositiveBuff(int32 Num) {
	auto totalPositiveBuffNum = HasPositiveBuffs_PerTurn.Num() + HasPositiveBuffs_PerSecond.Num();
	if (Num < 0) {
		NTLOG(Error, TEXT("Num must be Positive!"));
	}
	if (totalPositiveBuffNum > 0) {
		while (Num--) {
			auto randIndex = rand() % totalPositiveBuffNum;
			if (randIndex >= HasPositiveBuffs_PerTurn.Num()) {
				randIndex -= HasPositiveBuffs_PerTurn.Num();
				for (auto Buff : HasPositiveBuffs_PerSecond) {
					if (randIndex-- == 0) {
						HasPositiveBuffs_PerSecond.Remove(Buff.Key);
						break;
					}
				}
			}
			else {
				for (auto Buff : HasPositiveBuffs_PerTurn) {
					if (randIndex-- == 0) {
						HasPositiveBuffs_PerTurn.Remove(Buff.Key);
						break;
					}
				}
			}
		}
	}
}

void UBuffComponent::RemoveRandomNegativeBuff(int32 Num) {
	auto totalNegativeBuffNum = HasNegativeBuffs_PerTurn.Num() + HasNegativeBuffs_PerSecond.Num();
	if (Num < 0) {
		NTLOG(Error, TEXT("Num must be Positive!"));
	}
	if (totalNegativeBuffNum > 0) {
		while (Num--) {
			auto randIndex = rand() % totalNegativeBuffNum;
			if (randIndex >= HasNegativeBuffs_PerTurn.Num()) {
				randIndex -= HasNegativeBuffs_PerTurn.Num();
				for (auto Buff : HasNegativeBuffs_PerSecond) {
					if (randIndex-- == 0) {
						HasNegativeBuffs_PerSecond.Remove(Buff.Key);
						break;
					}
				}
			}
			else {
				for (auto Buff : HasNegativeBuffs_PerTurn) {
					if (randIndex-- == 0) {
						HasNegativeBuffs_PerTurn.Remove(Buff.Key);
						break;
					}
				}
			}
		}
	}
}

void UBuffComponent::RemoveAllPositiveBuff() {
	HasPositiveBuffs_PerTurn.Empty();
	HasPositiveBuffs_PerSecond.Empty();
}

void UBuffComponent::RemoveAllNegativeBuff() {
	HasNegativeBuffs_PerTurn.Empty();
	HasNegativeBuffs_PerSecond.Empty();
}

void UBuffComponent::RemoveAllBuff() {
	RemoveAllPositiveBuff();
	RemoveAllNegativeBuff();
}

void UBuffComponent::AcquireBuff(EBuffType BuffType, EBuffDataType TermType, FString BuffName, int32 Duration) {
	switch (TermType) {
	case EBuffDataType::Positive_Turn:
		HasPositiveBuffs_PerTurn.Add(BuffName, Duration);
		break;
	case EBuffDataType::Positive_Second:
		HasPositiveBuffs_PerSecond.Add(BuffName, Duration);
		break;
	case EBuffDataType::Negative_Turn:
		HasNegativeBuffs_PerTurn.Add(BuffName, Duration);
		break;
	case EBuffDataType::Negative_Second:
		HasNegativeBuffs_PerSecond.Add(BuffName, Duration);
		break;
	}
}

void UBuffComponent::ElapseTurn() {
	for (auto buff : HasPositiveBuffs_PerTurn) {
		buff.Value--;
		if (buff.Value == 0) {
			ExpireBuff(&HasPositiveBuffs_PerTurn, buff.Key);
		}
	}
	for (auto buff : HasNegativeBuffs_PerTurn) {
		buff.Value--;
		if (buff.Value == 0) {
			ExpireBuff(&HasNegativeBuffs_PerTurn, buff.Key);
		}
	}
}

void UBuffComponent::ElapseSecond() {
	for (auto buff : HasPositiveBuffs_PerSecond) {
		buff.Value--;
		if (buff.Value == 0) {
			ExpireBuff(&HasPositiveBuffs_PerSecond, buff.Key);
		}
	}
	for (auto buff : HasNegativeBuffs_PerSecond) {
		buff.Value--;
		if (buff.Value == 0) {
			ExpireBuff(&HasNegativeBuffs_PerSecond, buff.Key);
		}
	}
}


void UBuffComponent::ExpireBuff(TMap<FString, int32>* BuffMap, FString BuffId) {
	BuffMap->Remove(BuffId);
}