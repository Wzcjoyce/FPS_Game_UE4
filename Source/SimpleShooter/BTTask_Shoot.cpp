// Zuocheng Wang 2022


#include "BTTask_Shoot.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 * NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // get the AI Controlled ShooterCharacter
    AShooterCharacter* Character = (AShooterCharacter*)(OwnerComp.GetAIOwner()->GetPawn());

    if(Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    //Let the Character shoot
    Character->Shoot();
    
    return EBTNodeResult::Succeeded;
}