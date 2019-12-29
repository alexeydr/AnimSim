// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bot.h"
#include "Predator.generated.h"

/**
 * 
 */
UCLASS()
class ANIMSIM_API APredator : public ABot
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay();

	virtual void Eat();
};
