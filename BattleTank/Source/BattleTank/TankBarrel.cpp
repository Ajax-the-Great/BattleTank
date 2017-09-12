// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float Degrees)
{
	// Move the barrel frame by frame to value based on max elevation speed and frame rate
	UE_LOG(LogTemp, Warning, TEXT("Elevate by %f "), Degrees);
};

