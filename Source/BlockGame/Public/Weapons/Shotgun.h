#pragma once
#include "Gun.h"
#include "Shotgun.generated.h"


UCLASS()
class AShotgun : public AGun
{
	GENERATED_BODY()

public:
	AShotgun();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	int Bullets = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	int Spread = 20;

	virtual void SpawnProjectile(FVector SpawnLocation) override;
};
