#pragma once

#include "CoreMinimal.h"
#include "BlockBox.h"
#include "BlockGame/BlockGameCharacter.h"
#include "Components/BoxComponent.h"
#include "BlockBoxMagma.generated.h"

UCLASS()
class BLOCKGAME_API ABlockBoxMagma : public ABlockBox
{
	GENERATED_BODY()

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UBoxComponent* CollisionBox;

protected:
	 FTimerDelegate::TMethodPtr<ABlockGameCharacter> Event = &ABlockGameCharacter::DamageByBox;
	
public:
	// Sets default values for this actor's properties
	ABlockBoxMagma();

	UFUNCTION()
	virtual void NotifyOverLap(        UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) ;

	UFUNCTION()
	void NotifyEndHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);

protected:


public:
};

