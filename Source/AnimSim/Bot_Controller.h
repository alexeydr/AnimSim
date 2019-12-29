// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Bot_Controller.generated.h"

/**
 * 
 */

UCLASS()
class ANIMSIM_API ABot_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void OnPossess(APawn* InPawn) override;
	
	

};
