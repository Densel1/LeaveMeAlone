// LeaveMeAlone Game by Netologia. All Gights Reserved.


#include "Player/LMAPlayerController.h"

ALMAPlayerController::ALMAPlayerController()
{

}

void ALMAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ALMAPlayerController::BeginSpectatingState()
{
	SetControlRotation(FRotator(-25.0f, 0.0f, 0.0f));
	Super::BeginSpectatingState();
}