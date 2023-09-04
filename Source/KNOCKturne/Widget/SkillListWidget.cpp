// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillListWidget.h"

void USkillListWidget::NativePreConstruct() {
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Button_Background_1 = (UButton*)GetWidgetFromName(TEXT("Button_Background_1"));
	Button_Background_2 = (UButton*)GetWidgetFromName(TEXT("Button_Background_2"));
	Button_Background_3 = (UButton*)GetWidgetFromName(TEXT("Button_Background_3"));
	Button_Background_4 = (UButton*)GetWidgetFromName(TEXT("Button_Background_4"));
	Button_Background_5 = (UButton*)GetWidgetFromName(TEXT("Button_Background_5"));
	Button_Background_6 = (UButton*)GetWidgetFromName(TEXT("Button_Background_6"));
	Button_Background_7 = (UButton*)GetWidgetFromName(TEXT("Button_Background_7"));
	Button_Background_8 = (UButton*)GetWidgetFromName(TEXT("Button_Background_8"));
	Button_Background_9 = (UButton*)GetWidgetFromName(TEXT("Button_Background_9"));
	Button_Background_10 = (UButton*)GetWidgetFromName(TEXT("Button_Background_10"));
	Button_Background_11 = (UButton*)GetWidgetFromName(TEXT("Button_Background_11"));
	Button_Background_12 = (UButton*)GetWidgetFromName(TEXT("Button_Background_12"));
	Button_Background_13 = (UButton*)GetWidgetFromName(TEXT("Button_Background_13"));

	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Background_1 = (UImage*)GetWidgetFromName(TEXT("Image_Background_1"));
	Image_Background_2 = (UImage*)GetWidgetFromName(TEXT("Image_Background_2"));
	Image_Background_3 = (UImage*)GetWidgetFromName(TEXT("Image_Background_3"));
	Image_Background_4 = (UImage*)GetWidgetFromName(TEXT("Image_Background_4"));
	Image_Background_5 = (UImage*)GetWidgetFromName(TEXT("Image_Background_5"));
	Image_Background_6 = (UImage*)GetWidgetFromName(TEXT("Image_Background_6"));
	Image_Background_7 = (UImage*)GetWidgetFromName(TEXT("Image_Background_7"));
	Image_Background_8 = (UImage*)GetWidgetFromName(TEXT("Image_Background_8"));
	Image_Background_9 = (UImage*)GetWidgetFromName(TEXT("Image_Background_9"));
	Image_Background_10 = (UImage*)GetWidgetFromName(TEXT("Image_Background_10"));
	Image_Background_11 = (UImage*)GetWidgetFromName(TEXT("Image_Background_11"));
	Image_Background_12 = (UImage*)GetWidgetFromName(TEXT("Image_Background_12"));
	Image_Background_13 = (UImage*)GetWidgetFromName(TEXT("Image_Background_13"));

	Image_CheckBox = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox"));
	Image_CheckBox_1 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_1"));
	Image_CheckBox_2 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_2"));
	Image_CheckBox_3 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_3"));
	Image_CheckBox_4 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_4"));
	Image_CheckBox_5 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_5"));
	Image_CheckBox_6 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_6"));
	Image_CheckBox_7 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_7"));
	Image_CheckBox_8 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_8"));
	Image_CheckBox_9 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_9"));
	Image_CheckBox_10 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_10"));
	Image_CheckBox_11 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_11"));
	Image_CheckBox_12 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_12"));
	Image_CheckBox_13 = (UImage*)GetWidgetFromName(TEXT("Image_CheckBox_13"));

	Image_Energy = (UImage*)GetWidgetFromName(TEXT("Image_Energy"));
	Image_Energy_1 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_1"));
	Image_Energy_2 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_2"));
	Image_Energy_3 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_3"));
	Image_Energy_4 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_4"));
	Image_Energy_5 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_5"));
	Image_Energy_6 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_6"));
	Image_Energy_7 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_7"));
	Image_Energy_8 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_8"));
	Image_Energy_9 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_9"));
	Image_Energy_10 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_10"));
	Image_Energy_11 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_11"));
	Image_Energy_12 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_12"));
	Image_Energy_13 = (UImage*)GetWidgetFromName(TEXT("Image_Energy_13"));

	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
	Image_Icon_1 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_1"));
	Image_Icon_2 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_2"));
	Image_Icon_3 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_3"));
	Image_Icon_4 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_4"));
	Image_Icon_5 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_5"));
	Image_Icon_6 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_6"));
	Image_Icon_7 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_7"));
	Image_Icon_8 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_8"));
	Image_Icon_9 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_9"));
	Image_Icon_10 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_10"));
	Image_Icon_11 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_11"));
	Image_Icon_12 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_12"));
	Image_Icon_13 = (UImage*)GetWidgetFromName(TEXT("Image_Icon_13"));

	Image_IconBackground = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground"));
	Image_IconBackground_1 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_1"));
	Image_IconBackground_2 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_2"));
	Image_IconBackground_3 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_3"));
	Image_IconBackground_4 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_4"));
	Image_IconBackground_5 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_5"));
	Image_IconBackground_6 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_6"));
	Image_IconBackground_7 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_7"));
	Image_IconBackground_8 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_8"));
	Image_IconBackground_9 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_9"));
	Image_IconBackground_10 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_10"));
	Image_IconBackground_11 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_11"));
	Image_IconBackground_12 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_12"));
	Image_IconBackground_13 = (UImage*)GetWidgetFromName(TEXT("Image_IconBackground_13"));

	Image_Stance = (UImage*)GetWidgetFromName(TEXT("Image_Stance"));
	Image_Stance_1 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_1"));
	Image_Stance_2 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_2"));
	Image_Stance_3 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_3"));
	Image_Stance_4 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_4"));
	Image_Stance_5 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_5"));
	Image_Stance_6 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_6"));
	Image_Stance_7 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_7"));
	Image_Stance_8 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_8"));
	Image_Stance_9 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_9"));
	Image_Stance_10 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_10"));
	Image_Stance_11 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_11"));
	Image_Stance_12 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_12"));
	Image_Stance_13 = (UImage*)GetWidgetFromName(TEXT("Image_Stance_13"));

	TextBlock_Sec = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec"));
	TextBlock_Sec_1 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_1"));
	TextBlock_Sec_2 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_2"));
	TextBlock_Sec_3 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_3"));
	TextBlock_Sec_4 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_4"));
	TextBlock_Sec_5 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_5"));
	TextBlock_Sec_6 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_6"));
	TextBlock_Sec_7 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_7"));
	TextBlock_Sec_8 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_8"));
	TextBlock_Sec_9 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_9"));
	TextBlock_Sec_10 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_10"));
	TextBlock_Sec_11 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_11"));
	TextBlock_Sec_12 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_12"));
	TextBlock_Sec_13 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Sec_13"));

	TextBlock_SkillName = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName"));
	TextBlock_SkillName_1 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_1"));
	TextBlock_SkillName_2 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_2"));
	TextBlock_SkillName_3 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_3"));
	TextBlock_SkillName_4 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_4"));
	TextBlock_SkillName_5 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_5"));
	TextBlock_SkillName_6 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_6"));
	TextBlock_SkillName_7 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_7"));
	TextBlock_SkillName_8 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_8"));
	TextBlock_SkillName_9 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_9"));
	TextBlock_SkillName_10 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_10"));
	TextBlock_SkillName_11 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_11"));
	TextBlock_SkillName_12 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_12"));
	TextBlock_SkillName_13 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SkillName_13"));

	TextBlock_StanceText = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText"));
	TextBlock_StanceText_1 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_1"));
	TextBlock_StanceText_2 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_2"));
	TextBlock_StanceText_3 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_3"));
	TextBlock_StanceText_4 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_4"));
	TextBlock_StanceText_5 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_5"));
	TextBlock_StanceText_6 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_6"));
	TextBlock_StanceText_7 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_7"));
	TextBlock_StanceText_8 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_8"));
	TextBlock_StanceText_9 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_9"));
	TextBlock_StanceText_10 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_10"));
	TextBlock_StanceText_11 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_11"));
	TextBlock_StanceText_12 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_12"));
	TextBlock_StanceText_13 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_StanceText_13"));

	TextBlock_EnergyText = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText"));
	TextBlock_EnergyText_1 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_1"));
	TextBlock_EnergyText_2 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_2"));
	TextBlock_EnergyText_3 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_3"));
	TextBlock_EnergyText_4 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_4"));
	TextBlock_EnergyText_5 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_5"));
	TextBlock_EnergyText_6 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_6"));
	TextBlock_EnergyText_7 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_7"));
	TextBlock_EnergyText_8 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_8"));
	TextBlock_EnergyText_9 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_9"));
	TextBlock_EnergyText_10 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_10"));
	TextBlock_EnergyText_11 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_11"));
	TextBlock_EnergyText_12 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_12"));
	TextBlock_EnergyText_13 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_EnergyText_13"));

	TextBlock_SecText = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText"));
	TextBlock_SecText_1 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_1"));
	TextBlock_SecText_2 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_2"));
	TextBlock_SecText_3 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_3"));
	TextBlock_SecText_4 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_4"));
	TextBlock_SecText_5 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_5"));
	TextBlock_SecText_6 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_6"));
	TextBlock_SecText_7 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_7"));
	TextBlock_SecText_8 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_8"));
	TextBlock_SecText_9 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_9"));
	TextBlock_SecText_10 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_10"));
	TextBlock_SecText_11 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_11"));
	TextBlock_SecText_12 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_12"));
	TextBlock_SecText_13 = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_SecText_13"));
}