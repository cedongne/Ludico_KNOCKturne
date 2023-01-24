// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"
#include "BattleTableManagerSystem.h"

#include "BossSkillActor.generated.h"

UCLASS()
class KNOCKTURNE_API ABossSkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSkillActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flag")
	bool IsHitPlayer = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flag")
	bool IsInitialized = false;

	class UBattleTableManagerSystem* BattleTableManager;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	struct FBossSkillData SkillData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* SkillHitArea;

public:
	UFUNCTION(BlueprintCallable)
	void SetSkillData(FBossSkillData NewSkillData);
	UFUNCTION(BlueprintCallable)
	void SetSkillDataWithName(FString SkillName);

	UFUNCTION(BlueprintCallable)
	void HitPlayer();
};
