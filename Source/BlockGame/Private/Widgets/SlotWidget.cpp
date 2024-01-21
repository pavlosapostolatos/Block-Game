#include "Widgets/SlotWidget.h"

void USlotWidget::SetUp(FInventory& Inventory)
{
	Icon->SetBrushFromTexture(Inventory.Icon);
	if(Inventory.Type != InventoryType::BLOCK)
	{
		HideAmount();
	}
	else
	{
		GiveAmount(Inventory.Amount);
	}
}
