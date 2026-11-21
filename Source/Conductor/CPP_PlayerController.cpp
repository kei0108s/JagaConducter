// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "SliceActorComponent.h"

void ACPP_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // マウスイベントを有効化
    bShowMouseCursor = true;
}

void ACPP_PlayerController::BeginPlay()
{
    Super::BeginPlay();

}
