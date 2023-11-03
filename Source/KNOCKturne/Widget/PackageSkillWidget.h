// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "SkillListFormWidget.h"

#include "PackageSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKTURNE_API UPackageSkillWidget : public UUserWidget
{
	GENERATED_BODY()
	void NativePreConstruct();
	void NativeConstruct();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel_Skill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SkillListFormClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkillListFormWidget* SkillListFormRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USkillListFormWidget*> SkillListArr;
};
