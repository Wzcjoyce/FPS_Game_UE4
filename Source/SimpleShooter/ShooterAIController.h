// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

private:
	//UPROPERTY(EditAnyWhere)
	//float AcceptanceRadius = 300;

	UPROPERTY(EditAnyWhere)
	class UBehaviorTree* AIBehavior;
	
};
