// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> HUDClass;


	UPROPERTY(EditAnyWhere)
	float LoseRestartDelay = 5.f;

	UPROPERTY(EditAnyWhere)
	float WinRestartDelay = 30.f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnyWhere)
	UUserWidget *HUD;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
