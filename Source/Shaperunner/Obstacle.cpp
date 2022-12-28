// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "HitComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp,Warning,TEXT("Object Created"))
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = SphereComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComponent);
	HitComponent = CreateDefaultSubobject<UHitComponent>(TEXT("Hit"));
	HitComponent->SetShapeComponent(SphereComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);

}
void AObstacle::AddToSpeed(float SpeedAdd)
{
	this->Speed += SpeedAdd;
}

void AObstacle::Damage()
{
	if(ExplosionFX != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ExplosionFX,GetActorLocation(),FRotator(0.0f),FVector(0.05f));
		Destroy();
	}
}

void AObstacle::Move(float DeltaTime)
{
	FVector Location = GetActorLocation();
	Location.X -= (DeltaTime * Speed);
	SetActorLocation(Location, true);
	if (DestroyLimit > Location.X)
	{
		Destroy();
	}
}

