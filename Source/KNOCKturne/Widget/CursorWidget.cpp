// Fill out your copyright notice in the Description page of Project Settings.


#include "CursorWidget.h"
#include "KNOCKturne.h"

void UCursorWidget::Construct() {
	Super::Construct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(false);
}

void UCursorWidget::Tick(float DeltaTime) {
	float mouseX, mouseY;
	PlayerController->GetMousePosition(mouseX, mouseY);
	FVector2D mousePos(mouseX, mouseY);
	SetPositionInViewport(mousePos);
}