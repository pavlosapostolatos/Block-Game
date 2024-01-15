#include "Widgets/MainHud.h"

void UMyMainHud::ConstructAll()
{
	this->Construct();
	HealthWidget->Construct();
	Toolbar->ConstructAll();
}
