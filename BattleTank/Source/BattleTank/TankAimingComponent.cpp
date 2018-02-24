// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector LocationToAim, float LaunchSpeed)
{
	if (!Barrel)
		return;
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("ProjectileStart");

	// Calc LaunchVelocity
	FCollisionResponseParams ResponseParam(ECollisionResponse::ECR_Block);
	bool bCalcSuccess = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		LocationToAim,
		LaunchSpeed,
		false,
		0,
		0/*,
		ESuggestProjVelocityTraceOption::TraceFullPath,
		ResponseParam,
		TArray <AActor *>(),
		false*/
	);
	if (bCalcSuccess)
	{
		
		//FColor color(255, 0, 0);
		//DrawDebugLine(GetWorld(), StartLocation, LaunchVelocity, color, false, 0.f, 0, 10.f);
		UE_LOG(LogTemp, Warning, TEXT("LaunchVelocity %s"), *LaunchVelocity.ToString());

		auto AimDirection = LaunchVelocity.GetSafeNormal();

		auto TankName = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation();
		//UE_LOG(LogTemp, Warning, TEXT("LaunchVelocity %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming from %s at %s with speed %f"), *TankName, *BarrelLocation.ToString(), *LocationToAim.ToString(), LaunchSpeed);
		MoveBarrelTowards(AimDirection);
		//MoveTurretTowards(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		// Move the barrel frame by frame to value based on max elevation speed and frame rate
		UE_LOG(LogTemp, Warning, TEXT("%f: No solution"));
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	UE_LOG(LogTemp, Warning, TEXT("BarrelRotator %s"), *BarrelRotator.ToString());
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("Aim  rotator %s "), *AimRotator.ToString());
	//if (AimRotator.Pitch < 0)
		//return; // It's meaningless to aim with negative pitch - we cant't move burrel down. But we can ruine yaw, trying to aim on something we can't rich.
	Barrel->Elevate(DeltaRotator.Pitch); 
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Turn(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Turn(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and aim direction
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - TurretRotator;
	UE_LOG(LogTemp, Warning, TEXT("TurretRotator yaw %f Aim rotator yaw %f "), TurretRotator.Yaw, AimRotator.Yaw);
	Turret->Turn(DeltaRotator.Yaw); // TODO Remove magick number
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}