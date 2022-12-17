// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShaperunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHAPERUNNER_API AShaperunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AShaperunnerGameModeBase();
private:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float ChangingObstaclesSpeedRate{ 10.0f };
	UPROPERTY(EditAnywhere)
	float ObstacleSpeedAdd{ 15.3f };
	UPROPERTY(EditAnywhere)
	float ChangingPlatformMoverSpeedRate{ 1.0f };
	UPROPERTY(EditAnywhere)
	float PlatformMoverSpeedAdd{ 0.1f };
	void ChangeObstaclesSpeed();
	void ChangePlatformMoverSpeed();
	FTimerHandle ObstaclesTimerHandle;
	FTimerHandle PlatformMoverTimerHandle;

};
