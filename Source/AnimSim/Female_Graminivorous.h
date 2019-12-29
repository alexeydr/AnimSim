// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graminivorous.h"
#include "Engine/World.h"
#include "Female_Graminivorous.generated.h"

/**
 * 
 */

UCLASS()
class ANIMSIM_API AFemale_Graminivorous : public AGraminivorous
{

	GENERATED_BODY()

public:

	AFemale_Graminivorous();

	bool HavePartner = false;

	void Fertilization();

	virtual void Tick(float DeltaTime) override;

	template<typename S>
	FORCEINLINE S* SpawnActor(UClass* Class, const FVector&  Loc, const FRotator& Rot,FActorSpawnParameters SpawnParam)
	{
		return GetWorld()->SpawnActor<S>(Class, Loc, Rot, SpawnParam);
	};

protected:

	virtual void BeginPlay() override;

};
