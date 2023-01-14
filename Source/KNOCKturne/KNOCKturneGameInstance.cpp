// Fill out your copyright notice in the Description page of Project Settings.


#include "KNOCKturneGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UKNOCKturneGameInstance::Init() {
	Super::Init();
	NTLOG_S(Warning);
	PeppyTransform.SetLocation(FVector(933.0f, 993.0f, 104.287613f));
	auto GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
}

UKNOCKturneGameInstance::UKNOCKturneGameInstance() {
	FString PeppyStatDataPath = TEXT("/Game/Assets/DataTable/PeppyStat.PeppyStat");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSTATDATATABLE(*PeppyStatDataPath);

	NTCHECK(DT_PEPPYSTATDATATABLE.Succeeded());
	PeppyStatDataTable = DT_PEPPYSTATDATATABLE.Object;
	NTCHECK(PeppyStatDataTable->IsValidLowLevel());

	CurPeppyStat = *GetPeppyStatData("Init");
	NTLOG(Warning, TEXT("%d"), CurPeppyStat.MaxHP);
}

FPeppyStatData* UKNOCKturneGameInstance::GetPeppyStatData(FString DataType) {
	return PeppyStatDataTable->FindRow<FPeppyStatData>(*DataType, TEXT(""));
}