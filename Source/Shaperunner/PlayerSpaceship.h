// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerSpaceship.generated.h"

UCLASS()
class SHAPERUNNER_API APlayerSpaceship : public APawn
{
	GENERATED_BODY()

public:
	APlayerSpaceship();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Damage();

	UPROPERTY(BlueprintReadWrite)
	bool bIsPlayStarted{ false };

	UFUNCTION(BlueprintPure)
	int32 GetLives();

	UFUNCTION(BlueprintPure)
	float GetScore();

protected:
	virtual void BeginPlay() override;
private:
	FVector GetRotationRateFromInputMotion();
	void Move(const FVector &RotationRate);

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	int32 Speed {100};

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ExplosionFX;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* TailFX;
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	class UPlayerMovementComponent* PlayerMovement;

	UPROPERTY(EditAnywhere)
	class UWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere)
	class UHitComponent  *HitComponent;
	
	UPROPERTY(EditAnywhere)
	int32 Lives {3};
	
	UPROPERTY(EditAnywhere)
	class USceneComponent *TailLocation;
	
	float Score{ 0.0f };
};
