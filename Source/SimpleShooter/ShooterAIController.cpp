// Zuocheng Wang 2022


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    //APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    //SetFocus(PlayerPawn);

    
    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        // GetBlackboardComponent()->SetValueAsVector 
        // Set PlayerLocation in behavior tree to player pawn's location
        GetBlackboardComponent()->SetValueAsVector(
        TEXT("PlayerLocation"), 
        PlayerPawn->GetActorLocation());
        
        // Set StartLocation in behavior tree to AI Pawn's start location
        GetBlackboardComponent()->SetValueAsVector(
        TEXT("StartLocation"), 
        GetPawn()->GetActorLocation());

    }
    


}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    //Set the AI character to chase the Actor(player pawn)
    // second parameter is the to chase until within certain distance
    //MoveToActor(PlayerPawn, 500);

    /*
    Important **************************************************************
    AI Chasing Logic:

    IF LineOfSight
        //MoveTo Player Pawn   Default method MoveToActor(Player Pawn Actor)
        // Set Focus to Player Pawn   Default method SetFocus(Player Pawn Actor)
    Else
        //ClearFocus to Player Pawn  Default method StopMovement(EAIFocusPriority::Gameplay)
        // StopMovement  Default method StopMovement()
    */

   //Method 1 without blackboard and behavior tree
   /*

   APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

   if(LineOfSightTo(PlayerPawn))
   {
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, AcceptanceRadius);
   }
   else
   {
       ClearFocus(EAIFocusPriority::Gameplay);
       StopMovement();
   }
   */

  //method 2 using behavior tree and blackboard
  APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

  if(LineOfSightTo(PlayerPawn))
  {
    //Setting PlayerLocation
    // GetBlackboardComponent()->SetValueAsVector 
    // Set PlayerLocation in behavior tree to player pawn's location
    GetBlackboardComponent()->SetValueAsVector(
        TEXT("PlayerLocation"), 
        PlayerPawn->GetActorLocation());


    //Setting lastknown
    GetBlackboardComponent()->SetValueAsVector(
        TEXT("LastKnownPlayerLocation"), 
        PlayerPawn->GetActorLocation());

  }
  else
  {
    GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
  }

}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControllerCharacter = Cast<AShooterCharacter>(GetPawn());

    if(ControllerCharacter)
    {
        return ControllerCharacter->IsDead();
    }

    return true;
}
