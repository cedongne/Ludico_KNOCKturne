// Fill out your copyright notice in the Description page of Project Settings.


#include "HubWorldLevelScriptActor.h"
#include "Engine/GameInstance.h"
#include "Actor/Peppy.h"

AHubWorldLevelScriptActor::AHubWorldLevelScriptActor() {
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
	PrologueDialogueTableComponent = CreateDefaultSubobject<UDialogueTableComponent>(TEXT("PrologueDialogueMananger"));

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AHubWorldLevelScriptActor::PreInitializeComponents() {
	Super::PreInitializeComponents();
}

void AHubWorldLevelScriptActor::PostInitializeComponents() {
	Super::PostInitializeComponents();
}

void AHubWorldLevelScriptActor::BeginPlay() {
	Super::BeginPlay();

	KNOCKturneGameState = Cast<AKNOCKturneGameState>(UGameplayStatics::GetGameState(GetWorld()));
	PeppyController = Cast<APeppyController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Peppy = Cast<APeppy>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	CommonDialogueTableComponent->LoadDialogueTable("Dialogue_Npc");
	PrologueDialogueTableComponent->LoadDialogueTable("Dialogue_Prologue");

	StartLevelByCondition();
}

void AHubWorldLevelScriptActor::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (PeppyController != nullptr) {
		if (PeppyController->WasInputKeyJustPressed(EKeys::Escape)) {
			EscKeyEvent();
		}
		if (PeppyController->WasInputKeyJustPressed(EKeys::Q)) {
			NTLOG(Warning, TEXT("Q Pressed"));

			SkipPrologue();
		}
	}
}

void AHubWorldLevelScriptActor::StartPrologueDialogue() {
	PeppyController->PrologueInProcess = true;
	PrologueDialogueTableComponent->ResetDialogueRowPointer();

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
	DialogueWidgetRef->GetNextDialogueLine(PrologueDialogueTableComponent);
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
		DialogueWidgetRef->NextTalk(PrologueDialogueTableComponent);
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
	DialogueWidgetRef->NextTalk(PrologueDialogueTableComponent);
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

	if (DialogueWidgetRef) {
		DialogueWidgetRef->TextSpeed = 0.0;
		DialogueWidgetRef->RemoveFromParent();
	}

	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->PlayReverse();
	}
	else
	{
		NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
	}

	GetWorld()->GetTimerManager().SetTimer(LvSequenceTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			PrologueEndedAfterFadeOut();

			GetWorld()->GetTimerManager().ClearTimer(LvSequenceTimerHandle);
		}), 2, false);
}

