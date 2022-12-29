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
		DamageOwner(Owner,OtherActor);
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

bool UHitComponent::hasActorTag(AActor* Actor, const FName& Tag)
{
	if(Actor->Tags.Num() != 0)
	{
		return Tag == Actor->Tags[0];
	}
	return false;
}

void UHitComponent::DamageOtherActor(AActor* OtherActor)
{

	if (hasActorTag(OtherActor,FName(TEXT("Player"))))
	{
		DamagePlayer(OtherActor);
	}
	else
	{
		DamageObstacle(OtherActor);
	}
}

void UHitComponent::DamageOwner(AActor* Owner,AActor *OtherActor)
{

	if (hasActorTag(Owner,FName(TEXT("Obstacle"))))
	{
		DamageOtherActor(Owner);
	}
	else if(hasActorTag(Owner,FName(TEXT("Player"))) && hasActorTag(OtherActor,FName(TEXT("Obstacle"))))
	{
		DamagePlayer(Owner);
	}
	else if(hasActorTag(Owner,FName(TEXT("Projectile"))))
	{
		Owner->Destroy();
	}
}

