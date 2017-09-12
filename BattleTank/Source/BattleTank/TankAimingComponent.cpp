// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector LocationToAim, float LaunchSpeed)
{
	if (!Barrel)
		return;
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("ProjectileStart");

	// Calc LaunchVelocity
	bool bCalcSuccess = false;
	bCalcSuccess = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		LocationToAim,
		LaunchSpeed,
		false,
		50.f,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray <AActor *>(),
		true
	);
	if (bCalcSuccess)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();

		auto TankName = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("LaunchVelocity %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming from %s at %s with speed %f"), *TankName, *BarrelLocation.ToString(), *LocationToAim.ToString(), LaunchSpeed);
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("Aim rotator %s "), *AimRotator.ToString());
	Barrel->Elevate(5); // TODO Remove magick number
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}