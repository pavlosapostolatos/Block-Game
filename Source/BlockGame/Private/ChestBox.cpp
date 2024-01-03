#include "ChestBox.h"

#include "Kismet/KismetSystemLibrary.h"

AChestBox::AChestBox()
{
}

void AChestBox::Interact()
{
	UKismetSystemLibrary::PrintWarning("Interacted with chest");
}

