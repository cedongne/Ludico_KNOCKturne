#include "Boss.h"
#include "BossSkillActor.h"
#include "GameInstance/KNOCKturneGameInstance.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UBossStatComponent>(TEXT("StatComponent"));
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));

	static ConstructorHelpers::FClassFinder<AActor> BP_EnergySpawnerPath(TEXT("/Game/Blueprints/Actors/Battle/BP_EnergySpawner"));
	BP_EnergySpawnerClass = BP_EnergySpawnerPath.Class;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	auto KNOCKturneGameInstance = Cast<UKNOCKturneGameInstance>(GetGameInstance());
	BattleTableManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleTableManagerSystem>();

	EnergySpawner = Cast<UKNOCKturneObjectPool>(GetWorld()->SpawnActor<AActor>(BP_EnergySpawnerClass)->GetComponentByClass(UKNOCKturneObjectPool::StaticClass()));
}

void ABoss::PostInitializeComponents() {
	Super::PostInitializeComponents();

	StatComponent->SetDefaultStat();
}

// 보스 턴동안 주기적으로 스킬을 스폰.
void ABoss::SpawnBossSkill() {
	TArray<FString> BossSkillKeyArray;
	BattleTableManagerSystem->BossSkillSpawnDataMap.GenerateKeyArray(BossSkillKeyArray);

	if (BossSkillKeyArray.Num() == 0) {
		NTLOG(Error, TEXT("BossSkillSpawnDataMap loading is invlid!"));
	}
	FBossSkillSpawnData SpawnData = BattleTableManagerSystem->BossSkillSpawnDataMap[BossSkillKeyArray[FMath::Rand() % BossSkillKeyArray.Num()]];
	FTransform SpawnTransform = SpawnData.SkillTransform[FMath::Rand() % BossSkillKeyArray.Num()];
	auto SpawnActor = GetWorld()->SpawnActor(SpawnData.SkillObjectClass, &SpawnTransform);

	auto SkillData = BattleTableManagerSystem->BossContactSkillTable->FindRow<FBossSkillData>(*(SpawnData.SkillObjectClass->GetName()), TEXT(""));
	for (int count = 0; count < SkillData->SprayEnergy; count++) {
		EnergySpawner->SpawnPooledObject();
	}

	float SkillLifeTime = SkillData->SkillCastTime + SkillData->SkillDelayTime;
	float NextSkillDelayTime = FMath::RandRange(StatComponent->CurStatData.BossMinDelay, StatComponent->CurStatData.BossMaxDelay) - 2 + SkillData->SkillDelayTime;
	GetWorld()->GetTimerManager().SetTimer(
		UseSkillTimerHandler,
		this,
		&ABoss::SpawnBossSkill,
		SkillLifeTime + NextSkillDelayTime,
		false);
}

/*보스 턴이 시작될 때 일정 딜레이를 가지고 스킬을 스폰.*/
void ABoss::SpawnBossSkillWhenStartBossTurn() {
	GetWorld()->GetTimerManager().SetTimer(
		UseSkillTimerHandler,
		this,
		&ABoss::SpawnBossSkill,
		FMath::RandRange(StatComponent->CurStatData.BossMinDelay, StatComponent->CurStatData.BossMaxDelay),
		false);
}

void ABoss::ClearUseSkillTimer() {
	GetWorld()->GetTimerManager().ClearTimer(UseSkillTimerHandler);
}

void ABoss::Die() {
	IsDie = true;
	BP_Die();
}