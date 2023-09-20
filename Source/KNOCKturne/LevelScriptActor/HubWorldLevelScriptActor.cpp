// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"
#include "Engine/GameInstance.h"
#include "Actor/Peppy.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	PrologueDialogueComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("DialogueMananger"));
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
	PeppyController = (APeppyController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(this, 0));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHubWorldLevelScriptActor::StaticClass(), HubworldActors);
	/*for (int i = 0; i < HubworldActors.Num(); ++i)
	{
		DreamMActor = dynamic_cast<ADreamM*>(HubworldActors[i]);
		RabbitActor = dynamic_cast<ARabbit*>(HubworldActors[i]);
	}

	if (DreamMActor != nullptr) {
		NTLOG(Warning, TEXT("found"));
		DreamMActor->SetActorRotation(FRotator(0.0, 0.0, -70.0));
	}
	else {
		NTLOG(Warning, TEXT("not found"));
	}*/
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	DialogueTableComponent->LoadDialogueTable("Dialogue_Npc");
	//PrologueDialogueComponent->LoadDialogueTable("Dialogue_Prologue");

	// StartLevelByCondition();
}

void AHubWorldLevelScriptActor::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (PeppyController != nullptr) {
		if (PeppyController->WasInputKeyJustPressed(EKeys::Escape)) {
			EscKeyEvent();
		}
	}
}

void AHubWorldLevelScriptActor::StartPrologueDialogue() {
	PeppyController->PrologueInProcess = true;
	PrologueDialogueComponent->ResetDialogueRowPointer();

	if (DialogueWidgetClass) {
		DialogueWidgetRef = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (DialogueWidgetRef) {
			DialogueWidgetRef->AddToViewport();
		}
		else {
			NTLOG(Warning, TEXT("BP_Dialogue widget creating is failed!"));
		}
	}

	DialogueWidgetRef->TextBlock_E->SetVisibility(ESlateVisibility::Visible);

	DialogueWidgetRef->GetNextDialogueLine(PrologueDialogueComponent);
}

bool AHubWorldLevelScriptActor::MoveDirectionTF(FDialogueData DataTable) {
	if (DataTable.Direction.Contains("DT")) {
		return true;
	}
	else if (DataTable.Direction.Contains("DF")) {
		return false;
	}
	else {
		return NULL;
	}
}

void AHubWorldLevelScriptActor::StorePrevCameraRotation() {
	PrevCameraRotation = Peppy->Camera->GetComponentRotation();
}

void AHubWorldLevelScriptActor::StorePrevCameraLocation() {
	PrevCameraLocation = Peppy->Camera->GetComponentLocation();
}

void AHubWorldLevelScriptActor::StorePrevCameraTransform() {
	StorePrevCameraLocation();
	StorePrevCameraRotation();
}

void AHubWorldLevelScriptActor::PrologueDirection(FDialogueData DataTable) {
	if (DataTable.Direction.Contains("none")) {
		CallMoveDirection(DataTable);
	}
	else if (DataTable.Direction.Contains("before")) {
		BlackScreenOff();
		CallMoveDirection(DataTable);
	}
	else if (DataTable.Direction.Contains("after")) {
		CallMoveDirection(DataTable);
		BlackScreenOn();
	}
	else if (DataTable.Direction.Contains("both")) {
		BlackScreenOff();
		CallMoveDirection(DataTable);
		BlackScreenOn();
	}
}

