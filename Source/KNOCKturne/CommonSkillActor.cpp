// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSkillActor.h"


#include "KNOCKturneGameInstance.h"

// Sets default values
ACommonSkillActor::ACommonSkillActor()
{

}

// Called when the game starts or when spawned
void ACommonSkillActor::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();

	//	BattleTableManager->BattleTableInitDelegate.AddUFunction(this, FName("InitSkillData"));

	//	FBossSkillData* TempSkillData = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*(GetClass()->GetName()), TEXT(""));
	//	SkillData = *TempSkillData;	// ������ Ÿ���� FBossSkillData ����ü ������ �� Ÿ���� FBossSkillData ������ ������ �������� �����ϴ� ���� �Ұ�����.
									// = �������� ���ǰ� �Ǿ� ���� �ʴٴ� ����.
}

FName ACommonSkillActor::GetCurrentBlueprintClassName() {	
	return *(GetClass()->GetFName().ToString());
}
