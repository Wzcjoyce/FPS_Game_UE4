// Zuocheng Wang 2022


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Warning, TEXT("We have finished."));

    //remove the HUD from viewport after game has ended
    HUD->RemoveFromViewport();
    if(bIsWinner)
    {
        // User Controlled Characer is Winner
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, WinRestartDelay);
    
    }
    else
    {
        // User Controlled Characer is not Winner
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
        // game restart timer
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, LoseRestartDelay);
    }

}

// Called when the game starts or when spawned
void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
    // User Controlled Characer is not Winner
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }

    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }

}



