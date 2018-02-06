// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Constructor
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive the Tracks
	DriveTrack();
	//Apply sideways force
	ApplySidewaysForce();
	//Reset Throttle
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
	//Calculate the splippage speed
	auto Velocity = GetComponentVelocity();
	auto RightVector = GetRightVector();
	auto SlippageSpeed = FVector::DotProduct(Velocity, RightVector);

	//Work out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());

	//Calculate and apply sideways force (F=ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = ((TankRoot->GetMass()) * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);

}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