void AHubWorldLevelScriptActor::DefaultLocation() {
	Peppy->SetActorTransform(OriginalPeppyTransform);
	Peppy->Camera->SetWorldTransform(OriginalCameraTransform);
	RabbitActor->SetActorTransform(OriginalRabbitTransform);
	Peppy->SetActorHiddenInGame(false);
	DreamMActor->SetActorTransform(OriginalDreamMTransform);
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

			GetWorld()->GetTimerManager().SetTimer(BlackWigetTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					BP_BlackRef->RemoveFromParent();

					GetWorld()->GetTimerManager().ClearTimer(BlackWigetTimerHandle);
				}), 1.5, false);
			
			Peppy->SetActorLocation(FVector(1233.0, 843.0, 146.0));

			LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
			if (LevelSequencePlayer)
			{
				LevelSequencePlayer->Play();
			}
			else
			{
				NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
			}

			FTimerHandle CreateHUDTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(CreateHUDTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					CreateHubworldHUD();


					GetWorld()->GetTimerManager().ClearTimer(CreateHUDTimerHandle);
				}), 2, false);
			
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

			GetWorld()->GetTimerManager().SetTimer(HubworldTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					UWidgetLayoutLibrary::RemoveAllWidgets(this);
					OriginalCameraTransform = Peppy->Camera->GetComponentTransform();
					//Peppy->Camera->SetWorldLocationAndRotation(FVector(883.0, 1083.0, 146.0), FRotator(0.0, 0.0, -30.0));
					Peppy->Camera->SetWorldLocationAndRotation(FVector(883.0, 1083.0, 146.0), FRotator(0.0, -30.0, 0.0));

					if (BP_BlinkClass) {
						BP_BlinkRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlinkClass);
						if (BP_BlinkRef) {
							BP_BlinkRef->AddToViewport();
						}
						else {
							NTLOG(Warning, TEXT("BP_Blink widget creating is failed!"));
						}
					}

					GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, FTimerDelegate::CreateLambda([&]()
						{
							UWidgetLayoutLibrary::RemoveAllWidgets(this);
							CreateHubworldHUD();
							BattleFailDialogueWithEventBinding();

							GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
						}), 3.44, false);

					GetWorld()->GetTimerManager().ClearTimer(HubworldTimerHandle);
				}), 2, false);
			
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

			LoadingWidgetRef->LoadingText = CommonDialogueTableComponent->RandomLoadingText();

			GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					UWidgetLayoutLibrary::RemoveAllWidgets(this);

					LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
					if (LevelSequencePlayer)
					{
						LevelSequencePlayer->Play();
					}
					else
					{
						NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
					}

					CreateHubworldHUD();

					GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle);
					//4초로 변경 필요
				}), 0.1, false);
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

		GetWorld()->GetTimerManager().SetTimer(BlackWigetTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				UWidgetLayoutLibrary::RemoveAllWidgets(this);
				OriginalPeppyTransform = Peppy->GetActorTransform();
				OriginalCameraTransform = Peppy->Camera->GetComponentTransform();
				OriginalRabbitTransform = RabbitActor->GetActorTransform();
				OriginalDreamMTransform = DreamMActor->GetActorTransform();

				//Peppy->Camera->SetWorldLocationAndRotation(FVector(883.0, 1083.0, 146.0), FRotator(0.0, -90.0, -30.0));
				Peppy->Camera->SetWorldLocationAndRotation(FVector(883.0, 1083.0, 146.0), FRotator(-120.0, -90.0, 0.0));

				if (BP_BlinkClass) {
					BP_BlinkRef = CreateWidget<UUserWidget>(GetWorld(), BP_BlinkClass);
					if (BP_BlinkRef) {
						BP_BlinkRef->AddToViewport();
					}
					else {
						NTLOG(Warning, TEXT("BP_Blink widget creating is failed!"));
					}
				}

				GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						UWidgetLayoutLibrary::RemoveAllWidgets(this);

						if (!isSkip) { // 대사 시작 전 스킵 시 프롤로그 시작X
							StartPrologueDialogueWithEventBinding();
						}
						CreateHubworldHUD();

						GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
					}), 3.44, false);

				GetWorld()->GetTimerManager().ClearTimer(BlackWigetTimerHandle);
			}), 2, false);

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

	CommonDialogueTableComponent->SetDialogueIndexByGroupCode("AfterBattleFail_Hubworld");
	DialogueWidgetRef->GetNextDialogueLine(CommonDialogueTableComponent);
}

void AHubWorldLevelScriptActor::AfterBattleFailDirection(FDialogueData DialogueData) {
	if (DialogueData.Direction == "AfterBattleFail_Hubworld_DreamDiary and DreamFragment") {
		if (KNOCKturneGameState->isDreamDiaryUpdated) {
			CommonDialogueTableComponent->SetDialogueIndexByGroupCode("AfterBattleFail_Hubworld_DreamDiary");
			DialogueWidgetRef->NextTalk(CommonDialogueTableComponent);
		}
		else if(KNOCKturneGameState->GetDreamFragment){
			CommonDialogueTableComponent->SetDialogueIndexByGroupCode("AfterBattleFail_Hubworld_DreamFragment");
			DialogueWidgetRef->NextTalk(CommonDialogueTableComponent);
		}
		else {
			BattleFailDialogueAllEnded();
		}
	}
	else if (DialogueData.Direction == "AfterBattleFail_Hubworld_DreamFragment") {
		if (KNOCKturneGameState->GetDreamFragment) {
			CommonDialogueTableComponent->SetDialogueIndexByGroupCode("AfterBattleFail_Hubworld_DreamFragment");
			DialogueWidgetRef->NextTalk(CommonDialogueTableComponent);
		}
		else {
			BattleFailDialogueAllEnded();
		}
	}
}

