// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet\GameplayStatics.h"
#include "Bot.generated.h"

UENUM()
enum class ENeeds : uint8
{
	Explore_Location 	UMETA(DisplayName = "Explore Location "),
	Eat 	UMETA(DisplayName = "Eat"),
	Drink 	UMETA(DisplayName = "Drink"),
	Reproduction	UMETA(DisplayName = "Reproduction")
};


UCLASS()
class ANIMSIM_API ABot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABot();

	class USphereComponent *SphereComp;

	TArray<FVector> HerbLocation;


	template<typename T>
	TArray<AActor*> GetAllActors(T Class)
	{
		TArray<AActor*> Found_Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Class, Found_Actors);
		return Found_Actors;
	};


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	class AAIController *BotController;


	virtual void Eat();

	void Drink();

	virtual void Func_Reproduction();

	void Explore_Location();

	virtual void Decrement_Stats(uint8 ModifierHunger = 1, uint8 ModifierThrust = 1, uint8 ModifierReproduction = 1);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ENeeds CheckParam();

	ENeeds Current_Status = ENeeds::Explore_Location;

	inline void Start_Action() {
		Current_Status = CheckParam();
		Action();
	};

	UFUNCTION()
		void Action();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int Hunger = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Thrust = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Reproduction = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Health = 100;
};

