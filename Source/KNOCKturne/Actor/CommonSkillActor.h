// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"

#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/BattleManagerSystem.h"
#include "BattleManager.h"

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

	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UBattleManagerSystem* BattleManagerSystem;
	class ABattleManager* BattleManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* SkillHitArea;
	UFUNCTION(BlueprintCallable)
	FName GetCurrentBlueprintClassName();

private:
	void RegistSkillActorOnBattleManager();

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CustomSkillOperation(int32 EffectSequence, FCurEffectIndexSkillData SkillData);
};