// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "WeaponComponent.h"
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,WeaponComponent,&UWeaponComponent::Fire,ShootingRate,true,0.0f);
}

ASpaceship::ASpaceship()
{
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	WeaponComponent->SetupAttachment(RootComponent);
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
