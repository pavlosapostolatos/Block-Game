#include "Widgets/ToolbarWidget.h"

void UToolbarWidget::ConstructAll()
{
	this->Construct();
	for (auto Element : Slots)
	{
		Element->Construct();
	}
}

void UToolbarWidget::ActivateSlot(int Index)
{
	ActiveSlot->DeactivateSlot();
	ActiveSlot = Slots[Index];
	ActiveSlot->ActivateSlot();
}

void UToolbarWidget::SetUp(TArray<FInventory>& Inventory)
{
	const int Limit = std::min(Slots.Num(), Inventory.Num());
	for (int i = 0; i < Limit; ++i)
	{
		Slots[i]->SetUp(Inventory[i]);
	}
}
