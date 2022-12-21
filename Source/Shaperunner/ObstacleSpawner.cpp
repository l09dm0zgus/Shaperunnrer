// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstacle.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacleSpawner::Spawn()
{
	FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), BoxComponent->GetScaledBoxExtent());
	int32 ObstacleId = UKismetMathLibrary::RandomIntegerInRange(0, Obstacles.Num() - 1);
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FRotator Rotation;
	Location.Z = PlayerSpaceshipZLocation;
	AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(Obstacles[ObstacleId], Location, Rotation, ActorSpawnParams);
}

void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AObstacleSpawner::StartSpawning()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AObstacleSpawner::Spawn, SpawnRate, true, 2.0f);
}

void AObstacleSpawner::StopSpawning()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

