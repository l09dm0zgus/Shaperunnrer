// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformMover.h"
#include "Components/StaticMeshComponent.h"
APlatformMover::APlatformMover()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void APlatformMover::BeginPlay()
{
	Super::BeginPlay();
	StartFrom = GetActorLocation().X;
}

void APlatformMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void APlatformMover::Move(float DeltaTime)
{
	FVector Location = GetActorLocation();
	if (Location.X > End)
	{
		Location.X -= (DeltaTime * Speed);
		SetActorLocation(Location);
	}
	else
	{
		Location.X = StartFrom;
		SetActorLocation(Location);
	}
}
