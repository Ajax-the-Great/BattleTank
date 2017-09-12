// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return dynamic_cast<ATank*>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation is - %s"), *HitLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO HitLocation"));
	}
	// Get world location via linettrace from crosshair
	// If it hits the landscape
		// Tell controller to aim this point
};
FVector ATankPlayerController::DoStuff(float percentX, float percentY) const
{
	int32 nViewportSizeX = 0, nViewportSizeY = 0;
	GetViewportSize(nViewportSizeX, nViewportSizeY);
	FVector2D ScreenLocation(nViewportSizeX * percentX, nViewportSizeY * percentY);
	FVector WorldCameraPosition;
	FVector LookDirection;
	FColor color(255, 0, 0);

	GetLookDirection(ScreenLocation, WorldCameraPosition, LookDirection);
	UE_LOG(LogTemp, Warning, TEXT("%f\t%f\t%s,\t%s"), percentX, percentY, *WorldCameraPosition.ToString(), *LookDirection.ToString());
	FVector endLine = WorldCameraPosition + LookDirection*30000.f;
	DrawDebugLine(GetWorld(), WorldCameraPosition, endLine, color, false, 0.f, 0, 10.f);
	return LookDirection;
};

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 nViewportSizeX = 0, nViewportSizeY = 0;
	GetViewportSize(nViewportSizeX, nViewportSizeY);
	FVector2D ScreenLocation(nViewportSizeX * CrossHairXRatio, nViewportSizeY * CrossHairYRatio);
	FVector WorldCameraPosition;
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, WorldCameraPosition, LookDirection))
	{
		//DoStuff(0.f, 0.f);
		//DoStuff(0.f, 1.f);
		//DoStuff(1.f, 0.f);
		//DoStuff(1.f, 1.f);
		//auto vec1 = DoStuff(0.5, 0.f);
		//auto vec2 = DoStuff(0.5f, 1.f);
		//DoStuff(0.5f, 0.333333f);
		//float dp = FVector::DotProduct(vec1, vec2);
		//float rads = FMath::Acos(dp);
		//float angle = FMath::RadiansToDegrees(rads);
		//UE_LOG(LogTemp, Warning, TEXT("Angle \t%f\t%f\t%f"), dp, rads, angle);

		GetLookVectorHitLocation(WorldCameraPosition, LookDirection, OutHitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldCameraPosition, FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
		return false;
	FVector Start = WorldCameraPosition;
	FVector End = Start + LookDirection*LineTraceRange;
	FCollisionQueryParams collisionQueryParams("", false, ControlledTank);
	//UE_LOG(LogTemp, Warning, TEXT("We are - %s"), *ControlledTank->GetName());
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		collisionQueryParams))
	{
		AActor* HitActor = HitResult.GetActor();
		//UE_LOG(LogTemp, Warning, TEXT("HitResult is - %s"), *HitActor->GetName());

		OutHitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation is - %s"), *OutHitLocation.ToString());
		return true;
	}
	else
		return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldCameraPosition, FVector& LookDirection) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldCameraPosition, LookDirection);
}

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