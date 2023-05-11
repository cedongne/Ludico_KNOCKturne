// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManagerSystem.h"
#include "BattleFoothold.h"
#include "Kismet/GameplayStatics.h"

UBattleManagerSystem::UBattleManagerSystem() {
	InitializeFootholdObject();

	LeftCurTurnTime = 0;

	SelectedSkills1.SetNum(8);
}

void UBattleManagerSystem::InitializeFootholdObject() {
	FName PATH = TEXT("/Game/Blueprints/Actors/Battle/BP_BattleFoothold.BP_BattleFoothold_C");
	FootholdClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *PATH.ToString()));
	
	FActorSpawnParameters SpawnParams;
	FRotator Rotator;
	FVector SpawnLocation = FVector::ZeroVector;

	FTransform Transform = FTransform::Identity;
}

void UBattleManagerSystem::SpawnFoothold() {
	NTLOG_S(Warning);
	NTCHECK(FootholdObject == nullptr);
	FootholdObject = GetWorld()->SpawnActor(FootholdSubclass);
//	Cast<ABattleFoothold>(FootholdObject)->SetFoothold();
//	NTLOG(Warning, TEXT("%d"), Cast<ABattleFoothold>(FootholdObject)->data);
}

void UBattleManagerSystem::SetTimerUnvisibleHitArea() {
	FTimerHandle FlagUnsetTimer;
	GetWorld()->GetTimerManager().ClearTimer(FlagUnsetTimer);
	float UnsetTime = 8.0f;

	GetWorld()->GetTimerManager().SetTimer(FlagUnsetTimer, FTimerDelegate::CreateLambda([&]()
		{
			VisibleBossSkillHitArea = false;
		}), UnsetTime, false);
}

// 허브월드 보따리에서 선택한 스킬 리스트 크기 설정
void UBattleManagerSystem::SetSizeOfSelectedSkills1(int size) {
	SelectedSkills1.SetNum(size);
}

int UBattleManagerSystem::GetSizeOfSelectedSkills1() {
	return SelectedSkills1.Num();
}

// 허브월드 보따리에서 선택한 스킬 값 설정하기
void UBattleManagerSystem::SetOneSelectedSkills1(int index, int value) {
	SelectedSkills1[index] = value;
}

// 허브월드 보따리에서 선택한 스킬 값 가져오기
int UBattleManagerSystem::GetOneSelectedSkills1(int index) {
	return SelectedSkills1[index];
}

TArray<int32> UBattleManagerSystem::GetSelectedSkills1() {
	return SelectedSkills1;
}