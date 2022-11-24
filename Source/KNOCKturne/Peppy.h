// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Peppy.generated.h"

UCLASS()
class KNOCKTURNE_API APeppy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APeppy();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	UCapsuleComponent* InteractionCollider;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UPeppyStatComponent* PeppyStat;
	
	// Time Threshold to know if it was a short press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void SlideAction();
	void SlideHandling(float DeltaTime);

	void CheckInteraction();

	/* Move input mouse with keyboard
	void SetDestination();
	*/



private:
	APlayerController* PeppyController;

	bool IsMove;
	bool IsSlide;

	bool CanSlide;

	float SlideCooldown;
	float LeftSlideCooltime;

	float FollowTime;

	const float WEIGHTMOVESPEED = 0.5f;
	float MoveSpeed;
};