void AHubWorldLevelScriptActor::CallMoveDirection(FDialogueData DataTable) {
	bool isDirectionExist = MoveDirectionTF(DataTable);

	if (isDirectionExist) {
		MoveDirection();
		MDSelection++;
	}
	else {
		DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
		DialogueWidgetRef->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHubWorldLevelScriptActor::NextIsDirection(FDialogueData DataTable) {
	if (DataTable.Direction == "-1") {
		DialogueWidgetRef->isDirection = false;
	}
	else {
		DialogueWidgetRef->isDirection = true;
	}
}

void AHubWorldLevelScriptActor::AfterPrologueDirection() {
	DialogueWidgetRef->isCameraMoving = false;
	DialogueWidgetRef->RichTextBlock_Dialogue->SetText(FText::FromString(""));
	DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
	DialogueWidgetRef->SetVisibility(ESlateVisibility::Visible);
}

void AHubWorldLevelScriptActor::SetPeppyHiddenOrNot() {
	if (isPrologue) {
		if (KNOCKturneGameState->isBattleFail) {
			Peppy->SetActorHiddenInGame(true);
		}
		else {
			Peppy->SetActorHiddenInGame(false);
		}
	}
	else {
		Peppy->SetActorHiddenInGame(true);
	}
}

void AHubWorldLevelScriptActor::BattleFailDialogueAllEnded() {
	DialogueWidgetRef->RemoveFromParent();

	if (KNOCKturneGameState->isDreamDiaryUpdated) {
		KNOCKturneGameState->isDreamDiaryUpdated = false;
	}
	if (KNOCKturneGameState->GetDreamFragment) {
		KNOCKturneGameState->GetDreamFragment = false;
	}
	Peppy->Camera->SetWorldTransform(OriginalCameraTransform);
	Peppy->SetActorHiddenInGame(false);
}

void AHubWorldLevelScriptActor::CreateHubworldHUD() {
	if (HubworldHUDClass) {
		HubworldHUDRef = CreateWidget<UHubworldHUDWidget>(GetWorld(), HubworldHUDClass);
		if (HubworldHUDRef) {
			HubworldHUDRef->AddToViewport();
		}
	}

	if (KNOCKturneGameState->isDreamDiaryUpdated) {
		HubworldHUDRef->Image_DreamDiary_Updated->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		HubworldHUDRef->Image_DreamDiary_Updated->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHubWorldLevelScriptActor::PrologueEnded() {
	isPrologue = true;
	PeppyController->PrologueInProcess = false;
	DialogueWidgetRef->TextSpeed = 0.0;
	DialogueWidgetRef->RemoveFromParent();

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
		LevelSequencePlayer->PlayReverse();
	}
	else
	{
		NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
	}

	Delay(2.0);

	if (!isSkip) {
		if (LevelSequencePlayer)
		{
			LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Hubworld_Cabin, FMovieSceneSequencePlaybackSettings(), SequenceActor);
			LevelSequencePlayer->Play();
		}
		else
		{
			NTLOG(Warning, TEXT("Unable to create Hubworld_Cabin level sequence player!"));
		}

		Delay(7.0);
		SetState("Loading", "OnLoading");
	}

	if (LoadingWidgetClass) {
		LoadingWidgetRef = CreateWidget<ULoadingWidget>(GetWorld(), LoadingWidgetClass);
		if (LoadingWidgetRef) {
			LoadingWidgetRef->AddToViewport();
		}
		else {
			NTLOG(Warning, TEXT("LoadingWidget creating is failed!"));
		}
	}

	LoadingWidgetRef->LoadingText = DialogueTableComponent->RandomLoadingText();
	Delay(4.0);
	SetState("Loading", "None");
	DefaultLocation();
	LoadingWidgetRef->RemoveFromParent();

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
		LevelSequencePlayer->PlayReverse();
	}
	else
	{
		NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
	}

	Delay(2.0);
	isSkip = false;
}

void AHubWorldLevelScriptActor::DefaultLocation() {
	Peppy->SetActorTransform(OriginalPeppyTransform);
	Peppy->Camera->SetWorldTransform(OriginalCameraTransform);
	RabbitActor->SetActorTransform(OriginalRabbitTransform);
	Peppy->SetActorHiddenInGame(false);
	DreamMActor->SetActorLocation(OriginalDreamMLocation);
	DreamMActor->SetActorRotation(FRotator(0.0, 0.0, 100.0));
	DreamMActor->SetActorHiddenInGame(false);
}

void AHubWorldLevelScriptActor::EscKeyEvent() {
	if (BP_EscClass) {
		BP_EscRef = CreateWidget<UUserWidget>(GetWorld(), BP_EscClass);
		if (BP_EscRef) {
			BP_EscRef->AddToViewport();
		}
		else {
			NTLOG(Warning, TEXT("BP_Esc widget creating is failed!"));
		}
	}
}

void AHubWorldLevelScriptActor::StartLevelByCondition() {
	if (isPrologue) {
		if (KNOCKturneGameState->RightafterBattleClear) {
			if (BP_BlackClass) {
				BP_BlackRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlackClass);
				if (BP_BlackRef) {
					BP_BlackRef->AddToViewport();
				}
				else {
					NTLOG(Warning, TEXT("BP_Black widget creating is failed!"));
				}
			}

			Delay(1.5);
			BP_BlackRef->RemoveFromParent();
			Peppy->SetActorLocation(FVector(1233.0, 843.0, 146.0));

			if (LevelSequencePlayer)
			{
				LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
				LevelSequencePlayer->Play();
			}
			else
			{
				NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
			}

			Delay(2.0);
			CreateHubworldHUD();
		}
		else if (KNOCKturneGameState->isBattleFail) {
			if (BP_BlackClass) {
				BP_BlackRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlackClass);
				if (BP_BlackRef) {
					BP_BlackRef->AddToViewport();
				}
				else {
					NTLOG(Warning, TEXT("BP_Black widget creating is failed!"));
				}
			}

			Delay(2.0);
			UWidgetLayoutLibrary::RemoveAllWidgets(this);
			OriginalCameraTransform = Peppy->Camera->GetComponentTransform();
			Peppy->Camera->SetWorldLocationAndRotation(FVector(883.0, 1083.0, 146.0), FRotator(0.0, 0.0, -30.0));

			if (BP_BlinkClass) {
				BP_BlinkRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlinkClass);
				if (BP_BlinkRef) {
					BP_BlinkRef->AddToViewport();
				}
				else {
					NTLOG(Warning, TEXT("BP_Blink widget creating is failed!"));
				}
			}

			Delay(3.44);
			UWidgetLayoutLibrary::RemoveAllWidgets(this);
			CreateHubworldHUD();
			BattleFailDialogueWithEventBinding();
		}
		else {
			if (LoadingWidgetClass) {
				LoadingWidgetRef = CreateWidget<ULoadingWidget>(GetWorld(), LoadingWidgetClass);
				if (LoadingWidgetRef) {
					LoadingWidgetRef->AddToViewport();
				}
				else {
					NTLOG(Warning, TEXT("LoadingWidget creating is failed!"));
				}
			}

			LoadingWidgetRef->LoadingText = DialogueTableComponent->RandomLoadingText();
			Delay(0.2);
			UWidgetLayoutLibrary::RemoveAllWidgets(this);

			if (LevelSequencePlayer)
			{
				LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
				LevelSequencePlayer->Play();
			}
			else
			{
				NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
			}

			CreateHubworldHUD();
		}
	}
	else {
		if (BP_BlackClass) {
			BP_BlackRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlackClass);
			if (BP_BlackRef) {
				BP_BlackRef->AddToViewport();
			}
			else {
				NTLOG(Warning, TEXT("BP_Black widget creating is failed!"));
			}
		}

		Delay(2.0);
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		OriginalPeppyTransform = Peppy->GetActorTransform();
		OriginalCameraTransform = Peppy->Camera->GetComponentTransform();
		OriginalRabbitTransform = RabbitActor->GetActorTransform();
		OriginalDreamMLocation = DreamMActor->GetActorLocation();
		Peppy->Camera->SetWorldLocationAndRotation(FVector(883.0, 1083.0, 146.0), FRotator(0.0, -90.0, -30.0));

		if (BP_BlinkClass) {
			BP_BlinkRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlinkClass);
			if (BP_BlinkRef) {
				BP_BlinkRef->AddToViewport();
			}
			else {
				NTLOG(Warning, TEXT("BP_Blink widget creating is failed!"));
			}
		}

		Delay(3.44);
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		StartPrologueDialogue();
		CreateHubworldHUD();
	}


	BindNpcTalk();
	SetPeppyHiddenOrNot();
}

