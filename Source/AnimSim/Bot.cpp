// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot.h"
#include "Spawn_and_Explore_Volume.h"
#include "AIController.h"
#include "Water.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components\SphereComponent.h"

#define MinHunger 50.f
#define MinThrust 50.f
#define MinReproduction 10.f

// Sets default values
ABot::ABot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	SphereComp = CreateDefaultSubobject<USphereComponent>(FName("BoxComp"));
	SphereComp->AttachTo(GetRootComponent());
	SphereComp->SetSphereRadius(300);
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	this->AIControllerClass = AAIController::StaticClass();
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

	BotController = Cast<AAIController>(this->Controller);
	if (BotController)
	{
		Start_Action();
	}
	
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BotController)
	{
		if (BotController->GetMoveStatus() == EPathFollowingStatus::Idle && Current_Status != ENeeds::Reproduction)
		{
			Start_Action();
		}
	}

}

ENeeds ABot::CheckParam()
{
	ENeeds DesiredAction = ENeeds::Explore_Location;
	int MaxValue = -1;
	if (MaxValue<=Hunger && Hunger<=MinHunger)
	{
		if (HerbLocation.Num()> 0)
		{
			MaxValue = Hunger;
			DesiredAction = ENeeds::Eat;
		}
	}
	if(MaxValue <= Thrust && Thrust<=MinThrust)
	{
		MaxValue = Thrust;
		DesiredAction = ENeeds::Drink;
	}
	if (MaxValue <= Reproduction && Reproduction<=MinReproduction)
	{
		MaxValue = Reproduction;
		DesiredAction = ENeeds::Reproduction;
	}

	return DesiredAction;
}


void ABot::Action()
{
	switch (Current_Status)
	{
	case ENeeds::Eat:
		Eat();
		break;
	case ENeeds::Drink:
		Drink();
		break;
	case ENeeds::Reproduction:
		Func_Reproduction();
		break;
	case ENeeds::Explore_Location:
		Explore_Location();
		break;
	}
}

void ABot::Eat()
{
	UE_LOG(LogTemp, Warning, TEXT("im eat"));

}

void ABot::Drink()
{
	FVector BestLocation(0,0,0); 
	float Distance;

	for (AActor* Water : GetAllActors(AWater::StaticClass()))
	{
		if (BestLocation == FVector(0,0,0) || Distance > FVector::Distance(this->GetActorLocation(), Water->GetActorLocation()))
		{
			BestLocation = Water->GetActorLocation();
			Distance = FVector::Distance(this->GetActorLocation(), BestLocation);
			
		}
		
	}
	BotController->MoveToLocation(BestLocation);
	UE_LOG(LogTemp, Warning, TEXT("im drink"));

}

void ABot::Func_Reproduction()
{
	UE_LOG(LogTemp, Warning, TEXT("im reproduction"));

}

void ABot::Explore_Location()
{
	TArray<AActor*> Found_Actors = GetAllActors(ASpawn_and_Explore_Volume::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("im explore"));
	if (Found_Actors.Num()>0)
	{
		ASpawn_and_Explore_Volume *Act =Cast<ASpawn_and_Explore_Volume>(Found_Actors[FMath::RandRange(0, Found_Actors.Num() - 1)]);
		BotController->MoveToLocation(Act->Select_Point());
	}
}



void ABot::Decrement_Stats(uint8 ModifierHunger, uint8 ModifierThrust, uint8 ModifierReproduction)
{
	Hunger -= ModifierHunger;
	Thrust -= ModifierThrust;
	Reproduction -= ModifierReproduction;
	
	if (Hunger<0)
	{
		Hunger = 0;
		Health -= 1;
	}
	if (Thrust < 0)
	{
		Thrust = 0;
		Health -= 1;
	}
	if (Reproduction < 0)
	{
		Reproduction = 0;
	}
	
	if (Health<=0)
	{
		this->Destroy();
	}

}

// Called to bind functionality to input
void ABot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

