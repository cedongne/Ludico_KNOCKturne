// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "BattleTableManagerSystem.h"
#include "CommonSkillActor.h"

#include "BossSkillActor.generated.h"

UCLASS()
class KNOCKTURNE_API ABossSkillActor : public ACommonSkillActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSkillActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	struct FBossSkillData SkillData;

public:
	UFUNCTION(BlueprintCallable)
	void InitSkillData(FBossSkillData NewSkillData);
	UFUNCTION(BlueprintCallable)
	void SetSkillData(FBossSkillData NewSkillData);
	UFUNCTION(BlueprintCallable)
	void SetSkillDataWithName(FString SkillName);

	UFUNCTION(BlueprintCallable)
	void HitPlayer();

	UFUNCTION(BlueprintCallable)
	FVector GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaTime);
};
