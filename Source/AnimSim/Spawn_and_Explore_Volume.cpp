// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn_and_Explore_Volume.h"
#include "Components\BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawn_and_Explore_Volume::ASpawn_and_Explore_Volume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("MeshComp"));
	RootComponent = BoxComp;
}

// Called when the game starts or when spawned
void ASpawn_and_Explore_Volume::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ASpawn_and_Explore_Volume::Select_Point()
{
	return UKismetMathLibrary::RandomPointInBoundingBox(BoxComp->Bounds.Origin, BoxComp->Bounds.BoxExtent);
}

// Called every frame
void ASpawn_and_Explore_Volume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

