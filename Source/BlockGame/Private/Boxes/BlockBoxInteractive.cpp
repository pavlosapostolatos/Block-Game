#include "Boxes/BlockBoxInteractive.h"

#include "Kismet/KismetSystemLibrary.h"

ABlockBoxInteractive::ABlockBoxInteractive()
{
}

void ABlockBoxInteractive::Interact()
{
	UKismetSystemLibrary::PrintWarning("Interacted with box");
}
