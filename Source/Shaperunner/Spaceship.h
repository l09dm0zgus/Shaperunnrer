// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Spaceship.generated.h"

/**
 * 
 */
UCLASS()
class SHAPERUNNER_API ASpaceship : public AObstacle
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
	float ShootingRate{ 1.5f };

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* TailFX;
	
	UPROPERTY(EditAnywhere)
    class USceneComponent* TailFXPosition;
	
	UPROPERTY(EditAnywhere)
	class UWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere)
	double AddToRotation{30};

public:
	ASpaceship();
	virtual void Tick(float DeltaTime) override;
};
