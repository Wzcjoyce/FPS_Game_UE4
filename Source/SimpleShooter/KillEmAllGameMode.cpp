// Zuocheng Wang 2022


#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("A Pawn was Killed"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if(PlayerController)
    {
        EndGame(false);
    }

    //For Loop over ShooterAI in World:
        //Is not Dead?
            //return
    
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead())
        {
            return;
        }

    }

    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        //Method 1:
        
        bool bIsPlayerController = Controller->IsPlayerController();
        if(bIsPlayerWinner)
        {
            Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner);
        }
        else
        {
            Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner);
        }
        

        //method 2:
        /*
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
        */
    }
}