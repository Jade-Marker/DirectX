#include "SelectionHide.h"

void SelectionHide::OnSelected()
{
	_pParent->GetTransform().Scale = Vector3D(0, 0, 0);
}
