#include "Widgets/MainHud.h"

void UMyMainHud::ConstructAll()
{
	this->Construct();
	HealthWidget->Construct();
	HeartWidget->Construct();
	Toolbar->ConstructAll();
}
