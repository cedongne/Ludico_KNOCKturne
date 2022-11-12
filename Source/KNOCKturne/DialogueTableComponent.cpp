// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTableComponent.h"

UDialogueTableComponent::UDialogueTableComponent() {
	NTLOG(Warning, TEXT("UDialogueTableComponent is created."));
}

// Sets default values for this component's properties
UDialogueTableComponent::UDialogueTableComponent(FString TablePath)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;

	// ...
}


void UDialogueTableComponent::LoadDialogueTable(FString TablePath) {
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TABLE(*TablePath);
	DialogueTable = DT_TABLE.Object;
}

FDialogueData* UDialogueTableComponent::GetData(FString RowID) {
	return DialogueTable->FindRow<FDialogueData>(*RowID, TEXT(""));
}

