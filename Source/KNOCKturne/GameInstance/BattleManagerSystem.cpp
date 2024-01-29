// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManagerSystem.h"
#include "GameMode/NTBattleGameMode.h"
#include "Actor/BattleManager.h"
#include "Components/WidgetComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/ActorManagerSystem.h"
#include "Kismet/GameplayStatics.h"

UBattleManagerSystem::UBattleManagerSystem() {

	SelectedSkillCodeList.Init(-1, 8);

	InitSkillIconRowMap();
	InitSpecialtyIconRowMap();
	InitItemIconRowMap();

	static ConstructorHelpers::FClassFinder<AActor> BP_PS_AmbiguousEmotion(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_AmbiguousEmotion"));
	IconSkillActorMap.Add("Icon_skill_PS_AmbiguousEmotion", BP_PS_AmbiguousEmotion.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_WithYou(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_WithYou"));
	IconSkillActorMap.Add("Icon_skill_PS_WithYou", BP_PS_WithYou.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_EfficientEmpathy(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_EfficientEmpathy"));
	IconSkillActorMap.Add("Icon_skill_PS_EfficientEmpathy", BP_PS_EfficientEmpathy.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_LetMeHug(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_LetMeHug"));
	IconSkillActorMap.Add("Icon_skill_PS_LetMeHug", BP_PS_LetMeHug.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_CharmingVoice(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_CharmingVoice"));
	IconSkillActorMap.Add("Icon_skill_PS_CharmingVoice", BP_PS_CharmingVoice.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_RedEyes(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_RedEyes"));
	IconSkillActorMap.Add("Icon_skill_PS_RedEyes", BP_PS_RedEyes.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_ExhaustiveAdvice(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_ExhaustiveAdvice"));
	IconSkillActorMap.Add("Icon_skill_PS_ExhaustiveAdvice", BP_PS_ExhaustiveAdvice.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_PretendtoCry(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_PretendtoCry"));
	IconSkillActorMap.Add("Icon_skill_PS_PretendtoCry", BP_PS_PretendtoCry.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_ConsolationMusic(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_ConsolationMusic"));
	IconSkillActorMap.Add("Icon_skill_PS_ConsolationMusic", BP_PS_ConsolationMusic.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_Campfire(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_Campfire"));
	IconSkillActorMap.Add("Icon_skill_PS_Campfire", BP_PS_Campfire.Class);
	static ConstructorHelpers::FClassFinder<AActor> BP_PS_Starlight(TEXT("/Game/Blueprints/Skills/Peppy/BP_PS_Starlight"));
	IconSkillActorMap.Add("Icon_skill_PS_Starlight", BP_PS_Starlight.Class);
}

void UBattleManagerSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	
	auto GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	ActorManagerSystem = GameInstance->GetSubsystem<UActorManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
}

void UBattleManagerSystem::SetTimerUnvisibleHitArea() {
	FTimerHandle FlagUnsetTimer;
	GetWorld()->GetTimerManager().ClearTimer(FlagUnsetTimer);
	float UnsetTime = 8.0f;

	for(auto AttackRange : CurBossSkillHitArea)
	{
		if (AttackRange == nullptr) {
			break;
		}
		AttackRange->bHiddenInGame = false;
	}

	GetWorld()->GetTimerManager().SetTimer(FlagUnsetTimer, FTimerDelegate::CreateLambda([&]()
		{
			VisibleBossSkillHitArea = false;
		}), UnsetTime, false);
}


/*������-���� �� �غ�*/
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

int32 UBattleManagerSystem::FindItemRow(FString IconName) {
	return *ItemIconRowMap.Find(IconName);
}


/*���� ��*/
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

void UBattleManagerSystem::UpdateDreamDiaryWhenGameOver() {
	// DreamDiaryOpenRow = FMath::Clamp((DreamDiaryOpenRow + 1), 0, 4);

	if (DreamDiaryOpenRow < 3) {
		DreamDiaryOpenRow += 1;
		KNOCKturneGameState->isDreamDiaryUpdated = true;
	}
	else {
		KNOCKturneGameState->isDreamDiaryUpdated = false;
	}
}

void UBattleManagerSystem::UpdateDreamDiaryWhenGameClear() {
	DreamDiaryOpenRow = 3;
}

void UBattleManagerSystem::GetDreamFragmentAfterBattle() {
	if (ReducedEP >= 30) {
		KNOCKturneGameState->DreamFragmentCount += 1;
		KNOCKturneGameState->GetDreamFragment = true;
	}
	else {
		NTLOG(Warning, TEXT("Did not satisfy the condition"));
	}

	NTLOG(Warning, TEXT("%d %d"), KNOCKturneGameState->DreamFragmentCount, KNOCKturneGameState->GetDreamFragment);
}

void UBattleManagerSystem::UpdateRoundInfo() {
	LoadBattleTableManagerSystem();

	Round++;
	LastRoundBossHpRatio = ActorManagerSystem->BossActor->StatComponent->CurStatData.EP * 100 / ActorManagerSystem->BossActor->StatComponent->CurStatData.MaxEP;
	ReducedEP = 100 - LastRoundBossHpRatio;
	NTLOG(Warning, TEXT("%d %d"), Round, LastRoundBossHpRatio);
}

void UBattleManagerSystem::LoadBattleTableManagerSystem() {
	if (BattleTableManagerSystem == nullptr) {
		UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	}
}

void UBattleManagerSystem::LoadGameState(AGameStateBase* GameState) {
	if (KNOCKturneGameState == nullptr) {
		KNOCKturneGameState = Cast<AKNOCKturneGameState>(GameState);
	}
}