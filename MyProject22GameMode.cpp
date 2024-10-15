
#include "MyProject22GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AMyProject22GameMode::AMyProject22GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyProject22GameMode::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0); 
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
    }
}
