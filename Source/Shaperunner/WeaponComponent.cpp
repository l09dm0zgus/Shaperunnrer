// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Projectile.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetComponentLocation(), GetComponentRotation());
	Projectile->SetOwner(GetOwner());
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


