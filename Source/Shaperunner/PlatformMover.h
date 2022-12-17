// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformMover.generated.h"

UCLASS()
class SHAPERUNNER_API APlatformMover : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformMover();
	virtual void Tick(float DeltaTime) override;
	void AddToSpeed(float SpeedAdd);
protected:
	virtual void BeginPlay() override;
private:
	void Move(float DeltaTime);
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	float StartFrom{ 0.0f };
	UPROPERTY(EditAnywhere)
	float End{ -740.0f };
	UPROPERTY(EditAnywhere)
	float Speed{50.0f};

};
