// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "Components/StaticMeshComponent.h"

APlayerSpaceship::APlayerSpaceship()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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


void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Tilt,RotationRate,Gravity,Acceleration;
	if (PlayerController)
	{
		PlayerController->GetInputMotionState(Tilt, RotationRate, Gravity, Acceleration);
		FVector NewLocation(RotationRate.X, RotationRate.Y, 0.0f);
		SetActorLocation(GetActorLocation() + (Speed * DeltaTime * NewLocation));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *GetActorLocation().ToCompactString());
	}

}

void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

