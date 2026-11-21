// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_MouseTracker.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CONDUCTOR_API UCPP_MouseTracker : public UActorComponent
{
	GENERATED_BODY()

public:
	// BPからMouseDeltaを参照渡しで受け取り、値を更新する
	UFUNCTION(BlueprintCallable, Category = "Mouse")
	void UpdateMouseAndPlaneNormal(FVector& OutPlaneNormal , FVector2D& MouseDelta);

private:
	FVector2D PrevMousePos;
	FVector PlaneNormal;
};
