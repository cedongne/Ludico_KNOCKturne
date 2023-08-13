// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "Components/ActorComponent.h"

#include "GameInstance/BattleTableManagerSystem.h"

#include "PeppySkillComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API UPeppySkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPeppySkillComponent();

private:
	int32 SkillTableIndex;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UGameInstance* GameInstance;
	class UBattleTableManagerSystem* BattleTableManager;

	void LoadGameInstances();
	void LoadCanUsePeppySkillList();
	void AddCanUsePeppySkillWithLevelName(FString LevelName);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	TArray<FPeppySkillData> CanUsePeppySkillList;
	
	UFUNCTION(BlueprintCallable)
	void EnterBattleLevel();
};
