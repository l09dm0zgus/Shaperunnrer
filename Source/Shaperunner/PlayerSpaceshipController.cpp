// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceshipController.h"
#include "Blueprint/UserWidget.h"

void APlayerSpaceshipController::ShowPlayerHUD()
{	
	AddWidgetToViewport(PlayerHUDClass, HUDWidget);
}

void APlayerSpaceshipController::ShowGameOverScreen()
{

	AddWidgetToViewport(GameOverScreenClass, GameOverScreenWidget);
}

void APlayerSpaceshipController::ShowStartGameScreen()
{
	AddWidgetToViewport(StartGameScreenClass, StartGameScreenWidget);
}

void APlayerSpaceshipController::AddWidgetToViewport(TSubclassOf<class UUserWidget> WidgetClass, UUserWidget* Widget)
{
	if (Widget == nullptr)
	{
		Widget = CreateWidget(this,WidgetClass);
	}
	if (Widget != nullptr)
	{
		Widget->AddToViewport();
	}
}