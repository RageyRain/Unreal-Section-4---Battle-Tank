// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AIController: Begin Play"));

	/*
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: No possessed tank found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: Possessing %s"), *(ControlledTank->GetName()));
	}
	*/

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: No player pawn spotted"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: Spotted %s as player"), *(PlayerTank->GetName()));
	}
}

//Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}





ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	
	return Cast<ATank>(PlayerPawn);
}