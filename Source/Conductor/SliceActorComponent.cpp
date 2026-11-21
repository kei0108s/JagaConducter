// Fill out your copyright notice in the Description page of Project Settings.


#include "SliceActorComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values for this component's properties
USliceActorComponent::USliceActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USliceActorComponent::BeginPlay()
{
	Super::BeginPlay();

    // ProceduralMeshを生成してStaticMeshの内容をコピー
    ProceduralMeshComp = NewObject<UProceduralMeshComponent>(GetOwner());
    ProceduralMeshComp->RegisterComponent();
    ProceduralMeshComp->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

    UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(
        StaticMeshComp,
        0,
        ProceduralMeshComp,
        true
    );

    // StaticMeshは非表示にする
    StaticMeshComp->SetVisibility(false);
    StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 物理有効
    ProceduralMeshComp->SetSimulatePhysics(true);
    ProceduralMeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));
	
}

void USliceActorComponent::SliceMesh(const FVector& PlanePosition, const FVector& PlaneNormal)
{
    if (!ProceduralMeshComp) return;

    UProceduralMeshComponent* NewProcMesh = NewObject<UProceduralMeshComponent>(GetOwner());
    NewProcMesh->RegisterComponent();
    NewProcMesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

    UKismetProceduralMeshLibrary::SliceProceduralMesh(
        ProceduralMeshComp,
        PlanePosition,
        PlaneNormal,
        true,
        NewProcMesh,
        EProcMeshSliceCapOption::CreateNewSectionForCap,
        nullptr
    );

    ProceduralMeshComp->SetSimulatePhysics(true);
    NewProcMesh->SetSimulatePhysics(true);
}