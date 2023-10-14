// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DreamFragmentWidget.h"

#include "ItemCardWidget.h"

UDreamFragmentWidget::UDreamFragmentWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	FString ItemTablePath = TEXT("/Game/Assets/DataTable/ItemTable.ItemTable");
	FString SkillBuffStringTablePath = TEXT("/Game/Assets/DataTable/SkillBuffStringTable.SkillBuffStringTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMTABLE(*ItemTablePath);
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILLBUFFSTRINGTABLE(*SkillBuffStringTablePath);
	ItemTable = DT_ITEMTABLE.Object;
	SkillBuffStringTable = DT_SKILLBUFFSTRINGTABLE.Object;
	SkillDescriptionComponent = CreateDefaultSubobject<USkillDescriptionComponent>(TEXT("SkillDescriptionComponent"));
}

void UDreamFragmentWidget::NativePreConstruct() {
	Super::NativePreConstruct();

	Button_Cancel = (UButton*)GetWidgetFromName(TEXT("Button_Cancel"));
	Button_Select = (UButton*)GetWidgetFromName(TEXT("Button_Select"));
	GridPanel = (UGridPanel*)GetWidgetFromName(TEXT("GridPanel"));
}

void UDreamFragmentWidget::NativeConstruct() {
	Super::NativeConstruct();

	ItemTable->GetAllRows<FItemData>("GetAllRows", ItemTableRows);
	SkillBuffStringTable->GetAllRows<FDialogueString>("GetAllRows", SkillBuffStringTableRows);
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));

	for (int i = 0; i < 3; i++) {
		if (ItemCardFormClass) {
			ItemCardFormRef = CreateWidget<UItemCardWidget>(GetWorld(), ItemCardFormClass);
			if (ItemCardFormRef) {
				ItemCardArr.Add(ItemCardFormRef);
				GridPanel->AddChildToGrid(ItemCardFormRef, 0, i);
			}
		}
	}

	RndItemRowNumArr.Empty();
	PickRandomItem();
	SetItemCardUI();
}

void UDreamFragmentWidget::PickRandomItem() {
	bool NotSatisfiedConditon = false;
	int RndItemRowNum = rand() % 6;

	if (KNOCKturneGameState->ItemCountList[RndItemRowNum] < ItemTableRows[RndItemRowNum]->MaxCount) {
		for (int i = 0; i < RndItemRowNumArr.Num(); i++) {
			if (RndItemRowNum == RndItemRowNumArr[i]) {
				PickRandomItem();
				break;
			}
		}
	}
	else {
		PickRandomItem();
	}

	RndItemRowNumArr.Add(RndItemRowNum);

	if (RndItemRowNumArr.Num() < 3) {
		PickRandomItem();
	}
}

void UDreamFragmentWidget::SetItemCardUI() {
	for (int i = 0; i < 3; i++) {
		UTexture2D* icon = ItemTableRows[RndItemRowNumArr[i]]->ItemIcon;
		ItemCardArr[i]->Image_Icon->SetBrushFromTexture(icon);

		FString rowname = ItemTable->GetRowNames()[RndItemRowNumArr[i]].ToString().Append("_String");
		FString name = SkillBuffStringTable->FindRow<FDialogueString>(FName(*rowname), TEXT(""))->KOR;
		ItemCardArr[i]->TextBlock_Name->SetText(FText::FromString(name));

		FString description = SkillDescriptionComponent->ItemRedefineDescription(RndItemRowNumArr[i]);
		ItemCardArr[i]->RichTextBlock_Description->SetText(FText::FromString(description));

		FString easteregg = SkillBuffStringTable->FindRow<FDialogueString>(FName(*ItemTableRows[RndItemRowNumArr[i]]->ItemEasterEgg), TEXT(""))->KOR;
		ItemCardArr[i]->TextBlock_Easteregg->SetText(FText::FromString(easteregg));

		FString eastereggcharacter;
		if (ItemTableRows[RndItemRowNumArr[i]]->ItemEasterEgg_Character != "-1") {
			eastereggcharacter = SkillBuffStringTable->FindRow<FDialogueString>(FName(*ItemTableRows[RndItemRowNumArr[i]]->ItemEasterEgg_Character), TEXT(""))->KOR;
		}
		else {
			eastereggcharacter = "";
		}
		ItemCardArr[i]->RichTextBlock_EastereggCharacter->SetText(FText::FromString(eastereggcharacter));
	}
}