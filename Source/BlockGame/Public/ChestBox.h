#pragma once

#include "CoreMinimal.h"
#include "BlockBoxInteractive.h"
#include "GameFramework/Actor.h"
#include "ChestBox.generated.h"

UCLASS()
class BLOCKGAME_API AChestBox : public ABlockBoxInteractive //maybe abstract
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* top;

	UPROPERTY(EditAnywhere)
	USceneComponent* scene;

	LerpData rotationData;

public:
	// Sets default values for this actor's properties

protected:
	virtual void BeginPlay() override;


public:
	AChestBox();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;

	UFUNCTION(BlueprintCallable)
	void RotateTop(float DeltaTime);

	virtual UE::Math::TQuat<double> GetRotation(FVector originLocation,FVector SpawnLocation) override;
};
