// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlockGameCharacter.h"

#include "BlockBoxInteractive.h"
#include "BlockGameInstance.h"
#include "BlockBox.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/Utils.h"
#include "MyHealthWidget.h"
#include "TP_WeaponComponent.h"
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ABlockGameCharacter

ABlockGameCharacter::ABlockGameCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	EquipLerpData.LerpDuration = 0.5f;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(SheathWeaponLocation);
	// Mesh1P->SetRelativeRotation(FRotator(5, 2, 20));

	BlockOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockOutline"));
	BlockOutline->SetupAttachment(GetCapsuleComponent());
	BlockOutline->SetVisibility(false);
	BlockOutline->bCastDynamicShadow = false;
	BlockOutline->CastShadow = false;
	BlockOutline->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCharacterMovement()->MaxStepHeight = 51;
}

void ABlockGameCharacter::BeginPlay()
{
	BlockOutline->SetStaticMesh(SM_BlockOutline);

	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	MainHud = CreateWidget<UMyMainHud>(GetWorld(), C_MainHud);
	MainHud->ConstructAll();
	MainHud->GetHealthWidget()->SetHealth(health);
	MainHud->GetHeartWidget()->SetHealth(health);
	MainHud->GetToolbar()->SetUp(Inventory);
	MainHud->AddToViewport();

	SelectKey(EKeys::One);
}

//////////////////////////////////////////////////////////////////////////// Input

void ABlockGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABlockGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABlockGameCharacter::Look);


		//Custom actions. To register I put IMC_PlayerControls to Character's Input->Default Mapping Context in the blueprint
		EnhancedInputComponent->BindAction(BuildBlock, ETriggerEvent::Triggered, this, &ABlockGameCharacter::SpawnBox);
		//This works because i have set IMC_PlayerControls key to have a PRESSED trigger
		//Another solution would be not to set that and use ETriggerEvent::Started
		EnhancedInputComponent->BindAction(DeleteBlock, ETriggerEvent::Triggered, this,
		                                   &ABlockGameCharacter::DeleteBox);


		InputComponent->BindKey(EKeys::One, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::Two, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::Three, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::Four, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::Five, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::Six, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::Seven, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SelectKey);
		InputComponent->BindKey(EKeys::MouseScrollDown, EInputEvent::IE_Pressed, this,
		                        &ABlockGameCharacter::selectRight);
		InputComponent->BindKey(EKeys::MouseScrollUp, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::selectLeft);
		InputComponent->BindKey(EKeys::Gamepad_DPad_Left, EInputEvent::IE_Pressed, this,
		                        &ABlockGameCharacter::selectLeft);
		InputComponent->BindKey(EKeys::Gamepad_DPad_Left, EInputEvent::IE_Pressed, this,
		                        &ABlockGameCharacter::selectRight);
		InputComponent->BindKey(EKeys::Z, EInputEvent::IE_Pressed, this, &ABlockGameCharacter::SaveGame);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ABlockGameCharacter::Select()
{
	//BLOCK MODE TO WEAPON MODE
	if (WeaponActor == nullptr && Inventory[selectedBox].Type == InventoryType::WEAPON)
	{
		EquipWeapon();
		// EquipWeapon();
	}

	// WEAPON MODE TO BLOCK MODE
	if (WeaponActor != nullptr && Inventory[selectedBox].Type == InventoryType::BLOCK)
	{
		// UnEquipWeapon();
		EquipLerpData.direction = -1;
		EquipLerpData.bLerping = true;
		EquipLerpData.FinishFunction.BindUObject(this, &ABlockGameCharacter::FinishUnEquipWeapon);
	}

	// WEAPON MODE TO WEAPON MODE
	if (WeaponActor != nullptr && Inventory[selectedBox].Type == InventoryType::WEAPON)
	{
		EquipLerpData.direction = -1;
		EquipLerpData.bLerping = true;
		EquipLerpData.FinishFunction.BindUObject(this, &ABlockGameCharacter::SwitchWeapon);
	}

	MainHud->GetToolbar()->ActivateSlot(selectedBox);
}

