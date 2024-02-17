// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BuffIconFormWidget.h"
#include <Kismet/GameplayStatics.h>
#include "GameInstance/ActorManagerSystem.h"
#include <GameInstance/DialogueManagerSystem.h>
#include "Components/Image.h"

void UBuffIconFormWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CanvasPanel = (UCanvasPanel*)GetWidgetFromName(TEXT("CanvasPanel"));
	Button_Background = (UButton*)GetWidgetFromName(TEXT("Button_Background"));
	Image_Background = (UImage*)GetWidgetFromName(TEXT("Image_Background"));
	Image_Icon = (UImage*)GetWidgetFromName(TEXT("Image_Icon"));
}

void UBuffIconFormWidget::NativeConstruct()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BattleTableManagerSystem = GameInstance->GetSubsystem<UBattleTableManagerSystem>();
	ActorManagerSystem = GameInstance->GetSubsystem<UActorManagerSystem>();
}

FString UBuffIconFormWidget::GetSkillIndexByKeyword(EBuffType BuffType, FString Num)
{
	FBuffData BuffData = ActorManagerSystem->PeppyActor->BuffComponent->GetBuffData(BuffType);

	switch (FCString::Atoi(*Num)) {
	case 0:
		return FString::FromInt(BuffData.Value_N);
	case 1:
		return FString::FromInt(BuffData.Value_M);
	case 2:
		return FString::FromInt(BuffData.Value_T);
	default:
		return "None";
	}
}

FString UBuffIconFormWidget::RedefineDescription(int RowNum)
{
	FString rowname = ActorManagerSystem->PeppyActor->BuffComponent->BuffTableRows[RowNum]->BuffDescript;
	FString OriginalStr = BattleTableManagerSystem->SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
	FString Redefined = OriginalStr;
	int32 StartIdx = 0;
	FString tmp1 = "";
	FString skillindex = "";
	FString tmp2 = "";
	EBuffType BuffType = ActorManagerSystem->PeppyActor->BuffComponent->BuffIconNameToBuffTypeMap[Image_Icon->Brush.GetResourceName().ToString()];

	for (int idx = 0; idx < Redefined.Len(); idx++) {
		if (Redefined[idx] == '{') {
			if (Redefined[idx + 2] == '}') {
				tmp1 = Redefined.Mid(0, idx + 1);
				skillindex = GetSkillIndexByKeyword(BuffType, Redefined.Mid(idx + 1, 1));
				tmp2 = Redefined.Mid(idx + 2, Redefined.Len() - (idx + 2));
			}
			else {
				tmp1 = Redefined.Mid(0, idx + 2);
				skillindex = GetSkillIndexByKeyword(BuffType, Redefined.Mid(idx + 2, 1));
				tmp2 = Redefined.Mid(idx + 3, Redefined.Len() - (idx + 3));
			}

			Redefined = (tmp1.Append(skillindex)).Append(tmp2);
		}
	}

	int count = -1;
	for (int index = 0; index < Redefined.Len(); index++) {
		if (Redefined[index] == '{' || Redefined[index] == '}') {
			count++;
			Redefined.RemoveAt(index, 1);
		}
	}

	return Redefined;
}
