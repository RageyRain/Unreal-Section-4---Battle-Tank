// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

//Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get controlled tank
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	
	//Get Player tank
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
		

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		//Fire if ready
		ControlledTank->Fire(); //TODO limit firing rate

	}


}


