// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"
#include "BossBattleSystemComponent.generated.h"

USTRUCT()
struct FBossSkillSpawningData {
	GENERATED_BODY()
	
public:
	FBossSkillSpawningData(UClass* _SkillObjectClass, TArray<FVector> _SkillTransform);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	UClass* SkillObjectClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<FVector> SkillTransform;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UBossBattleSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossBattleSystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataStructure")
	TArray<FString> BossSkillList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataStructure")
	TMap<FString, FBossSkillSpawningData> BossSkillMap;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnRandomSkill();
};
