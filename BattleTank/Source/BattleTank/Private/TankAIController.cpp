// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"	// So we can implement OnDeath

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
	auto ControlledTank = GetPawn();
	
	//Get Player tank
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }
			
	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
		

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	

	//Fire if aiming or locked
	if (AimingComponent->GetFiringState() == EFiringState::Ready)
	{
		AimingComponent->Fire(); //TODO limit firing rate
	}

	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI Broadcast received"));
	if (!GetPawn())	{ return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

