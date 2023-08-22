#include "Peppy.h"

#include "Component/PeppyStatComponent.h"
#include "Component/BuffComponent.h"

APeppy::APeppy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	SpringArm->TargetArmLength = 600.0f;
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

	PeppyController = UGameplayStatics::GetPlayerController(this, 0);

	StatComponent = CreateDefaultSubobject<UPeppyStatComponent>(TEXT("PeppyStatComponent"));
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));

	// Initialize variables
	CanMove = true;
	IsSlide = false;
	IsHit = false;
	CanSlide = true;

	SlideCooldown = 3.0f;
	SlidingSpeed = 1300;
	CurWalkSpeed = StandardMaxWalkSpeed * MoveSpeed;

	GetCharacterMovement()->MaxWalkSpeed = CurWalkSpeed;
}

void APeppy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APeppy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SlideHandling(DeltaTime);
}

void APeppy::PostInitializeComponents() {
	Super::PostInitializeComponents();

	StatComponent->SetDefaultStat();
/*
	PeppyStat->OnHPIsZero.AddLambda([this]() ->void {
		NTLOG(Warning, TEXT("OnHPIsZero"));
		SetActorEnableCollision(false);
		});
		*/
}

void APeppy::SetImmobile() {
	CanMove = false;
	CanSlide = false;
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
}

void APeppy::SetMobile() {
	CanMove = true;
	CanSlide = true;
	GetCapsuleComponent()->SetCollisionProfileName("Peppy");
}

void APeppy::MoveForward(float Value) {
	if (CanMove) {
		if ((Controller != nullptr) && (Value != 0.0f)) {
			if (!IsSlide) {
				const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
				AddMovementInput(Direction, Value);
			}
		}
	}
}

void APeppy::MoveRight(float Value) {
	if (CanMove) {
		if ((Controller != nullptr) && (Value != 0.0f)) {
			if (!IsSlide) {
				const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
				AddMovementInput(Direction, Value);
			}
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

	InputComponent->BindAction("Sliding", EInputEvent::IE_Pressed, this, &APeppy::SlideAction);
}


void APeppy::SlideAction() {
	NTLOG_S(Warning);
	if (CanSlide) {
		if (FollowTime <= ShortPressThreshold) {
			IsSlide = true;
			CanSlide = false;

			GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
			LeftSlideCooltime = SlideCooldown;

			FVector HitLocation = FVector::ZeroVector;
			FHitResult Hit;
			bool ExistHitResult = PeppyController->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
			if (ExistHitResult) {
				HitLocation = Hit.Location;
			}
			else {
				NTLOG(Warning, TEXT("HitResult load failed."));
				return;
			}

			FRotator RotateDegree = FRotator(0.0f, (HitLocation - GetActorLocation()).Rotation().Yaw, 0.0f);
			GetCapsuleComponent()->SetWorldRotation(RotateDegree);

			FVector Direction = FRotationMatrix(FRotator(0, RotateDegree.Yaw, 0)).GetUnitAxis(EAxis::X);
			LaunchCharacter(Direction * SlidingSpeed, false, true);
		}
	}
}

void APeppy::SlideHandling(float DeltaTime) {
	if (LeftSlideCooltime - DeltaTime > 0.0f) {
		FVector velocity = GetMovementComponent()->Velocity;
		float CurMoveVelocity = sqrt((velocity.X * velocity.X) + (velocity.Y * velocity.Y));
		if (CurMoveVelocity > CurWalkSpeed) {
			IsSlide = true;
		}
		else {
			IsSlide = false;
		}
		LeftSlideCooltime -= DeltaTime;
	}
	else {
		LeftSlideCooltime = 0.0f;
		if (CanMove) {
			CanSlide = true;
		}
	}
}

void APeppy::AddCumulativeDamageBeforeStartTurn(FString EffectId, TArray<int32> Damages) {
	while (DamageArrayEachTurn.Num() < Damages.Num()) {
		DamageArrayEachTurn.Add(TMap<FString, int32>());
	}

	for (int32 index = 0; index < Damages.Num(); index++) {
		int32* Damage = DamageArrayEachTurn[index].Find(EffectId);
		Damages[index] += (Damage != nullptr) ? *Damage : 0;

		DamageArrayEachTurn[index].Add(EffectId, Damages[index]);
	}
}

void APeppy::AddDamageBeforeStartTurn(FString EffectId, TArray<int32> Damages) {
	while (DamageArrayEachTurn.Num() < Damages.Num()) {
		DamageArrayEachTurn.Add(TMap<FString, int32>());
	}
	for (int32 index = 0; index < Damages.Num(); index++) {
		DamageArrayEachTurn[index].FindOrAdd(EffectId, Damages[index]);
	}
}

void APeppy::Die() {
	IsDie = true;

	BP_Die();
}