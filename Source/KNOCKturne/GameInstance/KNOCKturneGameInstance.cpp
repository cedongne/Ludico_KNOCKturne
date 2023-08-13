// Fill out your copyright notice in the Description page of Project Settings.


#include "KNOCKturneGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Component/DialogueTableComponent.h"

void UKNOCKturneGameInstance::Init() {
	Super::Init();
//	PeppyTransform.SetLocation(FVector(933.0f, 993.0f, 104.287613f));
	auto GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
}

UKNOCKturneGameInstance::UKNOCKturneGameInstance() {
}
