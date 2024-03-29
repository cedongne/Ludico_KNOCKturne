// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BossHitEffectActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABossHitEffectActor::ABossHitEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	FString BossHitEffect_Yellow_Path = TEXT("/Game/Assets/Effects/BossEffect/BossHitEffect_Yellow.BossHitEffect_Yellow");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_BossHitEffect_Yellow(*BossHitEffect_Yellow_Path);
	BossHitEffect_Yellow = DT_BossHitEffect_Yellow.Object;

	FString BossHitEffect_Red_Path = TEXT("/Game/Assets/Effects/BossEffect/BossHitEffect_Red.BossHitEffect_Red");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_BossHitEffect_Red(*BossHitEffect_Red_Path);
	BossHitEffect_Red = DT_BossHitEffect_Red.Object;

	FString BossHitEffect_Gray_Path = TEXT("/Game/Assets/Effects/BossEffect/BossHitEffect_Gray.BossHitEffect_Gray");
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DT_BossHitEffect_Gray(*BossHitEffect_Gray_Path);
	BossHitEffect_Gray = DT_BossHitEffect_Gray.Object;

	BossHitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BossHitEffect"));
}

void ABossHitEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossHitEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossHitEffectActor::SetBossHitEffect(FString Stance)
{
	//BossHitEffect->SetActive(true);

	if (Stance == "Default") {
		BossHitEffect->SetAsset(BossHitEffect_Gray, true);
	}
	else if (Stance == "Empathy") {
		BossHitEffect->SetAsset(BossHitEffect_Yellow, true);
	}
	else if (Stance == "Scolding") {
		BossHitEffect->SetAsset(BossHitEffect_Red, true);
	}
}

