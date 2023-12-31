// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlockGameCharacter.h"

#include "Public\BlockBox.h"
#include "BlockGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "K2Node_SpawnActor.h"
#include "Components/TimelineComponent.h"
#include "Engine/LocalPlayer.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ABlockGameCharacter

ABlockGameCharacter::ABlockGameCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

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
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void ABlockGameCharacter::BeginPlay()
{
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
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
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


void ABlockGameCharacter::GetLineTraceFromCharacter(FHitResult& hit, bool& collided) //Could go in a lib file
{
	APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	// FVector4d location = GetActorLocation();//the same??
	// location.w
	FVector forward = cameraManager->GetActorForwardVector();
	FVector location = cameraManager->GetCameraLocation();
	FVector end = location + forward * 50000;
	TArray<AActor*> ignore;
	collided = UKismetSystemLibrary::LineTraceSingle(this, location, end, TraceTypeQuery1,
	                                                 0, ignore, EDrawDebugTrace::Persistent, hit, true);
}

void ABlockGameCharacter::SpawnBox()
{
	FHitResult hit;
	bool collided;
	GetLineTraceFromCharacter(hit, collided);

	if (collided)
	{
		UKismetSystemLibrary::PrintString(this, hit.GetActor()->GetActorNameOrLabel());
		FTransform SpawnTransform = UE::Math::TTransform(hit.ImpactPoint); //LOCATION works too

		SpawnTransform.SetLocation(SpawnTransform.GetLocation().GridSnap(100));
		//snaps blocks together. kinda hacky. make sure the dimensions of the box you are spawning is 100 too

		if (!BlueprintActorToSpawn)
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
		else
		{
			AActor* cube = GetWorld()->SpawnActor<AActor>(BlueprintActorToSpawn, SpawnTransform);
			cube->FinishSpawning(SpawnTransform);
		}
	}
}

void ABlockGameCharacter::DeleteBox()
{
	FHitResult hit;
	bool collided;
	GetLineTraceFromCharacter(hit, collided);

	// if (collided && hit.GetActor()->GetClass() == BlueprintActorToSpawn )
	// {
	// 	UKismetSystemLibrary::PrintString(this, hit.GetActor()->GetActorNameOrLabel());
	// 	hit.GetActor()->Destroy();
	// }
	if (collided && Cast<ABlockBox>(hit.GetActor()))
	{
		UKismetSystemLibrary::PrintString(this, hit.GetActor()->GetActorNameOrLabel());
		Cast<ABlockBox>(hit.GetActor())->DestroyBox();
	}
}
