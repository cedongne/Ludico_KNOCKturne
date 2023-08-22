// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"

#include "GameInstance/BattleTableManagerSystem.h"
#include "CommonSkillActor.h"

#include "BossSkillActor.generated.h"

UENUM(BlueprintType)
enum class ESkillActorLifeCycleStep : uint8 {
	DelayTime UMETA(DisplayName = "DelayTime"),
	CastTime UMETA(DisplayName = "CastTime"),
	DestroyTime UMETA(DisplayName = "DestroyTime")
};

UCLASS()
class KNOCKTURNE_API ABossSkillActor : public ACommonSkillActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ActorPivot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SkillMeshPivot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SkillMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* AttackRange;
public:	
	// Sets default values for this actor's properties
	ABossSkillActor();

private:
	float TempDelayTime;

	struct FBossSkillData SkillData;

	void EvaluateCurrentLifeCycleStep(float DeltaSeconds);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsContactSkill;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DeltaTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentLifeTime = 0;

	UFUNCTION(BlueprintCallable)
	void Initialize() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESkillActorLifeCycleStep CurrentStep = ESkillActorLifeCycleStep::DelayTime;

public:

	UFUNCTION(BlueprintCallable)
	void InitSkillData();
	UFUNCTION(BlueprintCallable)
	FBossSkillData GetSkillData();
	UFUNCTION(BlueprintCallable)
	void SetSkillData(FBossSkillData NewSkillData);

	UFUNCTION(BlueprintCallable)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable)
	FVector GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	bool DelayWithDeltaTime(float DelayTime, float DeltaSeconds);

	
};
