// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SpecialSkillActor.generated.h"

UCLASS()
class KNOCKTURNE_API ASpecialSkillActor : public AActor
{
	GENERATED_BODY()
	ASpecialSkillActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	class APeppyController* PeppyController;
	class UBattleManagerSystem* BattleManagerSystem;
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UActorManagerSystem* ActorManagerSystem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FSpecialSkillTable SpecialSkillData;

private:

	UPROPERTY()
	class UDataTable* SpecialSkillTable;
	UPROPERTY()
	int32 OriginalCoolTime;

public:

	UFUNCTION(BlueprintCallable)
	void CreateSpecialSkillData();

	/*특수기 사용 조건 만족 여부 반환*/
	UFUNCTION(BlueprintCallable)
	bool IsSatisfyUseCondition();
	UFUNCTION(BlueprintCallable)
	bool CheckCanUseSpecialSkill(float DeltaSeconds);
	UFUNCTION(BlueprintCallable)
	void ElapseTurn();
	UFUNCTION(BlueprintCallable)
	bool TryUseSpecialSkill();

	UFUNCTION(BlueprintCallable)
	int32 GetCurSpecialSkillCoolTime();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnEffect();
};
