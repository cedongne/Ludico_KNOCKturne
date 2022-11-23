// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
	/*
	InteractionPopupUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionPopupUI->SetupAttachment(RootComponent);

	InteractionPopupUI->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	InteractionPopupUI->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> INTERACTIONPOPUP_UI(TEXT("/Game/Blueprints/UMG/InteractionPopup.InteractionPopup"));
	if (INTERACTIONPOPUP_UI.Succeeded()) {
		InteractionPopupUI->SetWidgetClass(INTERACTIONPOPUP_UI.Class);
		InteractionPopupUI->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	*/

	IsHoverMouse = false;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
//	SetInteractionPopupWidget(InteractionPopupWidget);
}


// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::SetCanInteraction_Implementation() {

}

void ANPC::SetCannotInteraction_Implementation() {

}