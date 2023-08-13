// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "Component/BossStatComponent.h"
#include "Component/BuffComponent.h"

#include "Boss.generated.h"

UCLASS()
class KNOCKTURNE_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:
	ABoss();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	class UBossStatComponent* StatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	class UBuffComponent* BuffComponent;

protected:
	virtual void BeginPlay() override;

public:
	void Die();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Die();
};
