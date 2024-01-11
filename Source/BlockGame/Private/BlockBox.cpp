// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBox.h"

#include "BlockGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABlockBox::ABlockBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	SM_Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Block"));
	SM_Block->SetupAttachment(RootComponent); // Attach to the root component
}

// Called when the game starts or when spawned
void ABlockBox::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BlockMaterial, nullptr);
	// //
	DynMaterial->SetScalarParameterValue("Size", 3.0);
	DynMaterial->SetScalarParameterValue("DestroyAmount", 0.0);
	//
	SM_Block->SetMaterial(0,DynMaterial);
}

void ABlockBox::UpdateMaterialDestruction(float destroyAmount)
{
	Cast<UMaterialInstanceDynamic>(SM_Block->GetMaterial(0))->SetScalarParameterValue("DestroyAmount", destroyAmount);
}

// Called every frame
void ABlockBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DestroyBox(DeltaTime);
}

void ABlockBox::DestroyBox()
{
	destroyData.bLerping=true;
	UBlockGameInstance* gi = Cast<UBlockGameInstance>(UGameplayStatics::GetGameInstance(this));

	check(gi);
	gi->DeleteBox(FBlockData(TSubclassOf<ABlockBox>(GetClass()), GetActorLocation(),GetActorRotation()));
	gi->AutoSave();//Waiting for the destroyData timer to end is overkill here
}

void ABlockBox::DestroyBox(float DeltaTime)
{
	if (!destroyData.bLerping)
	{
		destroyData.LerpTimer = 0.0f;
		// destroyData.StartValue = 0.0f;
		// destroyData.EndValue = 1.0f;
	}
	if (destroyData.bLerping)
	{
		destroyData.LerpTimer += DeltaTime;

		if (destroyData.LerpTimer >= destroyData.LerpDuration)
		{
			destroyData.LerpAmount = destroyData.EndValue;
			destroyData.bLerping = false;
			Destroy();
			// Call function or perform action for finish
		}
		else
		{
			float Alpha = FMath::Clamp(destroyData.LerpTimer / destroyData.LerpDuration, 0.0f, 1.0f);
			destroyData.LerpAmount = FMath::Lerp(destroyData.StartValue, destroyData.EndValue, Alpha);
			UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(destroyData.LerpAmount));
			UpdateMaterialDestruction(destroyData.LerpAmount);
// Call function or perform action for update
		}
	}
}

UE::Math::TQuat<double> ABlockBox::GetRotation(FVector originLocation,FVector SpawnLocation)
{
	return UE::Math::TQuat(0.0,0.0,0.0,0.0);
}

