#include "Renderer.h"

void Renderer::Start()
{
    _pMesh = _parent->GetComponent<Mesh>();
    _pMaterial = _parent->GetComponent<Material>();
    _pRasterState = _parent->GetComponent<RasterState>();
    _pRenderingBuffers = _parent->GetComponent<RenderingBuffers>();
}

void Renderer::Draw()
{
    if (_pMesh && _pMaterial && _pRasterState && _pRenderingBuffers)
    {
        _pRenderingBuffers->BindBuffers(_pMaterial->GetShader());

        _pMaterial->GetShader()->SetShader();
        _pMaterial->GetShader()->SetInputLayout();

        for (int i = 0; i < _pMaterial->GetTextures().size(); i++)
            _pMaterial->GetTextures()[i]->Bind(_pMaterial->GetShader(), i);

        if (_pRasterState->IsWireframe())
        {
            _pRasterState->WireframeState();
            DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
        }
        else
        {
            if (!_pMaterial->IsTransparent())
                DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
            else
            {
                _pRasterState->FrontFaceCullState();
                DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);

                _pRasterState->BackFaceCullState();
                DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
            }
        }
    }
}
