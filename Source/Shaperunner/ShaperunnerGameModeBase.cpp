// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShaperunnerGameModeBase.h"
#include "Obstacle.h"
#include "PlatformMover.h"
#include "Kismet/GameplayStatics.h"
AShaperunnerGameModeBase::AShaperunnerGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;

}


void AShaperunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(PlatformMoverTimerHandle, this, &AShaperunnerGameModeBase::ChangePlatformMoverSpeed, ChangingPlatformMoverSpeedRate, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(ObstaclesTimerHandle, this, &AShaperunnerGameModeBase::ChangeObstaclesSpeed, ChangingObstaclesSpeedRate, true, 1.0f);

}

void AShaperunnerGameModeBase::ChangeObstaclesSpeed()
{
	TArray<AActor*> Obstacles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AObstacle::StaticClass(),Obstacles);
	UE_LOG(LogTemp, Warning, TEXT("Change Obstacles Speed called"));
	for (auto Actor : Obstacles)
	{
		AObstacle* Obstacle = Cast<AObstacle>(Actor);
		if (Obstacle != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Changing obstacle speed"));
			Obstacle->AddToSpeed(ObstacleSpeedAdd);
		}
	}

}

void AShaperunnerGameModeBase::ChangePlatformMoverSpeed()
{
	TArray<AActor*> PlatformMovers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlatformMover::StaticClass(), PlatformMovers);
	UE_LOG(LogTemp, Warning, TEXT("Change PlatformMover Speed called"));
	for (auto Actor : PlatformMovers)
	{
		APlatformMover* PlatformMover = Cast<APlatformMover>(Actor);
		if (PlatformMover != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Changing PlatformMover speed"));
			PlatformMover->AddToSpeed(PlatformMoverSpeedAdd);
		}
	}
}
