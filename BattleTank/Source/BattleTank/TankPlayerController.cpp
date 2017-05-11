// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return dynamic_cast<ATank*>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	UE_LOG(LogTemp, Warning, TEXT("AimTowardsCrosshair"));
	if (!GetControlledTank())
		return;
	// Get world location via linettrace from crosshair
	// If it hits the landscape
		// Tell controller to aim this point
};

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* pTank = GetControlledTank();
	if (pTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank - %s"), *(GetControlledTank()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO PLAYER TANK"));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}