// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHAPERUNNER_API UHitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHitComponent();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void SetShapeComponent(class UShapeComponent* shapeComponent);
protected:
	virtual void BeginPlay() override;
	class UShapeComponent* ShapeComponent;
private:
	bool hasActorTag(AActor *Actor,const FName &Tag);
	void DamageOtherActor(AActor *OtherActor);
	void DamageOwner(AActor *Owner,AActor *OtherActor);
	void DamagePlayer(AActor *OtherActor);
	void DamageObstacle(AActor *OtherActor);
};

