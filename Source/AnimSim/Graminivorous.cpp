// Fill out your copyright notice in the Description page of Project Settings.


#include "Graminivorous.h"
#include "Bot_Controller.h"
#include "Herb.h"
#include "Components\SphereComponent.h"
#include "TimerManager.h"


void AGraminivorous::BeginPlay()
{
	Super::BeginPlay();


	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AGraminivorous::OnBoxOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AGraminivorous::OnBoxEndOverlap);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("Decrement_Stats"), 1,1,1);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 1.f, true);
}


void AGraminivorous::OnBoxOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	BoxOverlapInChild(OtherActor);

}

void AGraminivorous::OnBoxEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AHerb* Overlapped_Herb = Cast<AHerb>(OtherActor);
	if (Overlapped_Herb)
	{
		HerbLocation.AddUnique(Overlapped_Herb->GetActorLocation());
	}
}


void AGraminivorous::Eat()
{
	Super::Eat();

	FVector Nearest_Point(0,0,0);
	float MaxDistance = 0;
	for (FVector Herb:HerbLocation)
	{
		if (MaxDistance > FVector::Distance(this->GetActorLocation(), Herb) || MaxDistance == 0)
		{
			MaxDistance = FVector::Distance(this->GetActorLocation(), Herb);
			Nearest_Point = Herb;
		}
		
	}
	BotController->MoveToLocation(Nearest_Point);
}

void AGraminivorous::Decrement_Stats(uint8 ModifierHunger, uint8 ModifierThrust, uint8 ModifierReproduction)
{
	Super::Decrement_Stats(ModifierHunger, ModifierThrust, ModifierReproduction);
}
