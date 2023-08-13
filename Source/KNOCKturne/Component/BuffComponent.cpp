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
	HasPositiveBuffs.Remove(BuffId);
}

void UBuffComponent::RemoveNegativeBuff(FString BuffId) {
	HasNegativeBuffs.Remove(BuffId);
}

void UBuffComponent::RemoveRandomPositiveBuff(int32 Num) {
	while (HasPositiveBuffs.Num() > 0 && Num-- > 0) {
		int32 RandIndex = rand() % HasPositiveBuffs.Num();
		for (auto Buff : HasPositiveBuffs) {
			if (!RandIndex--) {
				HasPositiveBuffs.Remove(Buff.Key);
				break;
			}
		}
	}
}

void UBuffComponent::RemoveRandomNegativeBuff(int32 Num) {
	while (HasNegativeBuffs.Num() > 0 && Num-- > 0) {
		int32 RandIndex = rand() % HasNegativeBuffs.Num();
		for (auto Buff : HasNegativeBuffs) {
			if (!RandIndex--) {
				HasNegativeBuffs.Remove(Buff.Key);
				break;
			}
		}
	}
}

void UBuffComponent::RemoveAllPositiveBuff() {
	HasPositiveBuffs.Empty();
}

void UBuffComponent::RemoveAllNegativeBuff() {
	HasNegativeBuffs.Empty();
}

void UBuffComponent::RemoveAllBuff() {
	RemoveAllPositiveBuff();
	RemoveAllNegativeBuff();
}