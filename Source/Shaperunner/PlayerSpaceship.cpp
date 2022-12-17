// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerMovementComponent.h"
#include "WeaponComponent.h"
APlayerSpaceship::APlayerSpaceship()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = SphereComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComponent);
	PlayerMovement = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement"));
	PlayerMovement->UpdatedComponent = RootComponent;
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	WeaponComponent->SetupAttachment(RootComponent);
}

void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}
}

FVector APlayerSpaceship::GetRotationRateFromInputMotion()
{
	FVector Tilt, RotationRate, Gravity, Acceleration;
	if (PlayerController)
	{
		PlayerController->GetInputMotionState(Tilt, RotationRate, Gravity, Acceleration);
		return RotationRate;
	}
	return FVector();
}

void APlayerSpaceship::Move(const FVector& RotationRate)
{
	PlayerMovement->AddInputVector(GetActorForwardVector() * RotationRate.X);
	PlayerMovement->AddInputVector(GetActorRightVector() * RotationRate.Y);
}


void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(GetRotationRateFromInputMotion());
}

void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, WeaponComponent, &UWeaponComponent::Fire);
}

void APlayerSpaceship::TakeDamage()
{
	Lives--;
	if (Lives <= 0)
	{
		Destroy();
	}
}
