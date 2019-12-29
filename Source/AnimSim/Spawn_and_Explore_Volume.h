// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawn_and_Explore_Volume.generated.h"

UCLASS()
class ANIMSIM_API ASpawn_and_Explore_Volume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawn_and_Explore_Volume();

	class UBoxComponent* BoxComp;

	FVector Select_Point();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
