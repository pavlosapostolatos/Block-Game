// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../BlockGameProjectile.h"
#include "Components/ArrowComponent.h"
#include "Gun.generated.h"

class ABlockGameCharacter;  // Forward declaration

UCLASS()
class BLOCKGAME_API AGun : public AActor
{
	GENERATED_BODY()
public:

	/** The Character holding this weapon*/
	ABlockGameCharacter* Character;

	// Sets default values for this actor's properties
	AGun();
	
	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(ABlockGameCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	UStaticMeshComponent* GunMesh;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABlockGameProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;
	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Logic, meta=(AllowPrivateAccess = "true"))
	float FireRateSeconds = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Logic, meta=(AllowPrivateAccess = "true"))
	float LastFireSeconds = 0;
};
