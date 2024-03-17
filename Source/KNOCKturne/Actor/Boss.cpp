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
	BattleManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBattleManagerSystem>();

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

	// 확률에 따라 보스와 같은 스탠스를 가진 스킬 혹은 기본 스킬 시전
	FString CurBossSkillStance;
	if (FMath::FRand() < 0.7) {
		CurBossSkillStance = BattleManagerSystem->BossStanceID;
	}
	else {
		CurBossSkillStance = "Default";
	}

	TArray<FString> CurBossStanceSkillArray = GetSpawnableBossSkills(BossSkillKeyArray, CurBossSkillStance);
	/*for (auto Key : BossSkillKeyArray) {
		FString SkillObjectClassName = BattleTableManagerSystem->BossSkillSpawnDataMap[Key].SkillObjectClass->GetName();
		auto TempSkillData = BattleTableManagerSystem->BossContactSkillTable->FindRow<FBossSkillData>(*(SkillObjectClassName), TEXT(""));
		if (TempSkillData == nullptr) {
			TempSkillData = BattleTableManagerSystem->BossNonContactSkillTable->FindRow<FBossSkillData>(*(SkillObjectClassName), TEXT(""));
		}

		if (TempSkillData->SkillStance == CurBossSkillStance && !BossSkillNameCoolTimeMap.Contains(TempSkillData->BossSkillID)) {
			CurBossStanceSkillArray.Add(Key);
		}
	}*/

	// 스탠스가 디폴트가 아닌 스킬을 시전해야 하는데, 모두 쿨타임이 지나지 않았을 때
	if (CurBossStanceSkillArray.Num() == 0 && CurBossSkillStance != "Default") {
		CurBossStanceSkillArray = GetSpawnableBossSkills(BossSkillKeyArray, "Default");
	}

	// 첫 번째 스킬로 MixedFeeling, HeightenedLonging은 나오지 않도록 한다.
	/*if (isFirstSkill) {
		CurBossStanceSkillArray.Remove("MixedFeeling");
		CurBossStanceSkillArray.Remove("HeightenedLonging");
		isFirstSkill = false;
		NTLOG(Warning, TEXT("MixedFeeling & HeightenedLonging Removed!"));
	}*/

	if (CurBossStanceSkillArray.Num() == 0) {
		NTLOG(Error, TEXT("BossSkillSpawnDataMap loading is invlid!"));
	}
	FBossSkillSpawnData SpawnData = BattleTableManagerSystem->BossSkillSpawnDataMap[CurBossStanceSkillArray[FMath::Rand() % CurBossStanceSkillArray.Num()]];
	FTransform SpawnTransform = SpawnData.SkillTransform[FMath::Rand() % CurBossStanceSkillArray.Num()];

	auto SpawnActor = GetWorld()->SpawnActor(SpawnData.SkillObjectClass, &SpawnTransform);
	auto SkillData = BattleTableManagerSystem->BossContactSkillTable->FindRow<FBossSkillData>(*(SpawnData.SkillObjectClass->GetName()), TEXT(""));
	if (SkillData == nullptr) {
		SkillData = BattleTableManagerSystem->BossNonContactSkillTable->FindRow<FBossSkillData>(*(SpawnData.SkillObjectClass->GetName()), TEXT(""));
		if (SkillData == nullptr) {
			NTLOG(Error, TEXT("Cannot Find SkillData From BossSkillTable!"));
			return;
		}
	}

	// 에너지 뿌리기
	int32 SprayEnergy = SkillData->SprayEnergy + BuffComponent->AdditionalEnergyByBuff;
	for (int count = 0; count < SprayEnergy; count++) {
		EnergySpawner->SpawnPooledObject();
	}

	// 공격 애니메이션 실행
	PlayAttackMontage();

	// 보스 스킬 쿨타임
	if (SkillData->SkillCoolTurn > 0)
		BossSkillNameCoolTimeMap.Add(SkillData->BossSkillID, SkillData->SkillCoolTurn);
	ElapseCoolTime();

	float SkillLifeTime = SkillData->SkillCastTime + SkillData->SkillDelayTime;
	NextSkillDelayTime = FMath::RandRange(StatComponent->CurStatData.BossMinDelay, StatComponent->CurStatData.BossMaxDelay) - 2 + SkillData->SkillDelayTime;
	GetWorld()->GetTimerManager().SetTimer(
		UseSkillTimerHandler,
		this,
		&ABoss::SpawnBossSkill,
		SkillLifeTime + NextSkillDelayTime,
		false);
}

TArray<FString> ABoss::GetSpawnableBossSkills(TArray<FString> BossSkillKeyArray, FString CurBossSkillStance)
{
	TArray<FString> CurBossStanceSkillArray;
	for (auto Key : BossSkillKeyArray) {
		FString SkillObjectClassName = BattleTableManagerSystem->BossSkillSpawnDataMap[Key].SkillObjectClass->GetName();
		auto TempSkillData = BattleTableManagerSystem->BossContactSkillTable->FindRow<FBossSkillData>(*(SkillObjectClassName), TEXT(""));
		if (TempSkillData == nullptr) {
			TempSkillData = BattleTableManagerSystem->BossNonContactSkillTable->FindRow<FBossSkillData>(*(SkillObjectClassName), TEXT(""));
		}

		if (TempSkillData->SkillStance == CurBossSkillStance && !BossSkillNameCoolTimeMap.Contains(TempSkillData->BossSkillID)) {
			CurBossStanceSkillArray.Add(Key);
		}
	}

	return CurBossStanceSkillArray;
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

void ABoss::ElapseCoolTime()
{
	TArray<FString> Keys;
	BossSkillNameCoolTimeMap.GetKeys(Keys);

	for (auto Key : Keys) {
		if (--BossSkillNameCoolTimeMap[Key] == 0)
			BossSkillNameCoolTimeMap.Remove(Key);
	}
}

void ABoss::Die() {
	class ABattleManager* BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));
	BattleManager->EndItem();

	IsDie = true;
	BP_Die();
}