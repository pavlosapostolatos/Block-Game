#include "Widgets/ToolbarWidget.h"

void UToolbarWidget::ActivateSlot(int Index)
{
	ActiveSlot->DeactivateSlot();
	ActiveSlot = Slots[Index];
	ActiveSlot->ActivateSlot();
}