void AHubWorldLevelScriptActor::BattleFailDialogue() {
	if (DialogueWidgetClass) {
		DialogueWidgetRef = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (DialogueWidgetRef) {
			DialogueWidgetRef->AddToViewport();
		}
		else {
			NTLOG(Warning, TEXT("BP_Dialogue widget creating is failed!"));
		}
	}

	DialogueTableComponent->SetDialogueIndexByGroupCode("EP1_AfterBattle");
	DialogueWidgetRef->GetNextDialogueLine(DialogueTableComponent);
}

void AHubWorldLevelScriptActor::AfterBattleFailDirection(FDialogueData DialogueData) {
	if (DialogueData.Direction == "AfterBattleFail_Hubworld_DreamDiary and DreamFragment") {
		if (KNOCKturneGameState->isDreamDiaryUpdated) {
			DialogueTableComponent->SetBattleFailDiaryDialogueIndex();
			DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
		}
		else if(KNOCKturneGameState->GetDreamFragment){
			DialogueTableComponent->SetDialogueIndexByGroupCode("AfterBattleFail_Hubworld_DreamFragment");
			DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
		}
		else {
			BattleFailDialogueAllEnded();
		}
	}
	else if (DialogueData.Direction == "AfterBattleFail_Hubworld_DreamFragment") {
		if (KNOCKturneGameState->GetDreamFragment) {
			DialogueTableComponent->SetDialogueIndexByGroupCode("AfterBattleFail_Hubworld_DreamFragment");
			DialogueWidgetRef->NextTalk(PrologueDialogueComponent);
		}
		else {
			BattleFailDialogueAllEnded();
		}
	}
}

