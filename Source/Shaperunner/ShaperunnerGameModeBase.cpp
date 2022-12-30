// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShaperunnerGameModeBase.h"
#include "Obstacle.h"
#include "PlatformMover.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerSpaceshipController.h"
#include "ObstacleSpawner.h"
#include "PlayerSpaceship.h"
#include "Projectile.h"

AShaperunnerGameModeBase::AShaperunnerGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShaperunnerGameModeBase::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}



void AShaperunnerGameModeBase::StartGame()
{
	Score = 0;
	if (PlayerController != nullptr)
	{
		PlayerController->ShowPlayerHUD();
		RestartPlayer(PlayerController);
	}
	APlayerSpaceship *PlayerSpaceship = Cast<APlayerSpaceship>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if(PlayerSpaceship != nullptr)
	{
		PlayerSpaceship->bIsPlayStarted = true;
	}
	if (PlatformMover != nullptr)
	{
		PlatformMover->RestoreStartSpeed();
	}
	if (ObstacleSpawner != nullptr)
	{
		ObstacleSpawner->StartSpawning();
	}
	GetWorld()->GetTimerManager().SetTimer(PlatformMoverTimerHandle, this, &AShaperunnerGameModeBase::ChangePlatformMoverSpeed, ChangingPlatformMoverSpeedRate, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(ObstaclesTimerHandle, this, &AShaperunnerGameModeBase::ChangeObstaclesSpeed, ChangingObstaclesSpeedRate, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(ScoreAddingTimerHandle,this,&AShaperunnerGameModeBase::AddScore,AddingScoreRate,true,1.0f);
	
}
void AShaperunnerGameModeBase::AddScore()
{
	Score += 10;
}

void AShaperunnerGameModeBase::ClearActors()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AObstacle::StaticClass(),Obstacles);
	for (auto Actor : Obstacles)
	{
		if (Actor != nullptr)
		{
			Actor->Destroy();
		}
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AProjectile::StaticClass(),Projectiles);
	for (auto Actor : Projectiles)
	{
		if (Actor != nullptr)
		{
			Actor->Destroy();
		}
	}
}

void AShaperunnerGameModeBase::GameOver()
{
	if (PlayerController != nullptr)
	{
		PlayerController->ShowGameOverScreen();
	}
	GetWorldTimerManager().ClearTimer(PlatformMoverTimerHandle);
	GetWorldTimerManager().ClearTimer(ObstaclesTimerHandle);
	GetWorldTimerManager().ClearTimer(ScoreAddingTimerHandle);
	if (PlatformMover != nullptr)
	{
		PlatformMover->Stop();
	}
	if (ObstacleSpawner != nullptr)
	{
		ObstacleSpawner->StopSpawning();
	}

	ClearActors();
}

float AShaperunnerGameModeBase::GetScore()
{
	return Score;
}


APlatformMover* AShaperunnerGameModeBase::GetPlatformMover()
{
	PlatformMover = Cast<APlatformMover>(UGameplayStatics::GetActorOfClass(GetWorld(), APlatformMover::StaticClass()));
	return PlatformMover;
}


void AShaperunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlatformMover = GetPlatformMover();
	PlayerController = GetPlayerController();
	ObstacleSpawner = GetObstacleSpawner();
	if (PlayerController != nullptr)
	{
		PlayerController->ShowStartGameScreen();
	}
}




APlayerSpaceshipController* AShaperunnerGameModeBase::GetPlayerController()
{
	return Cast<APlayerSpaceshipController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

AObstacleSpawner* AShaperunnerGameModeBase::GetObstacleSpawner()
{
	return Cast<AObstacleSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(),AObstacleSpawner::StaticClass()));
}

void AShaperunnerGameModeBase::ChangeObstaclesSpeed()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AObstacle::StaticClass(),Obstacles);
	for (auto Actor : Obstacles)
	{
		AObstacle* Obstacle = Cast<AObstacle>(Actor);
		if (Obstacle != nullptr)
		{
			Obstacle->AddToSpeed(ObstacleSpeedAdd);
		}
	}

}

void AShaperunnerGameModeBase::ChangePlatformMoverSpeed()
{
	if (PlatformMover != nullptr)
	{
		PlatformMover->AddToSpeed(PlatformMoverSpeedAdd);
	}
}
