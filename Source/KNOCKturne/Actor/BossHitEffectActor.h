// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossHitEffectActor.generated.h"

UCLASS()
class KNOCKTURNE_API ABossHitEffectActor : public AActor
{
	GENERATED_BODY()

	class UNiagaraSystem* BossHitEffect_Yellow;
	class UNiagaraSystem* BossHitEffect_Red;
	class UNiagaraSystem* BossHitEffect_Gray;
	
public:	
	ABossHitEffectActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* BossHitEffect;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetBossHitEffect(FString Stance);
};
