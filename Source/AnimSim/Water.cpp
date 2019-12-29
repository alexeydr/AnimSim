// Fill out your copyright notice in the Description page of Project Settings.


#include "Water.h"
#include "Engine\StaticMesh.h"
#include "Bot.h"
#include "Components\BoxComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AWater::AWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Asset(TEXT("StaticMesh'/Game/Meshes/Cube.Cube'"));
	UStaticMesh* Water = Asset.Object;
	StaticMesh->SetStaticMesh(Water);
}

// Called when the game starts or when spawned
void AWater::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AWater::OnBoxOverlap);
}

void AWater::OnBoxOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	ABot* CurrentBot = Cast<ABot>(OtherActor);
	if (CurrentBot)
	{
		if (CurrentBot->Current_Status == ENeeds::Drink)
		{
			CurrentBot->Thrust += 100;
			CurrentBot->Start_Action();
			this->Destroy();
		}
	}
}

// Called every frame
void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

