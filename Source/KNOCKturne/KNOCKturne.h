// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"


DECLARE_LOG_CATEGORY_EXTERN(KNOCKturne, Log, All);

#define NTLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define NTLOG_S(Verbosity) UE_LOG(KNOCKturne, Verbosity, TEXT("%s"), *NTLOG_CALLINFO)
#define NTLOG(Verbosity, Format, ...) UE_LOG(KNOCKturne, Verbosity, TEXT("%s %s"), *NTLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define NTCHECK(Expr, ...) {if(!(Expr)) { NTLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}