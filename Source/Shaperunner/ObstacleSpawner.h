// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class SHAPERUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleSpawner();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	void Spawn();
	UPROPERTY(EditAnywhere)
	float SpawnRate{ 3.0 };
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AObstacle>> Obstacles;
	UPROPERTY(EditAnywhere)
	float PlayerSpaceshipZLocation{ 32.0 };
	FTimerHandle TimerHandle;
};
