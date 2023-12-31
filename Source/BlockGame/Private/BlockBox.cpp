// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\BlockBox.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABlockBox::ABlockBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateDestroyAmount(DeltaTime);
}

void ABlockBox::DestroyBox()
{
	destroyData.bLerping=true;
}


void ABlockBox::UpdateDestroyAmount(float DeltaTime)
{
	if (!destroyData.bLerping)
	{
		destroyData.LerpTimer = 0.0f;
		destroyData.StartValue = 0.0f;
		destroyData.EndValue = 1.0f;
	}

	if (destroyData.bLerping)
	{
		destroyData.LerpTimer += DeltaTime;

		if (destroyData.LerpTimer >= destroyData.LerpDuration)
		{
			destroyData.DestroyAmount = destroyData.EndValue;
			destroyData.bLerping = false;
			Destroy();
			// Call function or perform action for finish
		}
		else
		{
			float Alpha = FMath::Clamp(destroyData.LerpTimer / destroyData.LerpDuration, 0.0f, 1.0f);
			destroyData.DestroyAmount = FMath::Lerp(destroyData.StartValue, destroyData.EndValue, Alpha);
			UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(destroyData.DestroyAmount));
// Call function or perform action for update
		}
	}
}

