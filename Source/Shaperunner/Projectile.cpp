// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerSpaceship.h"
#include "HitComponent.h"
#include "Components/CapsuleComponent.h" 

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	InitialLifeSpan = 5.0f;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->MaxSpeed = 500.0f;
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->UpdatedComponent = RootComponent;
	HitComponent = CreateDefaultSubobject<UHitComponent>(TEXT("Hit"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = CapsuleComponent;
	Mesh->SetupAttachment(RootComponent);
	HitComponent->SetShapeComponent(CapsuleComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



