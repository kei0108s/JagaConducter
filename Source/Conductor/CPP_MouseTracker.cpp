// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MouseTracker.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/PlayerController.h"

void UCPP_MouseTracker::UpdateMouseAndPlaneNormal(FVector& OutPlaneNormal , FVector2D& MouseDelta)
{
	// プレイヤーコントローラー取得
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		PlaneNormal = FVector::ZeroVector;
		return;
	}


	// マウス位置取得
	float MouseX, MouseY;
	if (!UWidgetLayoutLibrary::GetMousePositionScaledByDPI(PC, MouseX, MouseY))
	{
		PlaneNormal = FVector::ZeroVector;
		return;
	}

	FVector2D CurrentPos(MouseX, MouseY);
	MouseDelta = CurrentPos - PrevMousePos;
	PrevMousePos = CurrentPos;

	// Actor のベクトル取得
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		PlaneNormal = FVector::ZeroVector;
		return;
	}

	FVector RightVec = Owner->GetActorRightVector();
	FVector UpVec = Owner->GetActorUpVector();

	// PlaneNormal 計算
	OutPlaneNormal = RightVec * MouseDelta.Y + UpVec * MouseDelta.X;
}