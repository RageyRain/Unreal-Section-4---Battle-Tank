// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "BattleTank.h"
//#include "Public/UObject/Class.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h" //Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	ATank* GetControlledTank() const;

	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects with the world
	void AimTowardsCrosshair();
	
	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	
};
