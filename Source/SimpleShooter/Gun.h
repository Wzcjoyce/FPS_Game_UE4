// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();
	void PullBombTrigger();
	void PullTheForceKnockbackTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsOutofAmmo() const;

	int GetNumberOfAmmo();

	void Reload();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	//handle fire
	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* MuzzleFlash;

	//handle fire
	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* ImpactSound;



	//handle the force
	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* MuzzleTheForce;

	//handle the force sound
	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* MuzzleTheForceSound;


	
	//handle Bomb
	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* Bomb;

	//handle fire
	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* BombMuzzleSound;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* BombImpactEffect;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* BombImpactSound;


	void DrawCameraLine(FVector Location, FRotator Rotator);

	UPROPERTY(EditAnyWhere)
	float MaxGunRange = 8000;
	
	UPROPERTY(EditAnyWhere)
	float MaxBombRange = 5000;

	UPROPERTY(EditAnyWhere)
	float Damage = 10;

	UPROPERTY(EditAnyWhere)
	float BombDamage = 40;

	UPROPERTY(EditAnyWhere)
	float ForceDamage = 5;

	bool GunTrace(FHitResult &Hit, FVector& ShotDirection);
	
	AController* GetOwnerController() const;

	UPROPERTY(EditAnyWhere)
	int NumberOfAmmo;

	int MaxNumberOfAmmo = 24;

	bool OutofAmmo = false;


};
