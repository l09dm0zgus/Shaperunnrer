// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PlayerSpaceship.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp,Warning,TEXT("Object Created"))
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = SphereComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComponent);

}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentHit.AddDynamic(this, &AObstacle::OnHit);
}

bool AObstacle::HasActorTag(AActor* Actor, const FName& Tag)
{
	return Actor->Tags.Contains(Tag);
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

void AObstacle::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	
	if(HasActorTag(OtherActor,FName(TEXT("Player"))))
	{
		APlayerSpaceship *PlayerSpaceship = Cast<APlayerSpaceship>(OtherActor);
		PlayerSpaceship->Damage();
		Damage();
	}
	else if (HasActorTag(OtherActor,FName(TEXT("Obstacle"))))
	{
		AObstacle  *Obstacle = Cast<AObstacle>(OtherActor);
		Obstacle->Damage();
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