void AHubWorldLevelScriptActor::RandomTalk() {
	DialogueTableComponent->SetIsEndedDialogueRows(false);

	if (DialogueWidgetRef == nullptr) {
		if (DialogueWidgetClass) {
			DialogueWidgetRef = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
			if (DialogueWidgetRef) {
				DialogueWidgetRef->AddToViewport();
			}
			else {
				NTLOG(Warning, TEXT("BP_Dialogue widget creating is failed!"));
			}
		}
	}

	DialogueWidgetRef->RichTextBlock_Dialogue->SetVisibility(ESlateVisibility::Visible);
	DialogueTableComponent->SetRandomTalkIndex(Peppy->InteractingNpcActor, Peppy->InteractingNpcGroupcode);
	DialogueWidgetRef->GetNextDialogueLine(DialogueTableComponent);
}

void AHubWorldLevelScriptActor::AfterBattleFailHubworldDialogueEnded() {
	if (DialogueWidgetRef->isDirection) {
		AfterBattleFailDirection(DialogueWidgetRef->DialogueDataStructure);
	}
	else {
		BattleFailDialogueAllEnded();
	}
}

void AHubWorldLevelScriptActor::TalkWithNpcEnded() {
	DialogueWidgetRef->RemoveFromParent();
	DialogueTableComponent->EmptyTArray();
	Delay(0.5);
	Peppy->ReturnCameraInInteraction();
}

void AHubWorldLevelScriptActor::StartDreamFragmentDialogue() {
	DialogueTableComponent->SetIsEndedDialogueRows(false);
	DialogueWidgetRef->RichTextBlock_Dialogue->SetVisibility(ESlateVisibility::Visible);
	DialogueTableComponent->SetDialogueIndexByGroupCode("DreamFragment");
	DialogueWidgetRef->GetNextDialogueLine(DialogueTableComponent);
}

void AHubWorldLevelScriptActor::DreamMDirectionTrue() {
	DialogueWidgetRef->isCameraMoving = true;

	if (BP_DreamFragmentRef == nullptr) {
		if (BP_DreamFragmentClass) {
			BP_DreamFragmentRef = CreateWidget<UUserWidget>(GetWorld(), BP_DreamFragmentClass);
			if (BP_DreamFragmentRef) {
				BP_DreamFragmentRef->AddToViewport();
			}
			else {
				NTLOG(Warning, TEXT("BP_DreamFragment creating is failed!"));
			}
		}
	}
}

void AHubWorldLevelScriptActor::StartAfterBattleDialogue() {
	DialogueWidgetRef->RichTextBlock_Dialogue->SetVisibility(ESlateVisibility::Visible);
	DialogueTableComponent->SetDialogueIndexByGroupCode("EP1_AfterBattle_Hubworld");
	DialogueWidgetRef->GetNextDialogueLine(DialogueTableComponent);
}

void AHubWorldLevelScriptActor::AfterBattleDialogueEnded() {
	TalkWithNpcEnded();
	KNOCKturneGameState->RightafterBattleClear = false;
}
