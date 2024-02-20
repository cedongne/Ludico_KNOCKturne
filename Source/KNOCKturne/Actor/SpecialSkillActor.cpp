// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SpecialSkillActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASpecialSkillActor::ASpecialSkillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpecialSkillActor::BeginPlay()
{
	Super::BeginPlay();
	
	FString SpecialSkillTablePath = TEXT("/Game/Assets/DataTable/SpecialSkillTable.SpecialSkillTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SpecialSkillTABLE(*SpecialSkillTablePath);
	SpecialSkillTable = DT_SpecialSkillTABLE.Object;

	PeppyController = (APeppyController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleManagerSystem = GameInstance->GetSubsystem<UBattleManagerSystem>();
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UActorManagerSystem>();
}

// Called every frame
void ASpecialSkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpecialSkillActor::CreateSpecialSkillData()
{
}

bool ASpecialSkillActor::IsSatisfyUseCondition()
{
	return false;
}

bool ASpecialSkillActor::CheckCanUseSpecialSkill(float DeltaSeconds)
{
	return false;
}

void ASpecialSkillActor::ElapseTurn()
{
}

bool ASpecialSkillActor::TryUseSpecialSkill()
{
	return false;
}

int32 ASpecialSkillActor::GetCurSpecialSkillCoolTime()
{
	return int32();
}

