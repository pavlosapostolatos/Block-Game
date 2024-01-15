#include "Widgets/SlotWidget.h"

void USlotWidget::SetUp(FInventory& Inventory)
{
	Icon->SetBrushFromTexture(Inventory.Icon);
	GiveAmount(Inventory.Amount);
}
