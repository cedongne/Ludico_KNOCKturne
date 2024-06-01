// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSkillActor.h"


#include "GameInstance/KNOCKturneGameInstance.h"

ACommonSkillActor::ACommonSkillActor()
{

}

void ACommonSkillActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACommonSkillActor::Initialize() {
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleManager = Cast<ABattleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABattleManager::StaticClass()));

	//	BattleTableManager->BattleTableInitDelegate.AddUFunction(this, FName("InitSkillData"));

	//	FBossSkillData* TempSkillData = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*(GetClass()->GetName()), TEXT(""));
	//	SkillData = *TempSkillData;	// ������ Ÿ���� FBossSkillData ����ü ������ �� Ÿ���� FBossSkillData ������ ������ �������� �����ϴ� ���� �Ұ�����.
									// = �������� ���ǰ� �Ǿ� ���� �ʴٴ� ����.
	RegistSkillActorOnBattleManager();
}

FName ACommonSkillActor::GetCurrentBlueprintClassName() {	
	return *(GetClass()->GetFName().ToString());
}

bool ACommonSkillActor::TryOperateSkillEffect(ESkillUsingType SkillUsingType) {
	NTLOG(Error, TEXT("Override the (UseSkill) function!"));

	return false;
}

void ACommonSkillActor::RegistSkillActorOnBattleManager() {
	BattleManager->SkillActorsOnField.Add(this->GetFName().ToString(), this);
}