void ABlockGameCharacter::EquipWeapon()
{
	EquipLerpData.direction = 1;
	EquipLerpData.bLerping = true;
	EquipLerpData.FinishFunction.Unbind();
	FinishEquipWeapon();
}

void ABlockGameCharacter::FinishEquipWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	WeaponActor = GetWorld()->SpawnActor<AGun>(Inventory[selectedBox].C_WeaponActor, SpawnParameters);

	WeaponActor->AttachWeapon(this);
	// switch bHasRifle so the animation blueprint can switch to another animation set
}

void ABlockGameCharacter::FinishUnEquipWeapon()
{
	WeaponActor->Destroy();
	WeaponActor = nullptr;
	bHasRifle = false;
	GetMesh1P()->SetVisibility(false);
}


void ABlockGameCharacter::SwitchWeapon()
{
	FinishUnEquipWeapon();
	EquipWeapon();
}

void ABlockGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ABlockGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABlockGameCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ABlockGameCharacter::GetHasRifle()
{
	return bHasRifle;
}

void ABlockGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult hit;
	if (GetLineTraceFromCharacter(hit) && Cast<ABlockBox>(hit.GetActor()))
	{
		// BlockOutline->SetWorldLocation(hit.GetActor()->GetActorLocation());
		BlockOutline->SetWorldTransform(FTransform(hit.GetActor()->GetActorLocation()));
		BlockOutline->SetVisibility(true);
	}
	else
	{
		BlockOutline->SetVisibility(false);
	}

	LerpWeapon(DeltaTime);
}

bool ABlockGameCharacter::GetLineTraceFromCharacter(FHitResult& hit) const
//Could go in a lib file
{
	APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	// FVector4d location = GetActorLocation();//the same??
	// location.w
	FVector forward = cameraManager->GetActorForwardVector();
	FVector location = cameraManager->GetCameraLocation();
	FVector end = location + forward * 50000;
	TArray<AActor*> ignore;
	return UKismetSystemLibrary::LineTraceSingle(this, location, end, TraceTypeQuery1,
	                                             0, ignore, EDrawDebugTrace::None, hit, true);
}

void ABlockGameCharacter::SpawnBox()
{
	FHitResult hit;
	bool collided = GetLineTraceFromCharacter(hit);

	if (collided)
	{
		UKismetSystemLibrary::PrintString(this, hit.GetActor()->GetActorNameOrLabel());
		FTransform SpawnTransform = UE::Math::TTransform(hit.ImpactPoint); //LOCATION works too

		SpawnTransform.SetLocation(SpawnTransform.GetLocation().GridSnap(100));
		//snaps blocks together. kinda hacky. make sure the dimensions of the box you are spawning is 100 too

		if (ABlockBoxInteractive* interactiveBox = Cast<ABlockBoxInteractive>(hit.GetActor()))
		{
			interactiveBox->Interact();
		}
		else if (Inventory.IsEmpty())
		{
			SpawnStaticMesh(SpawnTransform);
		}
		else
		{
			if (checkBoxOverlap(this, SpawnTransform)) return;
			if (!Inventory[selectedBox].Amount) return;
			if (Inventory[selectedBox].Type != InventoryType::BLOCK) return;

			ABlockBox* cube = Cast<ABlockBox>(Inventory[selectedBox].C_Box->GetDefaultObject());

			SpawnTransform.SetRotation(cube->GetRotation(GetCapsuleComponent()->GetComponentLocation(),
			                                             SpawnTransform.GetLocation()));

			cube = GetWorld()->SpawnActor<ABlockBox>(Inventory[selectedBox].C_Box, SpawnTransform);
			cube->FinishSpawning(SpawnTransform);

			UBlockGameInstance* gi = Cast<UBlockGameInstance>(UGameplayStatics::GetGameInstance(this));

			check(gi);
			gi->AddBox(FBlockData(Inventory[selectedBox].C_Box, SpawnTransform.GetLocation(),
			                      SpawnTransform.Rotator()));
			MainHud->GetToolbar()->SetSlotAmount(selectedBox, --Inventory[selectedBox].Amount);
			gi->AutoSave();
		}
	}
}

