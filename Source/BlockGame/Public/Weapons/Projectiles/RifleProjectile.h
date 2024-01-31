// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "RifleProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ARifleProjectile : public AProjectile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UNiagaraSystem* HitVFX;

public:
	ARifleProjectile();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   FVector NormalImpulse, const FHitResult& Hit) override;
};
