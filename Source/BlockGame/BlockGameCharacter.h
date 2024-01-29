// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Structs/Inventory.h"
#include "Widgets/MainHud.h"
#include "BlockGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ABlockGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widget, meta=(AllowPrivateAccess = "true"))
	FVector EquippedWeaponLocation = FVector(12, -5, -161);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widget, meta=(AllowPrivateAccess = "true"))
	FVector SheathWeaponLocation = FVector(-26, 4, -182);

	LerpData EquipLerpData;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	UStaticMeshComponent* BlockOutline;

	UPROPERTY(VisibleDefaultsOnly, Category=Widget)
	UMyMainHud* MainHud;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* BuildBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DeleteBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widget, meta=(AllowPrivateAccess = "true"))
	int health = 100;

	uint8 selectedBox : 3 = 0;

	void Select();

	void SelectKey(FKey PressedKey)
	{
		if (EquipLerpData.bLerping) return;
		// Do something with the pressed key
		FString KeyName = PressedKey.GetDisplayName().ToString();
		selectedBox = FCString::Atoi(*KeyName) - 1;
		Select();
	}

	void selectRight()
	{
		if (EquipLerpData.bLerping) return;
		selectedBox = (selectedBox + 1) % Inventory.Num();
		Select();
	};


	void selectLeft()
	{
		if (EquipLerpData.bLerping) return;
		selectedBox = (selectedBox - 1 + Inventory.Num()) % Inventory.Num();
		Select();
	};

	void LerpWeapon(float DeltaTime);

public:
	ABlockGameCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable)
	void Heal();

	UFUNCTION(BlueprintCallable)
	void Damage();

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	virtual void Tick(float DeltaTime) override;
	bool GetLineTraceFromCharacter(FHitResult& hit) const;
	void SpawnStaticMesh(const FTransform& SpawnTransform) const;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void SaveGame();
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void EquipWeapon();
	void FinishEquipWeapon();
	void FinishUnEquipWeapon();
	void SwitchWeapon();

	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/

	//DEPRECATED
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* boxToSpawn;

	//DEPRECATED
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBlueprint* actorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventory> Inventory;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* test; //the correct way to do this shit

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* SM_BlockOutline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTP_WeaponComponent* WeaponComponent;

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widget)
	TSubclassOf<UMyMainHud> C_MainHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widget)
	TSubclassOf<UUserWidget> C_DeathHud;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnBox();

	UFUNCTION(BlueprintCallable)
	void DeleteBox();
};
