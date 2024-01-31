#include "Boxes/BlockBoxGreen.h"

ABlockBoxGreen::ABlockBoxGreen()
{
}

void ABlockBoxGreen::Interact()
{
	SM_Block->SetRelativeScale3D(0.8 * SM_Block->GetRelativeScale3D());
}
