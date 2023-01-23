// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "BattleTableComponent.h"
#include "Components/ActorComponent.h"
#include "BossBattleSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UBossBattleSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossBattleSystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBattleTableComponent* BattleTableComponent;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataStructure")
	TArray<FString> BossSkillList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataStructure")
	TMap<FString, UClass*> BossSkillMap;

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnRandomSkill();
};
