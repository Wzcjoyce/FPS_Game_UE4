// Zuocheng Wang 2022


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"

#include "ShooterCharacter.h"



// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	NumberOfAmmo = MaxNumberOfAmmo;
}

void AGun::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("You shot!"));

	if(NumberOfAmmo > 0)
	{

		NumberOfAmmo -= 1;

		if(MuzzleFlash)
		{
			//This particle effect is to attach the effect to a socket in gun skeleton
			// socket name is MuzzleFlashSocket
			UGameplayStatics::SpawnEmitterAttached(
			MuzzleFlash,
			Mesh,
			TEXT("MuzzleFlashSocket")
			);
			
			UGameplayStatics::SpawnSoundAttached(
				MuzzleSound,
				Mesh,
				TEXT("MuzzleFlashSocket")
			);


			FHitResult Hit;
			FVector ShotDirection;
			bool bSuccess = GunTrace(Hit, ShotDirection);

			if(bSuccess)
			{
				//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
				UGameplayStatics::SpawnEmitterAtLocation(
					GetWorld(),
					ImpactEffect,
					Hit.Location,
					ShotDirection.Rotation());

				UGameplayStatics::PlaySoundAtLocation(
					GetWorld(),
					ImpactSound,
					Hit.Location);


				AActor* HitActor = Hit.GetActor();

				if(HitActor != nullptr)
				{
					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

					HitActor->TakeDamage(
						Damage, 
						DamageEvent,
						GetOwnerController(),
						this);
				}
		

			}
			//DrawCameraLine(Location, Rotation);
		}
	}
	else
	{
		OutofAmmo = true;
	}

}

void AGun::PullBombTrigger()
{
	if(MuzzleFlash)
	{
		//This particle effect is to attach the effect to a socket in gun skeleton
		// socket name is MuzzleFlashSocket
		UGameplayStatics::SpawnEmitterAttached(
		Bomb,
		Mesh,
		TEXT("MuzzleFlashSocket")
		);

		UGameplayStatics::SpawnSoundAttached(
			BombMuzzleSound,
			Mesh,
			TEXT("MuzzleFlashSocket")
		);

		FHitResult Hit;
		FVector ShotDirection;
		bool bSuccess = GunTrace(Hit, ShotDirection);

		if(bSuccess)
		{
			//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				BombImpactEffect,
				Hit.Location,
				ShotDirection.Rotation());
			
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				BombImpactSound,
				Hit.Location);

			
			AActor* HitActor = Hit.GetActor();

			if(HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(BombDamage, Hit, ShotDirection, nullptr);

				HitActor->TakeDamage(
					BombDamage, 
					DamageEvent,
					GetOwnerController(),
					this);

			}
		}
		//DrawCameraLine(Location, Rotation);
	}


}


void AGun::PullTheForceKnockbackTrigger()
{
	if(MuzzleFlash)
	{
		//This particle effect is to attach the effect to a socket in gun skeleton
		// socket name is MuzzleFlashSocket
		UGameplayStatics::SpawnEmitterAttached(
		MuzzleTheForce,
		Mesh,
		TEXT("MuzzleFlashSocket")
		);

		UGameplayStatics::SpawnSoundAttached(
			MuzzleTheForceSound,
			Mesh,
			TEXT("MuzzleFlashSocket")
		);

	
	TArray<FHitResult> OutHits;
	FVector MyLocation = GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(600.f);
	
	//DrawDebugSphere(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);

	bool isHit = GetWorld()->SweepMultiByChannel(
		OutHits, 
		MyLocation,
		MyLocation,
		FQuat::Identity,
		ECC_WorldStatic,
		MyColSphere);

		if(isHit)
		{
			for(auto & Hit: OutHits)
			{
				AActor* HitActor = Hit.GetActor();

				if(HitActor != nullptr)
				{
					FPointDamageEvent DamageEvent(ForceDamage, Hit, MyLocation, nullptr);

					if(HitActor != GetOwner())
					{
						HitActor->TakeDamage(
							ForceDamage, 
							DamageEvent,
							GetOwnerController(),
							this);
						
						
						UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(HitActor->GetRootComponent());
						if(MeshComp)
						{
							MeshComp->AddRadialImpulse(MyLocation, 500.f, 2000.f, ERadialImpulseFalloff::RIF_Constant, true);
						}

					}
				}
			
			}

		}
		//DrawCameraLine(Location, Rotation);
	}


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::DrawCameraLine(FVector Location, FRotator Rotator)
{
	DrawDebugCamera(
		GetWorld(),
		Location,
		Rotator,
		90,
		2,
		FColor::Red,
		true
	);
}

bool AGun::GunTrace(FHitResult &Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();

	if(OwnerController == nullptr) 
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxGunRange;

	FCollisionQueryParams Params;

	// make sure the shoot(line trace) ignore  character owner 
	// preventing shooting self
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location, 
		End, 
		ECollisionChannel::ECC_GameTraceChannel11,
		Params);
}

AController* AGun::GetOwnerController() const
{
	APawn * OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

bool AGun::IsOutofAmmo() const
{
	return OutofAmmo;
}

int AGun::GetNumberOfAmmo()
{
	return NumberOfAmmo;
}


void AGun::Reload()
{
	NumberOfAmmo = MaxNumberOfAmmo;
	OutofAmmo = false;
	//UE_LOG(LogTemp, Warning, TEXT("Ammo: %d"), NumberOfAmmo);

}




