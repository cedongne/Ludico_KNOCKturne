// Fill out your copyright notice in the Description page of Project Settings.


#include "PeppyController.h"

APeppyController::APeppyController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}