// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithTrig.h"
#include "Components\BoxComponent.h"
#include "Components\StaticMeshComponent.h"

// Sets default values
AActorWithTrig::AActorWithTrig()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->AttachTo(GetRootComponent());
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	StaticMesh->AttachTo(GetRootComponent());
}

// Called when the game starts or when spawned
void AActorWithTrig::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AActorWithTrig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

