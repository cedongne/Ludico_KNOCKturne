// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class KNOCKTURNE_API AItemActor : public AActor
{
	GENERATED_BODY()
	class UBattleTableManagerSystem* BattleTableManagerSystem;
	class UBattleManagerSystem* BattleManagerSystem;
	class UActorManagerSystem* ActorManagerSystem;
	
public:	
	AItemActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FString ItemName;
	FItemData ItemData;

	/*눈썰매*/
	bool isSledItem;

	void TryUseItem();

public:	

	/*국왕의 비밀문서*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanAvoidAttack = false;
	UFUNCTION(BlueprintCallable)
	bool TryAvoidAttack();

	/*눈썰매*/
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isSledItem;*/

	UFUNCTION(BlueprintCallable)
	void RecoverEPRandomly();
	UFUNCTION(BlueprintCallable)
	void EndItem();
};
