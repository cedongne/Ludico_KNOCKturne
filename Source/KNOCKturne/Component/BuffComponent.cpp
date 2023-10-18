// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"

UBuffComponent::UBuffComponent()
{
	FString BuffTablePath = TEXT("/Game/Assets/DataTable/BuffTable.BuffTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BuffTABLE(*BuffTablePath);
	NTCHECK(DT_BuffTABLE.Succeeded());
	BuffTable = DT_BuffTABLE.Object;
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuffComponent::RemoveBuff(EBuffType BuffType) {
	HasPositiveBuffs_PerTurn.Remove(BuffType);
	HasPositiveBuffs_PerSecond.Remove(BuffType);
	HasNegativeBuffs_PerTurn.Remove(BuffType);
	HasNegativeBuffs_PerSecond.Remove(BuffType);
}

void UBuffComponent::RemoveRandomPositiveBuff(int32 Num) {
	auto totalPositiveBuffNum = HasPositiveBuffs_PerTurn.Num() + HasPositiveBuffs_PerSecond.Num();
	if (Num < 0) {
		NTLOG(Error, TEXT("Num must be Positive!"));
	}

	if (Num > totalPositiveBuffNum) {
		Num = totalPositiveBuffNum;
	}
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

void UBuffComponent::RemoveRandomNegativeBuff(int32 Num) {
	auto totalNegativeBuffNum = HasNegativeBuffs_PerTurn.Num() + HasNegativeBuffs_PerSecond.Num();
	if (Num < 0) {
		NTLOG(Error, TEXT("Num must be Positive!"));
	}

	if (Num > totalNegativeBuffNum) {
		Num = totalNegativeBuffNum;
	}
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

void UBuffComponent::AcquireBuff(EBuffType BuffType, FString SourceId) {
	auto buffTypeStr = BuffTypeToStringMap.Find(BuffType);
	if (buffTypeStr == nullptr) {
		NTLOG(Error, TEXT("BuffType is invalid!"));
		return;
	}

	auto acquiredBuff = BuffTable->FindRow<FBuffTable>(FName(*buffTypeStr), TEXT(""));
	if (acquiredBuff == nullptr) {
		NTLOG(Error, TEXT("Buff acquiration is failed!"));
		return;
	}
	
	auto buffData = new FBuffData(SourceId, acquiredBuff);

	if (acquiredBuff->BuffType == 0) {
		switch (buffData->BuffTermType) {
		case EBuffTermType::Turn:
			HasPositiveBuffs_PerTurn.Add(BuffType, *buffData);
			break;
		case EBuffTermType::Second:
			HasPositiveBuffs_PerSecond.Add(BuffType, *buffData);
			break;
		}
	}
	else if (acquiredBuff->BuffType == 1) {
		switch (buffData->BuffTermType) {
		case EBuffTermType::Turn:
			HasNegativeBuffs_PerTurn.Add(BuffType, *buffData);
			break;
		case EBuffTermType::Second:
			HasNegativeBuffs_PerSecond.Add(BuffType, *buffData);
			break;
		}
	}
}

void UBuffComponent::ElapseTurn() {
	for (auto buff : HasPositiveBuffs_PerTurn) {
		if (buff.Value.Duration-- == 0) {
			HasPositiveBuffs_PerTurn.Remove(buff.Key);
		}
	}
	for (auto buff : HasNegativeBuffs_PerTurn) {
		if (buff.Value.Duration-- == 0) {
			HasNegativeBuffs_PerTurn.Remove(buff.Key);
		}
	}
}

void UBuffComponent::ElapseSecond() {
	for (auto buff : HasPositiveBuffs_PerSecond) {
		if (buff.Value.Duration-- == 0) {
			HasPositiveBuffs_PerSecond.Remove(buff.Key);
		}
	}
	for (auto buff : HasNegativeBuffs_PerSecond) {
		if (buff.Value.Duration-- == 0) {
			HasNegativeBuffs_PerSecond.Remove(buff.Key);
		}
	}
}

void UBuffComponent::ExpireBuff(TMap<EBuffType, FBuffData>* BuffMap, EBuffType BuffType) {
	BuffMap->Remove(BuffType);
}

bool UBuffComponent::HasBuff(EBuffType BuffType) {
	return HasPositiveBuffs_PerSecond.Contains(BuffType)
		|| HasPositiveBuffs_PerTurn.Contains(BuffType)
		|| HasNegativeBuffs_PerSecond.Contains(BuffType)
		|| HasNegativeBuffs_PerTurn.Contains(BuffType)
		? true : false;
}