// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
// Hold's barrel params and Elevate it
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories=("Rendering", "Lighting"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	// -1 max down spped, +1 max up speed
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere, Category = Setup_params)
	float MaxDegreesPerSecond = 8.f; // default

	UPROPERTY(EditAnywhere, Category = Setup_params)
	float MinElevationDegrees = 0.f; // default

	UPROPERTY(EditAnywhere, Category = Setup_params)
	float MaxElevationDegrees = 40.f; // default
};
