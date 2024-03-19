// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "GameInstance/BattleManagerSystem.h"
#include "GameInstance/BattleTableManagerSystem.h"
#include "GameInstance/ActorManagerSystem.h"

AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	ActorManagerSystem = GameInstance->GetSubsystem<UActorManagerSystem>();

	TryUseItem();
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::TryUseItem()
{
	if (BattleManagerSystem->FinalItem != "") {
		ItemName = BattleManagerSystem->FinalItem;
		ItemData = *BattleTableManagerSystem->ItemTable->FindRow<FItemData>(FName(*ItemName), TEXT("Fail to load ItemData"));

		if (ItemName == "Item_broken_cookie") {
			ActorManagerSystem->PeppyActor->GetCharacterMovement()->MaxWalkSpeed *= 1 + ItemData.value1M;
		}
		else if (ItemName == "Item_king_confidential_document") {
			CanAvoidAttack = true;
		}
		else if (ItemName == "Item_fresh_sprout") {
			UStatComponent* BossStatComponent = Cast<UStatComponent>(ActorManagerSystem->BossActor->GetComponentByClass(UStatComponent::StaticClass()));
			BossStatComponent->TryUpdateCurStatData(FStatType::MaxEP, ItemData.value1N);
			BossStatComponent->TryUpdateCurStatData(FStatType::EP, ItemData.value1N);
		}
		else if (ItemName == "Item_sled") {
			isSledItem = true;
		}
		else {
			NTLOG(Warning, TEXT("Can't Use This Item"));
		}
	}
}

void AItemActor::EndItem()
{
	if (ItemName == "") {
		return;
	}

	if (ItemName == "Item_broken_cookie") {
		ActorManagerSystem->PeppyActor->GetCharacterMovement()->MaxWalkSpeed /= 1 + ItemData.value1M;
	}
	else if (ItemName == "Item_king_confidential_document") {
		CanAvoidAttack = false;
	}
	else if (ItemName == "Item_fresh_sprout") {
		UStatComponent* BossStatComponent = Cast<UStatComponent>(ActorManagerSystem->BossActor->GetComponentByClass(UStatComponent::StaticClass()));
		BossStatComponent->TryUpdateCurStatData(FStatType::MaxEP, -ItemData.value1N);
		BossStatComponent->TryUpdateCurStatData(FStatType::EP, -ItemData.value1N);
	}
	else if (ItemName == "Item_sled") {
		isSledItem = false;
	}
}

bool AItemActor::TryAvoidAttack()
{
	if (CanAvoidAttack) {
		auto Probability = FMath::FRand();

		if (Probability <= ItemData.value1M) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void AItemActor::RecoverEPRandomly()
{
	if (!isSledItem)
		return;

	auto Probability = FMath::FRand();

	if (Probability <= ItemData.value1M) {
		UStatComponent* PeppyStatComponent = Cast<UStatComponent>(ActorManagerSystem->PeppyActor->GetComponentByClass(UStatComponent::StaticClass()));
		PeppyStatComponent->TryUpdateCurStatData(FStatType::EP, ItemData.value1N);
	}
}

