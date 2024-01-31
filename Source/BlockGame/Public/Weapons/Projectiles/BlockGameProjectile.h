// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "BlockGameProjectile.generated.h"

UCLASS(config=Game)
class ABlockGameProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	ABlockGameProjectile();

	/** called when projectile hits something */
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					   FVector NormalImpulse, const FHitResult& Hit) override;
};

