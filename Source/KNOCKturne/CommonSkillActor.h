// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "BattleTableManagerSystem.h"

#include "CommonSkillActor.generated.h"

UCLASS()
class KNOCKTURNE_API ACommonSkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommonSkillActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flag")
	bool IsHitPlayer = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flag")
	bool IsInitialized = false;

	class UBattleTableManagerSystem* BattleTableManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* SkillHitArea;

};
