// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	// Move the barrel frame by frame to value based on max elevation speed and frame rate

	UE_LOG(LogTemp, Warning, TEXT("%f: Turn by relative speed  %f "), Time, RelativeSpeed);
	auto ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto TurnChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewTurn = RelativeRotation.Yaw + TurnChange;
	
	SetRelativeRotation(FRotator(0, RawNewTurn, 0));
};


