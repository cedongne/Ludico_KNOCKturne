// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillUIStructure.generated.h"

/**
 * 
 */

class KNOCKTURNE_API SkillUIStructure
{
public:
	SkillUIStructure();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_battleSetting_background_default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_battleSetting_skill_default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Icon_skill_PS_WithYou;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* icon_checkbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UI_battleSetting_skill_none;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* image;

	UFUNCTION()
	void InitializeSkillStructure(FSkillStructureData SkillStructure);
	UFUNCTION()
	void InitializeSelectedSkillStructure(FSelectedSkillStructureData SelectedSkillStructure);
	UFUNCTION()
	void InitializeItemStructure(FItemStructureData ItemStructure);
};

USTRUCT(BlueprintType)
struct FSkillStructureData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> BackgroundImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> IconBackgroundImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> SkillIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> CheckBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText Stance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 CoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESlateVisibility NumVisibility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText Description;
};

USTRUCT(BlueprintType)
struct FSelectedSkillStructureData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> BackgroundImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESlateVisibility IconVisibility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESlateVisibility CancelButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESlateVisibility NumVisibility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESlateVisibility NumBackgroundVisibility;
};

USTRUCT(BlueprintType)
struct FItemStructureData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> BackgroundImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> IconBackgroundImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TObjectPtr<UTexture2D> CheckBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText SkillName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText Description;
};
