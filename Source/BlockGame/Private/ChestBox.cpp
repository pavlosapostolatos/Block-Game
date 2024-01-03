#include "ChestBox.h"

#include "Kismet/KismetSystemLibrary.h"

AChestBox::AChestBox()
{

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	scene->SetupAttachment(SM_Block); // change location in BP

	top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	top->SetupAttachment(scene); // Attach to the box
	
	rotationData.LerpDuration = 1.0;
	rotationData.EndValue = 45.0;
	rotationData.direction = -1;
}

void AChestBox::Interact()
{
	UKismetSystemLibrary::PrintWarning("Interacted with chest");
	rotationData.bLerping = true;
	rotationData.direction=-rotationData.direction;
}

void AChestBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateTop(DeltaTime);
}

void AChestBox::RotateTop(float DeltaTime)
{
	if (!rotationData.bLerping)
	{
		// rotationData.LerpTimer = 0.0f;
		// rotationData.StartValue = 0.0f;
		// rotationData.EndValue = 1.0f;
	}
	if (rotationData.bLerping)
	{
		rotationData.LerpTimer = rotationData.LerpTimer + rotationData.direction * DeltaTime;

		if (
			(rotationData.direction == 1 && rotationData.LerpTimer >= rotationData.LerpDuration) ||
			(rotationData.direction == -1 && rotationData.LerpTimer < 0.0)
			)
		{
			// rotationData.LerpAmount = rotationData.EndValue;
			rotationData.bLerping = false;
		}
		else
		{
			float Alpha = FMath::Clamp(rotationData.LerpTimer / rotationData.LerpDuration, 0.0f, 1.0f);
			rotationData.LerpAmount = FMath::Lerp(rotationData.StartValue, rotationData.EndValue, Alpha);
			UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(rotationData.LerpAmount));
			scene->SetRelativeRotation(FRotator(rotationData.LerpAmount, 0,0));
			// Call function or perform action for update
		}
	}
}


