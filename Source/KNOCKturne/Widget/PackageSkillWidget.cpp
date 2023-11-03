// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PackageSkillWidget.h"

void UPackageSkillWidget::NativePreConstruct() {
	UniformGridPanel_Skill = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniformGridPanel_Skill"));
}

void UPackageSkillWidget::NativeConstruct() {
	int row = 0;

	for (int i = 0; i < 14; i++) {
		if (SkillListFormClass) {
			SkillListFormRef = CreateWidget<USkillListFormWidget>(GetWorld(), SkillListFormClass);
			if (SkillListFormRef) {
				SkillListArr.Add(SkillListFormRef);
				UniformGridPanel_Skill->AddChild(SkillListFormRef);
				if (i % 2 == 1) {
					UniformGridPanel_Skill->AddChildToUniformGrid(SkillListFormRef, row, 1);
					++row;
				}
				else {
					UniformGridPanel_Skill->AddChildToUniformGrid(SkillListFormRef, row, 0);
				}
			}
		}
	}
}