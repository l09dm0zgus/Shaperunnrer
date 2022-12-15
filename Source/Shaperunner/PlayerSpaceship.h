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
protected:
	virtual void BeginPlay() override;
private:
	FVector GetRotationRateFromInputMotion();
	void Move(const FVector &RotationRate);
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	int32 Speed {100};
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
	class UPlayerMovementComponent* PlayerMovement;
	UPROPERTY(EditAnywhere)
	class UWeaponComponent* WeaponComponent;
};
