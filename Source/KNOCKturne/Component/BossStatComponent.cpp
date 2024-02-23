// Fill out your copyright notice in the Description page of Project Settings.


#include "BossStatComponent.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/KNOCKturneGameInstance.h"
#include "Actor/Boss.h"
#include "GameMode/NTBattleGameMode.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widget/DamageTextWidget.h"
#include "Components/TextBlock.h"

UBossStatComponent::UBossStatComponent()
{
}

void UBossStatComponent::InitializeComponent() {
	Super::InitializeComponent();

}

// Called when the game starts
void UBossStatComponent::BeginPlay()
{
	Super::BeginPlay();

	BossActor = Cast<ABoss>(GetOwner());
	NTCHECK(BossActor != nullptr);
	SetDefaultStat();
}

void UBossStatComponent::SetDefaultStat() {
	auto KNOCKturneGameInstance = Cast<UKNOCKturneGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NTCHECK(KNOCKturneGameInstance != nullptr);
	BattleTableManagerSystem = KNOCKturneGameInstance->GetSubsystem<UBattleTableManagerSystem>();
	NTCHECK(BattleTableManagerSystem != nullptr);

	CurStatData = BattleTableManagerSystem->GetBossStatDataOnTable("Init");
	MinStatData = BattleTableManagerSystem->GetBossStatDataOnTable("Min");
	MaxStatData = BattleTableManagerSystem->GetBossStatDataOnTable("Max");
}

void UBossStatComponent::GetDamaged(float Value) {
	BossActor->PlayAttackedMontage();
	TryUpdateCurStatData(FStatType::EP, -Value);
	CreateDamageText(Value);
}

bool UBossStatComponent::TryUpdateCurStatData(FStatType StatType, float Value) {
	switch (StatType) {
	case FStatType::EP:
		CurStatData.EP = FMath::Clamp<int32>(CurStatData.EP + Value, 0, CurStatData.MaxEP);
		if (CurStatData.EP <= 0) {
			CurStatData.EP = 0;
			// ���� ���� �� Die ó���� �ϱ� ���� Flag�� �����ϰ� BattleManager�� TurnChange()���� ���� Die �޼��带 ȣ����.
			BossActor->IsDie = true;
		}
		break;
	case FStatType::AttackDamage:
		CurStatData.AttackDamage += Value;
		break;
	case FStatType::BossEnergyDrop:
		CurStatData.BossEnergyDrop += Value;
		break;
	default:
		NTLOG(Error, TEXT("PeppyStatType is invalid!"));
		return false;
	}
	return true;
}

void UBossStatComponent::CreateDamageText(float Value)
{
	class UDamageTextWidget* DamageTextWidget;
	FVector2D ScreenPos;
	if (BossActor->DamageTextWidgetClass) {
		DamageTextWidget = CreateWidget<UDamageTextWidget>(GetWorld(), BossActor->DamageTextWidgetClass);
		if (DamageTextWidget) {
			DamageTextWidget->AddToViewport();
			UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(UGameplayStatics::GetPlayerController(this, 0), BossActor->GetActorLocation(), ScreenPos, false);
			ScreenPos.X += 200;
			ScreenPos.Y -= 900;
			UWidgetLayoutLibrary::SlotAsCanvasSlot(DamageTextWidget->CanvasPanel)->SetPosition(ScreenPos);
			DamageTextWidget->PlayAnimation(DamageTextWidget->DamageTextUp);
			DamageTextWidget->TextBlock_Damage->SetText(FText::FromString(FString::FromInt(-Value)));
		}
	}
}
