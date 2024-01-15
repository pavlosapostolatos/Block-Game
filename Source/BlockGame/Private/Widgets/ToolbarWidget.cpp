#include "Widgets/ToolbarWidget.h"

void UToolbarWidget::ActivateSlot(int Index)
{
	ActiveSlot->DeactivateSlot();
	ActiveSlot = Slots[Index];
	ActiveSlot->ActivateSlot();
}

void UToolbarWidget::SetUp(TArray<FInventory>& Inventory)
{
	for (int i = 0; i < Slots.Num(); ++i)
	{
		Slots[i]->SetUp(Inventory[i]);
	}
}
