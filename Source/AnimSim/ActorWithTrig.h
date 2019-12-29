// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bot.h"
#include "ActorWithTrig.generated.h"


UCLASS()
class ANIMSIM_API AActorWithTrig : public AActor
{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorWithTrig();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* StaticMesh;

	class UBoxComponent* BoxComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//bool Object_Action(AActor* Act);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
