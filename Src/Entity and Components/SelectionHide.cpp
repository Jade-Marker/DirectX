#include "SelectionHide.h"

void SelectionHide::OnSelected()
{
	_parent->GetTransform().Scale = XMFLOAT3(0, 0, 0);
}
