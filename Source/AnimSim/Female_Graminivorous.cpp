// Fill out your copyright notice in the Description page of Project Settings.


#include "Female_Graminivorous.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Male_Graminivorous.h"
#include "Engine/World.h"

AFemale_Graminivorous::AFemale_Graminivorous()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Asset(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/DeerStagAndDoe/Meshes/SK_DeerDoe.SK_DeerDoe'"));
	USkeletalMesh* Mesh = Asset.Object;
	this->GetMesh()->SetSkeletalMesh(Mesh);
}


void AFemale_Graminivorous::BeginPlay()
{
	Super::BeginPlay();
}


void AFemale_Graminivorous::Fertilization()
{
	
	uint8 Quantity = FMath::RandRange(1, 5);
	

	this->Reproduction += 100;

	for (size_t i = 0; i < Quantity; i++)
	{
		if (FMath::RandBool())
		{

			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this->GetParentActor();
			SpawnActor<ThisClass>(ThisClass::StaticClass(), this->GetActorLocation() + FVector(0,0,100), FRotator::ZeroRotator, SpawnParam);


		}
		else
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this->GetParentActor();
			SpawnActor<AMale_Graminivorous>(AMale_Graminivorous::StaticClass(), this->GetActorLocation() + FVector(0, 0, 100), FRotator::ZeroRotator, SpawnParam);

		}
	}

	this->HavePartner = false;
	this->Current_Status = this->CheckParam();
	this->Start_Action();
}

void AFemale_Graminivorous::Tick(float DeltaTime)
{
	if (this->HavePartner == true)
	{
		if (this->Hunger < 40 || this->Thrust<40)
		{
			this->HavePartner = false;
			this->Current_Status = CheckParam();
			this->Start_Action();
		}

	}
}
