// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerSpaceship.h"
#include "Obstacle.h"
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
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = CapsuleComponent;
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

bool AProjectile::HasActorTag(AActor* Actor, const FName& Tag)
{
	if(Actor->Tags.Num() != 0)
	{
		return  Actor->Tags[0] == Tag;
	}
	return false;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	if(HasActorTag(OtherActor,FName(TEXT("Player"))))
	{
		APlayerSpaceship *PlayerSpaceship = Cast<APlayerSpaceship>(OtherActor);
		PlayerSpaceship->Damage();
	}
	else if (HasActorTag(OtherActor,FName(TEXT("Obstacle"))))
	{
		AObstacle  *Obstacle = Cast<AObstacle>(OtherActor);
		Obstacle->Damage();
	}
	Destroy();
}



