// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "BlockGame/BlockGameCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Projectiles/Projectile.h"

// Sets default values
ADrone::ADrone()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("BulletHitBox"));
	CollisionComp->SetupAttachment(GetMesh());
	CollisionComp->OnComponentHit.AddDynamic(this, &ADrone::OnHit);

	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetupAttachment(GetMesh());
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ADrone::OnOverlap);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// set up a notification for when this component hits something blocking
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();

	int i = -1;
	for (UMaterialInterface* MI : GetMesh()->GetMaterials()) //only need the first one
	{
		i++;
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MI, nullptr);
		GetMesh()->SetMaterial(i, DynMaterial);
	}
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Destruct(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ADrone::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                   FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && Cast<AProjectile>(OtherActor))
	{
		DestroyData.bLerping = true;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// dunno why the sensei did not move the entire capsule component and the mesh with it because it's a child
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetMesh()->AddImpulse(Hit.Normal * 1500, NAME_None, true);
	}
}

void ADrone::Destruct(float DeltaTime)
{
	if (!DestroyData.bLerping)
	{
		DestroyData.LerpTimer = 0.0f;
		// DestroyData.StartValue = 0.0f;
		// DestroyData.EndValue = 1.0f;
	}
	if (DestroyData.bLerping)
	{
		DestroyData.LerpTimer += DeltaTime;

		if (DestroyData.LerpTimer >= DestroyData.LerpDuration)
		{
			DestroyData.LerpAmount = DestroyData.EndValue;
			DestroyData.bLerping = false;

			Destroy();
			// Call function or perform action for finish
		}
		else
		{
			float Alpha = FMath::Clamp(DestroyData.LerpTimer / DestroyData.LerpDuration, 0.0f, 1.0f);
			DestroyData.LerpAmount = FMath::Lerp(DestroyData.StartValue, DestroyData.EndValue, Alpha);
			UpdateMaterialDestruction(DestroyData.LerpAmount);
			// Call function or perform action for update
		}
	}
}

void ADrone::UpdateMaterialDestruction(float destroyAmount)
{
	for (UMaterialInterface* MI : GetMesh()->GetMaterials())
		Cast<UMaterialInstanceDynamic>(MI)->SetScalarParameterValue("DissolveAmount", destroyAmount);
}

void ADrone::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ABlockGameCharacter* Character = Cast<ABlockGameCharacter>(OtherActor);
	if (!Character)
		return;

	Character->Damage(25);

	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticles, GetCapsuleComponent()->GetComponentLocation(),
	                                         FRotator::ZeroRotator, FVector::One(), true, EPSCPoolMethod::None, true);
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetCapsuleComponent()->GetComponentLocation(), 0.25f);

	Destroy();
}


void ADrone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
		return;
	Super::EndPlay(EndPlayReason);
	DeathDelegate.Broadcast();
	// Cast<ABlockGameGameMode>(UGameplayStatics::GetGameMode(this))->DroneDeathListener();
}
