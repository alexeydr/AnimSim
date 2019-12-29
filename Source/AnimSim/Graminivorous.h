// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bot.h"
#include "Graminivorous.generated.h"

/**
 * 
 */
UCLASS()
class ANIMSIM_API AGraminivorous : public ABot
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void BoxOverlapInChild(AActor* OtherActor) {};

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

	void Eat() override final;

	UFUNCTION()
	virtual void Decrement_Stats(uint8 ModifierHunger = 1, uint8 ModifierThrust = 1, uint8 ModifierReproduction = 1) override;
	

};
