// Fill out your copyright notice in the Description page of Project Settings.


#include "Herb.h"
#include "TimerManager.h"
#include "Bot.h"
#include "Components\BoxComponent.h"
#include "Components\StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AHerb::AHerb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Asset(TEXT("StaticMesh'/Game/Foliage/KiteDemo/Environments/Foliage/Ferns/SM_Fern_01.SM_Fern_01'"));
	UStaticMesh* Foliage = Asset.Object;
	StaticMesh->SetStaticMesh(Foliage);
	StaticMesh->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
	BoxComp->SetBoxExtent(FVector(100, 100, 100));
}

// Called when the game starts or when spawned
void AHerb::BeginPlay()
{
	Super::BeginPlay();
	PlantGrowth();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AHerb::OnBoxOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AHerb::OnBoxEndOverlap);
}

void AHerb::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ArrBots.Add(Cast<ABot>(OtherActor));
	
	for (ABot* Bot : ArrBots)
	{
		if (Bot->Current_Status == ENeeds::Eat)
		{
			Bot->Hunger += Food;
			Bot->HerbLocation.Remove(this->GetActorLocation());
			Bot->Start_Action();
				
		}
	}
	
}

void AHerb::OnBoxEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	
	ABot* CurrentBot = Cast<ABot>(OtherActor);
	if (CurrentBot)
	{
		ArrBots.Remove(CurrentBot);
	}
	
}

// Called every frame
void AHerb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHerb::PlantGrowth()
{
	if (StaticMesh->RelativeScale3D.X < 1)
	{
		FTimerHandle TimerHandle;
		Food += 10;
		StaticMesh->SetRelativeScale3D(StaticMesh->RelativeScale3D + FVector(0.1,0.1,0.1));
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AHerb::PlantGrowth, 10.f, false);
	}
}

