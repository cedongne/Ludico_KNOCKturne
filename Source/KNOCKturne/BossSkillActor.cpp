// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillActor.h"
#include "Peppy.h"
#include "PeppyStatComponent.h"
#include "Engine/DataTable.h"
#include "BattleTableManagerSystem.h"

// Sets default values
ABossSkillActor::ABossSkillActor()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("DataTable'/Game/DataTables/MyDataTable.MyDataTable'"));

	
	if (DataTableAsset.Succeeded())
	{
		
		// Set the DataTable asset reference
		UDataTable* MyDataTable = DataTableAsset.Object;
	}
}

void ABossSkillActor::BeginPlay() {
	Super::BeginPlay();
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManager = GameInstance->GetSubsystem<UBattleTableManagerSystem>();

//	FBossSkillData* TempSkillData = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*(GetClass()->GetName()), TEXT(""));
//	SkillData = *TempSkillData;	// ������ Ÿ���� FBossSkillData ����ü ������ �� Ÿ���� FBossSkillData ������ ������ �������� �����ϴ� ���� �Ұ�����.
								// = �������� ���ǰ� �Ǿ� ���� �ʴٴ� ����.
}

void ABossSkillActor::SetSkillData(FBossSkillData NewSkillData) {
	SkillData = NewSkillData;
	IsInitialized = true;
}

void ABossSkillActor::SetSkillDataWithName(FString SkillName) {
//	FBossSkillData* SkillDataPtr = BattleTableManager->BossSkillTable->FindRow<FBossSkillData>(*SkillName, TEXT(""));
	IsInitialized = true;
}
void ABossSkillActor::HitPlayer() {
	NTLOG(Warning, TEXT("%d"), SkillData.Value_1_N);
	APeppy* Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));
	Peppy->PeppyHit(SkillData.Value_1_N);
}

FVector ABossSkillActor::GetDeltaDurationMove(FVector StartPosition, FVector EndPosition, float Duration, float DeltaTime) {
	return FMath::Lerp<FVector>(StartPosition, EndPosition, DeltaTime / Duration) - StartPosition;
}