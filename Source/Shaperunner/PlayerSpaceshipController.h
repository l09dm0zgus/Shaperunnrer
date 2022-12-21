// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerSpaceshipController.generated.h"

/**
 * 
 */
UCLASS()
class SHAPERUNNER_API APlayerSpaceshipController : public APlayerController
{
	GENERATED_BODY()
public:
	void ShowPlayerHUD();
	void ShowGameOverScreen();
	void ShowStartGameScreen();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameOverScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> StartGameScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	class UUserWidget* HUDWidget{ nullptr };
	class UUserWidget* StartGameScreenWidget{ nullptr };
	class UUserWidget* GameOverScreenWidget{ nullptr };

	void AddWidgetToViewport(TSubclassOf<class UUserWidget> WidgetClass, class UUserWidget* Widget);
};
