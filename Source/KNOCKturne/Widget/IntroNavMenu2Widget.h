// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IntroNavMenu2Widget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UIntroNavMenu2Widget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

	class AKNOCKturneGameState* KNOCKturneGameState;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Continue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_NewGame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Setting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Exit;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_FadeInOutClass;

	UFUNCTION(BlueprintCallable)
	void ClickContinue();
	UFUNCTION(BlueprintCallable)
	void InactiveContinue();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFadeOutAnim();
};
