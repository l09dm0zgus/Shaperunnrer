// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerMovementComponent.h"
#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShaperunnerGameModeBase.h"


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

	TailLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Tail Location"));
	TailLocation->SetupAttachment(RootComponent);
	
}
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
	UNiagaraFunctionLibrary::SpawnSystemAttached(TailFX,TailLocation,NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::SnapToTarget, true);
}

FVector APlayerSpaceship::GetRotationRateFromInputMotion()
{
	FVector Tilt, RotationRate, Gravity, Acceleration;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
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
	if (bIsPlayStarted)
	{
		Move(GetRotationRateFromInputMotion());
	}
}

void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, WeaponComponent, &UWeaponComponent::Fire);
}

void APlayerSpaceship::Damage()
{
	Lives--;
	if (Lives <= 0)
	{
		AShaperunnerGameModeBase *GameMode = Cast<AShaperunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode != nullptr)
		{
			GameMode->GameOver();
		}
		
		if (ExplosionSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
		}
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ExplosionFX,GetActorLocation(),FRotator(0.0f),FVector(0.05f));
		Destroy();
	}
}

int32 APlayerSpaceship::GetLives()
{
	return Lives;
}

