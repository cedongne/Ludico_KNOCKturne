// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/IntroNavMenu2Widget.h"
#include "GameMode/KNOCKturneGameState.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>

void UIntroNavMenu2Widget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Button_Continue = (UButton*)GetWidgetFromName(TEXT("Button_Continue"));
	Button_NewGame = (UButton*)GetWidgetFromName(TEXT("Button_NewGame"));
	Button_Setting = (UButton*)GetWidgetFromName(TEXT("Button_Setting"));
	Button_Exit = (UButton*)GetWidgetFromName(TEXT("Button_Exit"));
}

void UIntroNavMenu2Widget::NativeConstruct()
{
	Super::NativeConstruct();

	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	if (Button_Continue) {
		Button_Continue->OnClicked.AddDynamic(this, &UIntroNavMenu2Widget::ClickContinue);
	}
	InactiveContinue();
}

void UIntroNavMenu2Widget::ClickContinue()
{
	KNOCKturneGameState->LoadKNOCKturneData();

	if (BP_FadeInOutClass) {
		class UUserWidget* BP_FadeInOut = CreateWidget<UUserWidget>(GetWorld(), BP_FadeInOutClass);
		if (BP_FadeInOut) {
			BP_FadeInOut->AddToViewport();
			PlayFadeOutAnim();
		}
	}

	FTimerHandle CreateHUDTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(CreateHUDTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			UGameplayStatics::OpenLevel(this, "LV_HubWorld");
			GetWorld()->GetTimerManager().ClearTimer(CreateHUDTimerHandle);
		}), 2, false);
}

void UIntroNavMenu2Widget::InactiveContinue()
{
	if (!KNOCKturneGameState->IsSaveDataExist()) {
		Button_Continue->SetIsEnabled(false);
	}
}
