// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	// Move the barrel frame by frame to value based on max elevation speed and frame rate

	auto ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto TurnChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewTurn = RelativeRotation.Yaw + TurnChange;

	UE_LOG(LogTemp, Warning, TEXT("RawNewTurn %f "), RawNewTurn);
	SetRelativeRotation(FRotator(0, RawNewTurn, 0));
};


