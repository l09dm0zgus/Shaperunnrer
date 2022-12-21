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
	virtual void RestartPlayer(AController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	void GameOver();
private:
	TArray<AActor*> Obstacles;

	class APlatformMover* PlatformMover;
	class APlatformMover* GetPlatformMover();

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float ChangingObstaclesSpeedRate{ 10.0f };

	UPROPERTY(EditAnywhere)
	float ObstacleSpeedAdd{ 15.3f };

	UPROPERTY(EditAnywhere)
	float ChangingPlatformMoverSpeedRate{ 1.0f };

	UPROPERTY(EditAnywhere)
	float PlatformMoverSpeedAdd{ 0.1f };

	class APlayerSpaceshipController* GetPlayerController();
	class APlayerSpaceshipController* PlayerController;
	class AObstacleSpawner* GetObstacleSpawner();
	class AObstacleSpawner* ObstacleSpawner;

	void ChangeObstaclesSpeed();
	void ChangePlatformMoverSpeed();
	FTimerHandle ObstaclesTimerHandle;
	FTimerHandle PlatformMoverTimerHandle;

};
