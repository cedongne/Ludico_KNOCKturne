// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/KNOCKturneGameInstance.h"
#include "Actor/Peppy.h"
#include "GameMode/NTBattleGameMode.h"
#include "Widget/DamageTextWidget.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

UPeppyStatComponent::UPeppyStatComponent()
{
	bWantsInitializeComponent = true;
	PeppyActor = Cast<APeppy>(GetOwner());
}


void UPeppyStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPeppyStatComponent::InitializeComponent() {
	Super::InitializeComponent();
	SetDefaultStat();
}

void UPeppyStatComponent::SetDefaultStat() {
	auto KNOCKturneGameInstance = Cast<UKNOCKturneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NTCHECK(KNOCKturneGameInstance != nullptr);
	BattleTableManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleTableManagerSystem>();
	NTCHECK(BattleTableManagerSystem != nullptr);
	BattleManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleManagerSystem>();
	NTCHECK(BattleManagerSystem != nullptr);
	ActorManagerSystem = KNOCKturneGameInstance->GetSubsystem<UActorManagerSystem>();
	NTCHECK(ActorManagerSystem != nullptr);

	CurStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Init");
	MinStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Min");
	MaxStatData = BattleTableManagerSystem->GetPeppyStatDataOnTable("Max");
}

void UPeppyStatComponent::GetDamaged(float Value) {
	float DamageValue = Value + ActorManagerSystem->BossActor->StatComponent->CurStatData.AttackDamage - this->CurStatData.DefenseDamage;

	if (PeppyActor->BuffComponent->GetShieldNum() > 0) {
		PeppyActor->BuffComponent->ReduceOneShield();
		NTLOG(Warning, TEXT("Shield: Remained Shield Num %d"), PeppyActor->BuffComponent->GetShieldNum());
	}
	else {
		if (CanBeDamaged) {
			TryUpdateCurStatData(FStatType::EP, -DamageValue);
			CreateDamageText(DamageValue);
		}
	}
}

bool UPeppyStatComponent::TryUpdateCurStatData(FStatType StatType, float Value) {
	switch (StatType) {
	case FStatType::EP:
		CurStatData.EP = FMath::Clamp<int32>(CurStatData.EP + Value, 0, CurStatData.MaxEP);
		if (CurStatData.EP <= 0) {
			CurStatData.EP = 0;

			BattleGameMode->GameOver();
		}
		break;
	case FStatType::Energy:
		CurStatData.Energy = FMath::Clamp<int32>(CurStatData.Energy + Value, 0, CurStatData.MaxEnergy);
		break;
	case FStatType::AttackDamage:
		CurStatData.AttackDamage += Value;
		break;
	default:
		NTLOG(Error, TEXT("PeppyStatType is invalid!"));
		return false;
	}
	return true;
}

void UPeppyStatComponent::CreateDamageText(float Value)
{
	class UDamageTextWidget* DamageTextWidget;
	FVector2D ScreenPos;
	if (PeppyActor->DamageTextWidgetClass) {
		DamageTextWidget = CreateWidget<UDamageTextWidget>(GetWorld(), PeppyActor->DamageTextWidgetClass);
		if (DamageTextWidget) {
			DamageTextWidget->AddToViewport();
			UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(UGameplayStatics::GetPlayerController(this, 0), PeppyActor->GetActorLocation(), ScreenPos, false);
			ScreenPos.X += 50;
			ScreenPos.Y -= 50;
			UWidgetLayoutLibrary::SlotAsCanvasSlot(DamageTextWidget->CanvasPanel)->SetPosition(ScreenPos);
			DamageTextWidget->PlayAnimation(DamageTextWidget->DamageTextUp);
			DamageTextWidget->TextBlock_Damage->SetText(FText::FromString(FString::FromInt(-Value)));
		}
	}
}
