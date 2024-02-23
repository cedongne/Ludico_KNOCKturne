// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KNOCKturne.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Controller.h"

#include "Component/PeppyStatComponent.h"
#include "Component/PeppySkillComponent.h"
#include "NPC.h"

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
	class UPeppyStatComponent* StatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	class UBuffComponent* BuffComponent;
	
	// Time Threshold to know if it was a short press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flag)
	bool CanMove;

	TArray<TMap<FString, int32>> DamageArrayEachTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* OverlappedActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DamageTextWidgetClass;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDie = false;

	// Animation triggers;
	TMap<FString, bool> AnimationTriggerMap;
	bool IsDeliberate = false;
	bool IsExhaledeeply = false;
	bool IsHug = false;
	bool IsHugCampfire = false;
	bool IsSummon = false;

	class AHubWorldLevelScriptActor* HubWorldLevelScriptActor;

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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ReturnCameraInInteraction();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InteractionCameraMove(APawn* NPC);

	void Die();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Die();

	/* N턴 간 보스 턴이 시작될 때마다 페피에게 적용할 대미지를 순서에 맞게 배열 형태로 입력합니다. 지정한 턴에 이미 EffectId를 Key로 가지는 데이터가 존재한다면 값을 누적합니다. */
	void AddCumulativeDamageBeforeStartTurn(FString EffectId, TArray<int32> Damages);
	/* N턴 간 보스 턴이 시작될 때마다 페피에게 적용할 대미지를 순서에 맞게 배열 형태로 입력합니다. 지정한 턴에 이미 EffectId를 Key로 가지는 데이터가 존재한다면 값을 추가하지 않습니다.*/
	void AddDamageBeforeStartTurn(FString EffectId, TArray<int32> Damages);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString InteractingNpcGroupcode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ANPC* InteractingNpcActor;
	UFUNCTION(BlueprintCallable)
	void SetInteractingNpc();

	/*버프*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool HasShieldBuff = false;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBossBuffUI();
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePeppyBuffUI();
	UFUNCTION(BlueprintImplementableEvent)
	void AddBossBuffUI(EBuffType BuffType);
	UFUNCTION(BlueprintImplementableEvent)
	void AddPeppyBuffUI(EBuffType BuffType);
};