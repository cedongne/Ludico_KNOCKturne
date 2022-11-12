// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatDataInstance.h"

void UPeppyStatDataInstance::Init() {
	Super::Init();
	NTLOG_S(Warning);
}

UPeppyStatDataInstance::UPeppyStatDataInstance() {
	FString PeppyStatDataPath = TEXT("/Game/Assets/DataTable/PeppyStat.PeppyStat");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSTATTABLE(*PeppyStatDataPath);
	NTCHECK(DT_PEPPYSTATTABLE.Succeeded());
	PeppyStatDataTable = DT_PEPPYSTATTABLE.Object;
	NTCHECK(PeppyStatDataTable->GetRowMap().Num() > 0);
}

FPeppyStatData* UPeppyStatDataInstance::GetPeppyStatData(FString DataType) {
	auto RowData = PeppyStatDataTable->FindRow<FPeppyStatData>(*DataType, TEXT("Fail to load data"));
	NTLOG(Warning, TEXT("%s %d"), *DataType, RowData->SlidingCooldown);
	return RowData;
}