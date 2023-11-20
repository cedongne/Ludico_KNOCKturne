// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Widget/DreamDiaryWidget.h"
#include "GameMode/KNOCKturneGameState.h"

#include "HubworldHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UHubworldHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UHubworldHUDWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

	AKNOCKturneGameState* KNOCKturneGameState;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Diary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Setting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Save;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SettingText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_DiaryText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_SaveText;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image_DreamDiary_Updated;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> DreamDiaryWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDreamDiaryWidget* DreamDiaryWidgetRef;

	UFUNCTION()
	void OnClick_ButtonDiary();
};
