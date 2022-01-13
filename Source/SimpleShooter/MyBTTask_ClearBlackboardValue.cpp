// Zuocheng Wang 2022


#include "MyBTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

//Constructor with a Blackboard Node name
//Behavior Tree can get this Node by setting the Node Name
UMyBTTask_ClearBlackboardValue::UMyBTTask_ClearBlackboardValue()
{
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UMyBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 * NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Return a FName
    //GetSelectedBlackboardKey()

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}