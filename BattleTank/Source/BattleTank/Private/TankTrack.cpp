// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Constructor
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Calculate the splippage speed
	auto Velocity = GetComponentVelocity();
	auto RightVector = GetRightVector();
	auto SlippageSpeed = FVector::DotProduct(Velocity, RightVector);

	//Work out the required acceleration this frame to correct
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());

	//Calculate and apply sideways force (F=ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = ((TankRoot->GetMass()) * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	

	//TODO clamp actual throttle value so player can't override
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Track contact"));
}

