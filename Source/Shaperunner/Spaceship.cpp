// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "WeaponComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "HitComponent.h"

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,WeaponComponent,&UWeaponComponent::Fire,ShootingRate,true,0.0f);
	UNiagaraFunctionLibrary::SpawnSystemAttached(TailFX, TailFXPosition, NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::SnapToTarget, true);

}

ASpaceship::ASpaceship()
{
	RootComponent = SphereComponent;
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	WeaponComponent->SetupAttachment(RootComponent);
	TailFXPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Tail position"));
	TailFXPosition->SetupAttachment(RootComponent);
	
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
