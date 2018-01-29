// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.generated.h" //Must be at bottom

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Fire();


private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	// TODO Remove once firing is moved to aiming component 
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FiringSpeed = 4000; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;
		
	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO Remove


	double LastFireTime = 0;
};
