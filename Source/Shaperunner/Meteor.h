// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Meteor.generated.h"

/**
 * 
 */
UCLASS()
class SHAPERUNNER_API AMeteor : public AObstacle
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
private:
	void RandomRotate(float DeltaTime);
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float MinimalAngle{ 0.0f };
	UPROPERTY(EditAnywhere)
	float MaximalAngle{ 60.0f };
};