void ABlockGameCharacter::SpawnStaticMesh(const FTransform& SpawnTransform) const
{
	AStaticMeshActor* cube = GetWorld()->SpawnActorDeferred<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(), SpawnTransform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::Undefined);
	if (cube)
	{
		// Set the static mesh component for the spawned actor
		UStaticMeshComponent* StaticMeshComponent = cube->GetStaticMeshComponent();
		StaticMeshComponent->SetMobility(EComponentMobility::Movable);
		if (StaticMeshComponent)
		{
			if (!boxToSpawn)
				// UStaticMesh* YourStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/Meshes/SM_Block.SM_Block'"));
				UKismetSystemLibrary::PrintWarning("Box to spawn is not set");
			StaticMeshComponent->SetStaticMesh(boxToSpawn);
		}

		// Finish spawning the actor
		cube->FinishSpawning(SpawnTransform);
	}
}

void ABlockGameCharacter::DeleteBox()
{
	FHitResult hit;
	const bool collided = GetLineTraceFromCharacter(hit);

	// if (collided && hit.GetActor()->GetClass() == BlueprintActorToSpawn )
	// {
	// 	UKismetSystemLibrary::PrintString(this, hit.GetActor()->GetActorNameOrLabel());
	// 	hit.GetActor()->Destroy();
	// }
	if (collided && Cast<ABlockBox>(hit.GetActor()))
	{
		UKismetSystemLibrary::PrintString(this, hit.GetActor()->GetActorNameOrLabel());

		for (int i = 0; i < Inventory.Num(); ++i)
		{
			if (hit.GetActor()->GetClass() == Inventory[i].C_Box)
			{
				MainHud->GetToolbar()->SetSlotAmount(i, ++Inventory[i].Amount);
			}
		}

		Cast<ABlockBox>(hit.GetActor())->DestroyBox();
	}
}


void ABlockGameCharacter::SaveGame()
{
	Cast<UBlockGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveGame();
}

void ABlockGameCharacter::Heal()
{
	health++;
	MainHud->GetHealthWidget()->SetHealth(health);
	MainHud->GetHeartWidget()->SetHealth(health);
	UKismetSystemLibrary::PrintString(this, "health: " + FString::FromInt(health));
};

void ABlockGameCharacter::Damage()
{
	health -= 11;
	if (health <= 0)
	{
		DisableInput(UGameplayStatics::GetPlayerController(this, 0));
		UUserWidget* DeathWidget = CreateWidget<UUserWidget>(GetWorld(), C_DeathHud);
		DeathWidget->AddToViewport();
	}

	MainHud->GetHealthWidget()->SetHealth(health);
	MainHud->GetHeartWidget()->SetHealth(health);
	UKismetSystemLibrary::PrintString(this, "health: " + FString::FromInt(health));
};

void ABlockGameCharacter::LerpWeapon(float DeltaTime)
{
	if (!EquipLerpData.bLerping)
	{
		// EquipLerpData.LerpTimer = 0.0f;
		// EquipLerpData.StartValue = 0.0f;
		// EquipLerpData.EndValue = 1.0f;
	}
	if (EquipLerpData.bLerping)
	{
		EquipLerpData.LerpTimer = EquipLerpData.LerpTimer + EquipLerpData.direction * DeltaTime;

		if (
			(EquipLerpData.direction == 1 && EquipLerpData.LerpTimer >= EquipLerpData.LerpDuration) ||
			(EquipLerpData.direction == -1 && EquipLerpData.LerpTimer < 0.0)
		)
		{
			// EquipLerpData.LerpAmount = EquipLerpData.EndValue;
			EquipLerpData.bLerping = false;
			EquipLerpData.FinishFunction.ExecuteIfBound();
		}
		else
		{
			float Alpha = FMath::Clamp(EquipLerpData.LerpTimer / EquipLerpData.LerpDuration, 0.0f, 1.0f);
			EquipLerpData.LerpAmount = FMath::Lerp(EquipLerpData.StartValue, EquipLerpData.EndValue, Alpha);
			UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(EquipLerpData.LerpAmount));
			Mesh1P->SetRelativeLocation(FMath::Lerp(SheathWeaponLocation, EquippedWeaponLocation,
			                                        EquipLerpData.LerpAmount));
			// Call function or perform action for update
		}
	}
}
