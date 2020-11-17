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

        _pRasterState->SetRasterState();   

        for (int i = 0; i < _pMaterial->GetTextures().size(); i++)
            _pMaterial->GetTextures()[i]->Bind(_pMaterial->GetShader(), i);

        DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
    }
}