void AHubWorldLevelScriptActor::RandomTalk() {
	CommonDialogueTableComponent->SetIsEndedDialogueRows(false);

	if(DreamMActor->DialogueWidgetRef){
		DialogueWidgetRef = DreamMActor->DialogueWidgetRef;
	}
	if (DialogueWidgetRef == nullptr || DialogueWidgetRef->IsInViewport() == false) {
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
	if (Peppy->InteractingNpcActor && Peppy->InteractingNpcGroupcode != "") {
		CommonDialogueTableComponent->SetRandomTalkIndex(Peppy->InteractingNpcActor, Peppy->InteractingNpcGroupcode);
		DialogueWidgetRef->GetNextDialogueLine(CommonDialogueTableComponent);
	}
	else {
		NTLOG(Warning, TEXT("Peppy->InteractingNpcActor or Peppy->InteractingNpcGroupcode is Empty!"));
	}
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
	if (DreamMActor->DialogueWidgetRef) {
		DreamMActor->DialogueWidgetRef->RemoveFromParent();
	}
	if (DialogueWidgetRef) {
		DialogueWidgetRef->RemoveFromParent();
	}
	
	CommonDialogueTableComponent->EmptyStartRandomNpcTalkArr();
	Peppy->ReturnCameraInInteraction();
}

void AHubWorldLevelScriptActor::StartDreamFragmentDialogue() {
	DialogueWidgetRef = DreamMActor->DialogueWidgetRef;
	CommonDialogueTableComponent->SetIsEndedDialogueRows(false);
	DialogueWidgetRef->RichTextBlock_Dialogue->SetVisibility(ESlateVisibility::Visible);
	CommonDialogueTableComponent->SetDialogueIndexByGroupCode("DreamFragment");
	DialogueWidgetRef->GetNextDialogueLine(CommonDialogueTableComponent);
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
	CommonDialogueTableComponent->SetDialogueIndexByGroupCode("EP1_AfterBattle_Hubworld");
	DialogueWidgetRef->GetNextDialogueLine(CommonDialogueTableComponent);
}

void AHubWorldLevelScriptActor::AfterBattleDialogueEnded() {
	TalkWithNpcEnded();
	KNOCKturneGameState->RightafterBattleClear = false;
}

void AHubWorldLevelScriptActor::PrologueEndedAfterFadeOut() {
	if (!isSkip) {

		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Hubworld_Cabin, FMovieSceneSequencePlaybackSettings(), SequenceActor);
		if (LevelSequencePlayer)
		{
			LevelSequencePlayer->Play();
		}
		else
		{
			NTLOG(Warning, TEXT("Unable to create Hubworld_Cabin level sequence player!"));
		}

		GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				SetState("Loading", "OnLoading");
				StartLoadingAfterPrologue();

				GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle);
			}), 7, false);
	}
	else {
		StartLoadingAfterPrologue();
	}
}

void AHubWorldLevelScriptActor::StartLoadingAfterPrologue() {
	if (LoadingWidgetClass) {
		LoadingWidgetRef = CreateWidget<ULoadingWidget>(GetWorld(), LoadingWidgetClass);
		if (LoadingWidgetRef) {
			LoadingWidgetRef->AddToViewport();
		}
		else {
			NTLOG(Warning, TEXT("LoadingWidget creating is failed!"));
		}
	}

	LoadingWidgetRef->LoadingText = CommonDialogueTableComponent->RandomLoadingText();

	FTimerHandle LoadingTimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle2, FTimerDelegate::CreateLambda([&]()
		{
			SetState("Loading", "None");
			DefaultLocation();
			NTLOG(Warning, TEXT("%f, %f, %f"), OriginalPeppyTransform.GetLocation().X, OriginalPeppyTransform.GetLocation().Y, OriginalPeppyTransform.GetLocation().Z);
			NTLOG(Warning, TEXT("%f, %f, %f"), OriginalPeppyTransform.GetRotation().X, OriginalPeppyTransform.GetRotation().Y, OriginalPeppyTransform.GetRotation().Z);
			LoadingWidgetRef->RemoveFromParent();

			LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeIn, FMovieSceneSequencePlaybackSettings(), SequenceActor);
			if (LevelSequencePlayer)
			{
				LevelSequencePlayer->Play();
			}
			else
			{
				NTLOG(Warning, TEXT("Unable to create FadeIn level sequence player!"));
			}

			GetWorld()->GetTimerManager().SetTimer(LvSequenceTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					isSkip = false;

					GetWorld()->GetTimerManager().ClearTimer(LvSequenceTimerHandle);
				}), 2, false);

			GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle2);
		}), 4, false);
}

void AHubWorldLevelScriptActor::SkipPrologue() {
	if (isPrologue == false && isSkip == false) {
		PrologueDialogueTableComponent->SetIsEndedDialogueRows(true);
		isSkip = true;
		PrologueEnded();
	}
}