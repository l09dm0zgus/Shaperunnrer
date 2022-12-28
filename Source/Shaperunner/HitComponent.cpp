// Fill out your copyright notice in the Description page of Project Settings.


#include "HitComponent.h"
#include "PlayerSpaceship.h"
#include "Components/ShapeComponent.h"
#include  "Obstacle.h"

UHitComponent::UHitComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHitComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor  != nullptr)
	{
		AActor *Owner = GetOwner();
		DamageOtherActor(OtherActor);
		DamageOwner(Owner);
	}
}


void UHitComponent::SetShapeComponent(UShapeComponent* shapeComponent)
{
	ShapeComponent = shapeComponent;
}

void UHitComponent::BeginPlay()
{
	Super::BeginPlay();
	ShapeComponent->OnComponentHit.AddDynamic(this, &UHitComponent::OnHit);
}

void UHitComponent::DamagePlayer(AActor *OtherActor)
{
	APlayerSpaceship* Player = Cast<APlayerSpaceship>(OtherActor);
	if(Player != nullptr)
	{
		Player->Damage();
	}
}

void UHitComponent::DamageObstacle(AActor* OtherActor)
{
	AObstacle *Obstacle = Cast<AObstacle>(OtherActor);
	if(Obstacle != nullptr)
	{
		Obstacle->Damage();	
	}
}

void UHitComponent::DamageOtherActor(AActor* OtherActor)
{
	FName OtherActorTag;
	if(OtherActor->Tags.Num() != 0)
	{
		OtherActorTag = OtherActor->Tags[0];
	}
	if (OtherActorTag == FName(TEXT("Player")))
	{
		DamagePlayer(OtherActor);
	}
	else
	{
		DamageObstacle(OtherActor);
	}
}

void UHitComponent::DamageOwner(AActor* Owner)
{
	FName OwnerTag;
	if(Owner->Tags.Num() != 0)
	{
		OwnerTag = Owner->Tags[0];
	}
	if (OwnerTag == FName(TEXT("Player")))
	{
		DamagePlayer(Owner);
	}
	else if (OwnerTag == FName(TEXT("Obstacle")))
	{
		DamageOtherActor(Owner);
	}
	else
	{
		Owner->Destroy();
	}
}

