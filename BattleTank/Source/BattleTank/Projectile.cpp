// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	projectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Movement_component"));
	projectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float fSpeed)
{
	UE_LOG(LogTemp, Error, TEXT("%f: FIRE!!!"), fSpeed);
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*fSpeed); // Moves forward. In ATank::Fire we've created it with direction same as barrel.
	projectileMovementComponent->Activate();
};