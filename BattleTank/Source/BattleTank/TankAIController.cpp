// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return dynamic_cast<ATank*>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* pPlayerController = GetWorld()->GetFirstPlayerController();
	if (pPlayerController)
		return dynamic_cast<ATank*>(pPlayerController->GetPawn());
	else
		return nullptr;
}

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* pTank = GetControlledTank();
	if (pTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank - %s"), *(pTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO AI TANK"));
	}

	ATank* pPlayerController = GetPlayerTank();
	if (pPlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player tank - %s"), *(pPlayerController->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI NOT FOUND PLAYER TANK"));
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* pPlayerTank = GetPlayerTank();
	if (!pPlayerTank)
		return;

	ATank* pControlledTank = GetControlledTank();
	if (!pControlledTank)
		return;

	auto PlayerTankLocation = pPlayerTank->GetActorLocation();
	pControlledTank->AimAt(PlayerTankLocation);
	// Fire if ready
	pControlledTank->Fire();
}
