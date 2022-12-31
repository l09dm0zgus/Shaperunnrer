// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetComponentLocation(), GetComponentRotation());
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetComponentLocation());
	}
	Projectile->SetOwner(GetOwner());
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


