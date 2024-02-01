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

// ���� �ϵ��� �ֱ������� ��ų�� ����.
void ABoss::SpawnBossSkill() {
	TArray<FString> BossSkillKeyArray;
	BattleTableManagerSystem->BossSkillSpawnDataMap.GenerateKeyArray(BossSkillKeyArray);

	// 첫 번째 스킬로 MixedFeeling, HeightenedLonging은 나오지 않도록 한다.
	/*if (isFirstSkill) {
		BossSkillKeyArray.Remove("MixedFeeling");
		BossSkillKeyArray.Remove("HeightenedLonging");
		isFirstSkill = false;
		NTLOG(Warning, TEXT("MixedFeeling & HeightenedLonging Removed!"));
	}*/

	if (BossSkillKeyArray.Num() == 0) {
		NTLOG(Error, TEXT("BossSkillSpawnDataMap loading is invlid!"));
	}
	FBossSkillSpawnData SpawnData = BattleTableManagerSystem->BossSkillSpawnDataMap[BossSkillKeyArray[FMath::Rand() % BossSkillKeyArray.Num()]];
	FTransform SpawnTransform = SpawnData.SkillTransform[FMath::Rand() % BossSkillKeyArray.Num()];

	auto SpawnActor = GetWorld()->SpawnActor(SpawnData.SkillObjectClass, &SpawnTransform);
	auto SkillData = BattleTableManagerSystem->BossContactSkillTable->FindRow<FBossSkillData>(*(SpawnData.SkillObjectClass->GetName()), TEXT(""));

	int32 SprayEnergy = SkillData->SprayEnergy + BuffComponent->AdditionalEnergyByBuff;
	for (int count = 0; count < SprayEnergy; count++) {
		EnergySpawner->SpawnPooledObject();
	}

	float SkillLifeTime = SkillData->SkillCastTime + SkillData->SkillDelayTime;
	NextSkillDelayTime = FMath::RandRange(StatComponent->CurStatData.BossMinDelay, StatComponent->CurStatData.BossMaxDelay) - 2 + SkillData->SkillDelayTime;
	GetWorld()->GetTimerManager().SetTimer(
		UseSkillTimerHandler,
		this,
		&ABoss::SpawnBossSkill,
		SkillLifeTime + NextSkillDelayTime,
		false);
}

/*���� ���� ���۵� �� ���� ����̸� ������ ��ų�� ����.*/
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