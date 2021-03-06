// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

// Hold's and move's barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector LocationToAim, float LaunchSpeed);
	void SetBarrel(UTankBarrel* BarrelToSet);
	void SetTurret(UTankTurret* TurretToSet);
	
private:
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
