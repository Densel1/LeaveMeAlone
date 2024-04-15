// LeaveMeAlone Game by Netologia. All Gights Reserved.


#include "LMA.h"

#include "Public/Player/LMADefaultCharacter.h"
#include "Public/Player/LMAPlayerController.h"

ALMA::ALMA()
{
	DefaultPawnClass = ALMADefaultCharacter::StaticClass();
	PlayerControllerClass = ALMAPlayerController::StaticClass();

}