// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManagerSystem.h"
#include "BattleFoothold.h"
#include "Kismet/GameplayStatics.h"

UBattleManagerSystem::UBattleManagerSystem() {
	InitializeFootholdObject();

	LeftCurTurnTime = 0;

	SelectedSkills1.SetNum(8);

	InitIconRowMap();
	InitIconSkillActorMap();
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
void UBattleManagerSystem::SetSizeOfSelectedSkills1(int size) {
	SelectedSkills1.SetNum(size);
}

int UBattleManagerSystem::GetSizeOfSelectedSkills1() {
	return SelectedSkills1.Num();
}

void UBattleManagerSystem::SetOneSelectedSkills1(int index, int value) {
	SelectedSkills1[index] = value;
}

int UBattleManagerSystem::GetOneSelectedSkills1(int index) {
	return SelectedSkills1[index];
}

TArray<int32> UBattleManagerSystem::GetSelectedSkills1() {
	return SelectedSkills1;
}

void UBattleManagerSystem::InitIconRowMap() {
	IconRowMap.Add("Icon_skill_PS_WithYou", 0);
	IconRowMap.Add("Icon_skill_PS_ConsolationMusic", 1);
	IconRowMap.Add("Icon_skill_PS_Campfire", 2);
	IconRowMap.Add("Icon_skill_PS_LetMeHug", 3);
	IconRowMap.Add("Icon_skill_PS_Starlight", 4);
	IconRowMap.Add("Icon_skill_PS_CharmingVoice", 5);
	IconRowMap.Add("Icon_skill_PS_RedEyes", 6);
	IconRowMap.Add("Icon_skill_PS_AdviceforFreshStart", 7);
	IconRowMap.Add("Icon_skill_PS_AngryScolding", 8);
	IconRowMap.Add("Icon_skill_PS_ExhaustiveAdvice", 9);
	IconRowMap.Add("Icon_skill_PS_NeedtoRecharge", 10);
	IconRowMap.Add("Icon_skill_PS_PretendtoCry", 11);
	IconRowMap.Add("Icon_skill_PS_EfficientEmpathy", 12);
	IconRowMap.Add("Icon_skill_PS_AmbiguousEmotion", 13);
}

int32 UBattleManagerSystem::FindRow(FString IconName) {
	return *IconRowMap.Find(IconName);
}


/*페피 턴*/
void UBattleManagerSystem::InitIconSkillActorMap() {
	/*IconSkillActorMap.Add("None", );
	IconSkillActorMap.Add("Icon_skill_PS_WithYou", );
	IconSkillActorMap.Add("Icon_skill_PS_ConsolationMusic", );
	IconSkillActorMap.Add("Icon_skill_PS_Campfire", );
	IconSkillActorMap.Add("Icon_skill_PS_LetMeHug", );
	IconSkillActorMap.Add("Icon_skill_PS_Starlight", );
	IconSkillActorMap.Add("Icon_skill_PS_CharmingVoice", );
	IconSkillActorMap.Add("Icon_skill_PS_RedEyes", );
	IconSkillActorMap.Add("Icon_skill_PS_AdviceforFreshStart", );
	IconSkillActorMap.Add("Icon_skill_PS_AngryScolding", );
	IconSkillActorMap.Add("Icon_skill_PS_ExhaustiveAdvice", );
	IconSkillActorMap.Add("Icon_skill_PS_NeedtoRecharge", );
	IconSkillActorMap.Add("Icon_skill_PS_PretendtoCry", );
	IconSkillActorMap.Add("Icon_skill_PS_EfficientEmpathy", );
	IconSkillActorMap.Add("Icon_skill_PS_AmbiguousEmotion", );*/
}

AActor* UBattleManagerSystem::FindSkillActor(FString IconName) {
	return IconSkillActorMap.Find(IconName);
}

void UBattleManagerSystem::AddSelectedSkillActor(AActor* SkillActor) {
	SelectedSkillActor.Add(SkillActor);
}