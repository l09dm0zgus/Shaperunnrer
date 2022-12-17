// Fill out your copyright notice in the Description page of Project Settings.


#include "HitComponent.h"
#include "PlayerSpaceship.h"
#include "Components/ShapeComponent.h"

UHitComponent::UHitComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHitComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor  != nullptr)
	{
		if (OtherActor->Tags.Num() != 0 && OtherActor->Tags[0] == FName(TEXT("Player")))
		{
			APlayerSpaceship* Player = Cast<APlayerSpaceship>(OtherActor);
			Player->TakeDamage();
		}
		else
		{
			OtherActor->Destroy();
		}
		GetOwner()->Destroy();
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


