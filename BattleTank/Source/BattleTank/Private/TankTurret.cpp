// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//Rotate the turret the right amount this frame
	//given a maximum rotation speed, and the time frame
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	auto NewRotation = RelativeRotation.Yaw + RotationChange; // POT PROB
	SetRelativeRotation(FRotator(0, NewRotation, 0));
	
	
	
	
	//UE_LOG(LogTemp, Warning, TEXT("Turret-Rotate() called at speed %f"), RelativeSpeed);

}


