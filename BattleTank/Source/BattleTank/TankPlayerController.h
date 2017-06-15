// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldCameraPosition, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector WorldCameraPosition, FVector LookDirection, FVector& OutHitLocation) const;
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Length of vector from player view point
	float fReach = 100.f;

	UPROPERTY(EditAnywhere)
	float CrossHairXRatio = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYRatio = 0.5f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	FVector DoStuff(float percentX, float percentY) const;
};
