// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	
	UFUNCTION(BlueprintPure)
	bool IsOutOfAmmo() const;

	void ReloadGun();

	UFUNCTION(BlueprintPure)
	int GetNumberOfAmmo() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void Shoot();
	void Bomb();
	void TheForceKnockback();
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//Since the Character pitch function only take one parameter
	// we can directly call it in the call back function parameter
	//AddControllerPitchInput(float AxisValue);  we don't need void LookUp(float AxisValue);
	//void LookUp(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);


	UPROPERTY(EditAnyWhere)
	float RotationRate = 10;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnyWhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun * Gun;



};
