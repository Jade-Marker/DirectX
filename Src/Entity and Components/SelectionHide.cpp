#include "SelectionHide.h"

void SelectionHide::OnSelected()
{
	_pParent->GetTransform().Scale = XMFLOAT3(0, 0, 0);
}
