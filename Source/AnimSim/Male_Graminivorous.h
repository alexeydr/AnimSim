// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graminivorous.h"
#include "Male_Graminivorous.generated.h"

/**
 * 
 */
UCLASS()
class ANIMSIM_API AMale_Graminivorous : public AGraminivorous
{
	GENERATED_BODY()
	
public:

	AMale_Graminivorous();

	void Func_Reproduction() override;

	virtual void Tick(float DeltaTime) override;

	class AFemale_Graminivorous* Fem;

protected:


	virtual void BeginPlay() override;

	void BoxOverlapInChild(AActor* OtherActor) override;

};
