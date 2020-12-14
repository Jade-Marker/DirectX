#include "Renderer.h"

void Renderer::BindTexture(Texture* texture, int slot)
{
    if (texture)
        texture->Bind(_pMaterial->GetShader(), slot);
    else
       Texture::GetDefault()->Bind(_pMaterial->GetShader(), slot);
}

void Renderer::Start()
{
    _pMesh = _pParent->GetComponent<Mesh>();
    _pMaterial = _pParent->GetComponent<Material>();
    _pRasterState = _pParent->GetComponent<RasterState>();
    _pRenderingBuffers = _pParent->GetComponent<RenderingBuffers>();

    if (dynamic_cast<SkyboxRasterState*>(_pRasterState) != nullptr)
        _isSkybox = true;
}

void Renderer::Draw()
{
    if (_pMesh && _pMaterial && _pRasterState && _pRenderingBuffers)
    {
        _pRenderingBuffers->BindBuffers(_pMaterial->GetShader());

        _pMaterial->GetShader()->SetShader();
        _pMaterial->GetShader()->SetInputLayout();

        BindTexture(_pMaterial->GetDiffuseTexture(), cDiffuseSlot);
        BindTexture(_pMaterial->GetAmbientTexture(), cAmbientSlot);
        BindTexture(_pMaterial->GetSpecularTexture(), cSpecularSlot);

        if (_pRasterState->IsWireframe())
        {
            _pRasterState->WireframeState();
            DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
        }
        else
        {
            if (!_pMaterial->IsTransparent())
            {
                if (_isSkybox)
                    ((SkyboxRasterState*)_pRasterState)->SkyboxState();
                else
                    _pRasterState->BackFaceCullState();

                DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
            }
            else
            {
                //Draw the back faces then the front faces so that both are seen in transparent objects

                _pRasterState->FrontFaceCullState();
                DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);

                _pRasterState->BackFaceCullState();
                DeviceManager::GetContext()->DrawIndexed(_pMesh->GetIndexCount(), 0, 0);
            }
        }
    }
}
