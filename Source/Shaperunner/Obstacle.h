// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class SHAPERUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	virtual void Tick(float DeltaTime) override;
	void AddToSpeed(float SpeedAdd);
protected:
	void Move(float DeltaTime);
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
	float Speed{ 500.0f };
	UPROPERTY(EditAnywhere)
	float DestroyLimit{ 0.0 };
};
