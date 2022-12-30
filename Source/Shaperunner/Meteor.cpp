// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"
#include "Kismet/KismetMathLibrary.h"


void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RandomRotate(DeltaTime);
	
}

void AMeteor::RandomRotate(float DeltaTime)
{
	FRotator Rotation;
	Rotation.Roll = UKismetMathLibrary::RandomFloatInRange(MinimalAngle, MaximalAngle) * DeltaTime;
	Rotation.Yaw = UKismetMathLibrary::RandomFloatInRange(MinimalAngle, MaximalAngle) * DeltaTime;
	Rotation.Pitch = UKismetMathLibrary::RandomFloatInRange(MinimalAngle, MaximalAngle) * DeltaTime;
	AddActorLocalRotation(Rotation);
}

void AMeteor::BeginPlay()
{
	Super::BeginPlay();
}
