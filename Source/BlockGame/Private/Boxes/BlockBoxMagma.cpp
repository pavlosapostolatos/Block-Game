#include "Boxes/BlockBoxMagma.h"

#include "BlockGame/BlockGameCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ABlockBoxMagma::ABlockBoxMagma()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("Collision Box"));
	CollisionBox->SetupAttachment(SM_Block); // Attach to the root component

	CollisionBox->SetRelativeScale3D(FVector(1.1f, 1.1f, 1.7f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABlockBoxMagma::NotifyOverLap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABlockBoxMagma::NotifyEndHit);

}

void ABlockBoxMagma::NotifyOverLap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// Handle the overlap event here
	// Create a delegate to your function
	ABlockGameCharacter* Character = Cast<ABlockGameCharacter>(OtherActor);
	if(Character == nullptr)
	{
		return;
	}

	// FTimerDelegate TimerDelegate;
	// TimerDelegate.BindUFunction(Character, FName("Damage"));

	// Set the timer with the specified delay and the delegate
	// GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 3, false);
	GetWorldTimerManager().SetTimer(TimerHandle, Character, event, 1, true);

}

void ABlockBoxMagma::NotifyEndHit(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	// Handle the overlap event here
	// Create a delegate to your function
	ABlockGameCharacter* Character = Cast<ABlockGameCharacter>(OtherActor);
	if(Character == nullptr)
	{
		return;
	}
	//
	// FTimerDelegate TimerDelegate;
	// TimerDelegate.BindUFunction(Character, FName("Damage"));

	// Set the timer with the specified delay and the delegate
	// GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 3, false);
	GetWorldTimerManager().ClearTimer( TimerHandle );		

}