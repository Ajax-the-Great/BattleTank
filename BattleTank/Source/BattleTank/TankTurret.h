// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Rendering", "Lighting"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:		
	void Turn(float RelativeSpeed);
	
	UPROPERTY(EditDefaultsOnly, Category = Setup_params)
	float MaxDegreesPerSecond = 20.f; // default
};
