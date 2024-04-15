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

