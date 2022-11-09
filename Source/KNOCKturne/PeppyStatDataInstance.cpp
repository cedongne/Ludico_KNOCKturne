// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyStatDataInstance.h"

void UPeppyStatDataInstance::Init() {
	Super::Init();
}

UPeppyStatDataInstance::UPeppyStatDataInstance() {
	FString PeppyStatDataPath = TEXT("/Game/Assets/DataTable/PeppyStat.PeppyStat");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PEPPYSTATTABLE(*PeppyStatDataPath);
	PeppyStatDataTable = DT_PEPPYSTATTABLE.Object;
}

FPeppyStatData* UPeppyStatDataInstance::GetPeppyStatData(FString DataType) {
	return PeppyStatDataTable->FindRow<FPeppyStatData>(*DataType, TEXT(""));
}