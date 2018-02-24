// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming_component"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrel(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrel(BarrelToSet);
	BarrelForProjector = BarrelToSet;
};

void ATank::SetTurret(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurret(TurretToSet);
};

void ATank::Fire()
{
	float fTime = FPlatformTime::Seconds();

	bool isReloaded = fTime - fLastTimeFired > fReloadTimeInSeconds;
	if (!isReloaded)
		return;

	fLastTimeFired = fTime;

	if (!BarrelForProjector)
		return;
	
	FVector ProjectileLocation = BarrelForProjector->GetSocketLocation("ProjectileStart");
	FRotator ProjectileRotation = BarrelForProjector->GetSocketRotation("ProjectileStart");
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
	Projectile->LaunchProjectile(LaunchSpeed);
};