// Fill out your copyright notice in the Description page of Project Settings.


#include "Male_Graminivorous.h"
#include "Female_Graminivorous.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AIController.h"

AMale_Graminivorous::AMale_Graminivorous()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Asset(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/DeerStagAndDoe/Meshes/SK_DeerStag.SK_DeerStag'"));
	USkeletalMesh* Mesh = Asset.Object;
	this->GetMesh()->SetSkeletalMesh(Mesh);
}

void AMale_Graminivorous::Func_Reproduction()
{

	bool FindPartner = false;
	for (AActor* Act : GetAllActors(AFemale_Graminivorous::StaticClass()))
	{
		Fem = Cast<AFemale_Graminivorous>(Act);
		if (!Fem->HavePartner && Fem->Reproduction<40)
		{
			FindPartner = true;
			Fem->HavePartner = true;

			BotController->MoveToActor(Fem);
			break;
		}
	}
	if (!FindPartner)
	{
		Current_Status = ENeeds::Explore_Location;
		Start_Action();
	}
}

void AMale_Graminivorous::Tick(float DeltaTime)
{
	ABot::Tick(DeltaTime);

	
}


void AMale_Graminivorous::BeginPlay()
{
	Super::BeginPlay();

}

void AMale_Graminivorous::BoxOverlapInChild(AActor * OtherActor)
{
	AFemale_Graminivorous* OtherFem = Cast<AFemale_Graminivorous>(OtherActor);
	if (Fem)
	{
		if (Fem == OtherFem)
		{
			this->Reproduction += 100;
			this->Current_Status = this->CheckParam();
			this->Start_Action();
			Fem->Fertilization();
			this->Fem = NULL;
		}

	}
}
