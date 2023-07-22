// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Character.h"

#include "PeppyStatComponent.h"
#include "PeppySkillComponent.h"

#include "Peppy.generated.h"

UCLASS()
class KNOCKTURNE_API APeppy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APeppy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	UCapsuleComponent* InteractionCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	class UPeppyStatComponent* PeppyStatComponent;
	
	// Time Threshold to know if it was a short press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flag)
	bool CanMove;

	TArray<TMap<FString, int32>> DamageArrayEachTurn;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	
	void SlideAction();
	void SlideHandling(float DeltaTime);

	APlayerController* PeppyController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSlide;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsHit;

	// Animation triggers;
	TMap<FString, bool> AnimationTriggerMap;
	bool IsDeliberate = false;
	bool IsExhaledeeply = false;
	bool IsHug = false;
	bool IsHugCampfire = false;
	bool IsSummon = false;

private:

	bool CanSlide;

	float SlideCooldown;
	UPROPERTY(Transient, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float LeftSlideCooltime;

	float FollowTime;

	const float WEIGHTMOVESPEED = 0.5f;

	UPROPERTY(EditAnywhere)
	int32 SlidingSpeed;

	// ���ǰ� ��Ʋ �ʵ忡�� ������ ������ �̵��ϴ� �� 10�ʰ� �ɸ��� �ӵ�
	const float StandardMaxWalkSpeed = 93.0f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5;
	float CurWalkSpeed;

public:
	UFUNCTION(BlueprintCallable)
	void SetImmobile();
	UFUNCTION(BlueprintCallable)
	void SetMobile();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HitVisualEffect();

	/* N턴 간 보스 턴이 시작될 때마다 페피에게 적용할 대미지를 순서에 맞게 배열 형태로 입력합니다. 지정한 턴에 이미 EffectId를 Key로 가지는 데이터가 존재한다면 값을 누적합니다. */
	void AddCumulativeDamageBeforeStartTurn(FString EffectId, TArray<int32> Damages);
	/* N턴 간 보스 턴이 시작될 때마다 페피에게 적용할 대미지를 순서에 맞게 배열 형태로 입력합니다. 지정한 턴에 이미 EffectId를 Key로 가지는 데이터가 존재한다면 값을 추가하지 않습니다.*/
	void AddDamageBeforeStartTurn(FString EffectId, TArray<int32> Damages);
};