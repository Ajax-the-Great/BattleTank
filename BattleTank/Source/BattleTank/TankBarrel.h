// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
// Hold's barrel params and Elevate it
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories=("Collision", "Rendering", "Lighting"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float Degrees);
	
	UPROPERTY(EditAnywhere, Category = Setup_params)
	float MaxDegreesPerSecond = 20.f; // default

	UPROPERTY(EditAnywhere, Category = Setup_params)
	float MinElevationDegrees = 0.f; // default

	UPROPERTY(EditAnywhere, Category = Setup_params)
	float MaxElevationDegrees = 40.f; // default
};
