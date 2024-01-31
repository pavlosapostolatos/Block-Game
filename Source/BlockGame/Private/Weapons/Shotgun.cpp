#include "Weapons/Shotgun.h"

#include "BlockGame//BlockGameCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AShotgun::AShotgun()
{
	FireRateSeconds = 1.5;
}

void AShotgun::SpawnProjectile(const FVector SpawnLocation)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		for (int i = 0; i < Bullets; ++i)
		{
			FVector RandomSpread = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(SpawnRotation.Vector(), Spread);
			// Spawn the projectile at the muzzle
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, RandomSpread.Rotation(), ActorSpawnParams);
		}
	}
}
