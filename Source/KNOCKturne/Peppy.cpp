// Fill out your copyright notice in the Description page of Project Settings.
#include "Peppy.h"

// Sets default values
APeppy::APeppy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;

	InteractionCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionCollider"));
	InteractionCollider->SetupAttachment(RootComponent);
	InteractionCollider->SetCapsuleRadius(96.0f);
	InteractionCollider->SetCapsuleHalfHeight(48.0f);


	isMove = false;

}

// Called when the game starts or when spawned
void APeppy::BeginPlay()
{
	Super::BeginPlay();

//	InteractionCollider->OnComponentBeginOverlap.AddDynamic(this, &APeppy::OnOverlapBegin);
//	InteractionCollider->OnComponentEndOverlap.AddDynamic(this, &APeppy::OnOverlapEnd);
	
}

// Called every frame
void APeppy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APeppy::MoveForward(float Value) {
	if ((Controller != nullptr) && (Value != 0.0f)) {
		if (isMove) {
			GetMovementComponent()->StopMovementImmediately();
			isMove = false;
		}
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APeppy::MoveRight(float Value) {
	if ((Controller != nullptr) && (Value != 0.0f)) {
		if (isMove) {
			GetMovementComponent()->StopMovementImmediately();
			isMove = false;
		}
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APeppy::SetDestination() {
	isMove = true;
}


void APeppy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this) && OtherComp) {
		if (OtherActor->ActorHasTag("NPC")) {
			UE_LOG(LogTemp, Warning, TEXT("NPC overlapped"));
		}
	}
}

void APeppy::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this) && OtherComp) {
		if (OtherActor->ActorHasTag("NPC")) {
			UE_LOG(LogTemp, Warning, TEXT("NPC out of range"));
		}
	}
}

void APeppy::CheckInteraction() {
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(100.f),
		Params
	);

	if (bResult) {
		if (HitResult.GetActor()) {
		}
	}
}

// Called to bind functionality to input
void APeppy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APeppy::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APeppy::MoveRight);
	PlayerInputComponent->BindAction("SetDestination", IE_Pressed, this, &APeppy::SetDestination);
}

