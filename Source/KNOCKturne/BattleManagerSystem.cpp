// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManagerSystem.h"
#include "BattleFoothold.h"
#include "Kismet/GameplayStatics.h"

UBattleManagerSystem::UBattleManagerSystem() {
	InitializeFootholdObject();

	LeftCurTurnTime = 0;

	//SelectedSkillCodeList.Add(13);
	SelectedSkillCodeList.SetNum(8);

	InitSkillIconRowMap();
	InitSpecialtyIconRowMap();
	InitItemIconRowMap();

	static ConstructorHelpers::FClassFinder<AActor> BP_PS_AmbiguousEmotion(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_AmbiguousEmotion"));
	IconSkillActorMap.Add("Icon_skill_PS_AmbiguousEmotion", BP_PS_AmbiguousEmotion.Class);
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


/*보따리-전투 전 준비*/
void UBattleManagerSystem::SetSizeOfSelectedSkillCodeList(int32 size) {
	SelectedSkillCodeList.SetNum(size);
}

int32 UBattleManagerSystem::GetSizeOfSelectedSkillCodeList() {
	return SelectedSkillCodeList.Num();
}

void UBattleManagerSystem::SetOneSelectedSkillCodeList(int32 index, int32 value) {
	SelectedSkillCodeList[index] = value;
}

int32 UBattleManagerSystem::GetOneSelectedSkillCodeInList(int32 index) {
	return SelectedSkillCodeList[index];
}

TArray<int32> UBattleManagerSystem::GetSelectedSkillCodeList() {
	return SelectedSkillCodeList;
}

void UBattleManagerSystem::InitSkillIconRowMap() {
	SkillIconRowMap.Add("Icon_skill_PS_WithYou", 0);
	SkillIconRowMap.Add("Icon_skill_PS_ConsolationMusic", 1);
	SkillIconRowMap.Add("Icon_skill_PS_Campfire", 2);
	SkillIconRowMap.Add("Icon_skill_PS_LetMeHug", 3);
	SkillIconRowMap.Add("Icon_skill_PS_Starlight", 4);
	SkillIconRowMap.Add("Icon_skill_PS_CharmingVoice", 5);
	SkillIconRowMap.Add("Icon_skill_PS_RedEyes", 6);
	SkillIconRowMap.Add("Icon_skill_PS_AdviceforFreshStart", 7);
	SkillIconRowMap.Add("Icon_skill_PS_AngryScolding", 8);
	SkillIconRowMap.Add("Icon_skill_PS_ExhaustiveAdvice", 9);
	SkillIconRowMap.Add("Icon_skill_PS_NeedtoRecharge", 10);
	SkillIconRowMap.Add("Icon_skill_PS_PretendtoCry", 11);
	SkillIconRowMap.Add("Icon_skill_PS_EfficientEmpathy", 12);
	SkillIconRowMap.Add("Icon_skill_PS_AmbiguousEmotion", 13);
}

int32 UBattleManagerSystem::FindSkillRow(FString IconName) {
	return *SkillIconRowMap.Find(IconName);
}

void UBattleManagerSystem::InitSpecialtyIconRowMap() {
	SpecialtyIconRowMap.Add("Icon_skill_special_wakeup", 0);
	SpecialtyIconRowMap.Add("Icon_skill_special_gatherenergy", 1);
	SpecialtyIconRowMap.Add("Icon_skill_special_positivethinking", 2);
	SpecialtyIconRowMap.Add("Icon_skill_special_narrowescape", 3);
	SpecialtyIconRowMap.Add("Icon_skill_special_pretendnotsick", 4);
	SpecialtyIconRowMap.Add("Icon_skill_special_twolives", 5);
}

int32 UBattleManagerSystem::FindSpecialtyRow(FString IconName) {
	return *SpecialtyIconRowMap.Find(IconName);
}

void UBattleManagerSystem::InitItemIconRowMap() {
	ItemIconRowMap.Add("Icon_Item_broken_cookie", 0);
	ItemIconRowMap.Add("Icon_Item_sled", 1);
	ItemIconRowMap.Add("Icon_Item_king_confidential_document", 2);
	ItemIconRowMap.Add("Icon_Item_fresh_sprout", 3);
	ItemIconRowMap.Add("Icon_Item_energy_cube", 4);
	ItemIconRowMap.Add("Icon_Item_eyedrop", 5);
}

int32 UBattleManagerSystem::FindItemlRow(FString IconName) {
	return *ItemIconRowMap.Find(IconName);
}


/*페피 턴*/
TSubclassOf<AActor> UBattleManagerSystem::FindSkillActor(FString IconName) {
	if (IconSkillActorMap.Contains(IconName)) {
		return *(IconSkillActorMap[IconName]);
	}
	else {
		return nullptr;
	}
}

void UBattleManagerSystem::AddSelectedSkillActorClassList(TSubclassOf<AActor> SkillActor) {
	SelectedSkillActorClassList.Add(SkillActor);
}

void UBattleManagerSystem::EndPeppyTurn() {
	for (auto SkillActorClass : SelectedSkillActorClassList) {
		GetWorld()->SpawnActor<AActor>(SkillActorClass);
	}
}