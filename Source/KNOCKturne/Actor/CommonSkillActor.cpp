// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSkillActor.h"


#include "GameInstance/KNOCKturneGameInstance.h"

// Sets default values
ACommonSkillActor::ACommonSkillActor()
{

}

// Called when the game starts or when spawned
void ACommonSkillActor::BeginPlay()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));

	//	BattleTableManager->BattleTableInitDelegate.AddUFunction(this, FName("InitSkillData"));

	//	FBossSkillData* TempSkillData = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*(GetClass()->GetName()), TEXT(""));
	//	SkillData = *TempSkillData;	// 포인터 타입의 FBossSkillData 구조체 변수를 값 타입의 FBossSkillData 변수에 포인터 연산으로 저장하는 것이 불가능함.
									// = 연산자의 정의가 되어 있지 않다는 에러.
	RegistSkillActorOnBattleManager();
	Super::BeginPlay();
}

FName ACommonSkillActor::GetCurrentBlueprintClassName() {	
	return *(GetClass()->GetFName().ToString());
}

void ACommonSkillActor::RegistSkillActorOnBattleManager() {
	BattleManager->SkillActorsOnField.Add(this->GetFName().ToString(), this);
}