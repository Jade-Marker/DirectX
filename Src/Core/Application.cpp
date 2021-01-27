#include "Application.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    LPCREATESTRUCT pcs;

    UINT width;
    UINT height;

    int x, y;

    static Application* app;

    switch (message)
    {
        case WM_CREATE:
            pcs = (LPCREATESTRUCT)lParam;
            app = (Application*)pcs->lpCreateParams;
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);

            app->Resize(width, height);
            break;

        case WM_KEYDOWN:
            InputManager::KeyDown((char)wParam);
            break;

        case WM_KEYUP:
            InputManager::KeyUp((char)wParam);
            break;

        case WM_LBUTTONDOWN:
            InputManager::KeyDown(VK_LBUTTON);
            break;

        case WM_LBUTTONUP:
            InputManager::KeyUp(VK_LBUTTON);
            break;
        
        case WM_RBUTTONDOWN:
            InputManager::KeyDown(VK_RBUTTON);
            break;

        case WM_RBUTTONUP:
            InputManager::KeyUp(VK_RBUTTON);
            break;

        case WM_MOUSEMOVE:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            InputManager::MouseMove(x, y);
            break;

        case WM_SETFOCUS:
            InputManager::FocusChange(true);
            break;

        case WM_KILLFOCUS:
            InputManager::FocusChange(false);
            break;

        case WM_MOVE:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            InputManager::WindowMove(x, y);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

Application::Application():
    _hInst(nullptr), _hWnd(nullptr), _driverType(D3D_DRIVER_TYPE_NULL), _featureLevel(D3D_FEATURE_LEVEL_11_0), _pSwapChain(nullptr), _pRenderTargetView(nullptr),
    _pDepthStencilView(nullptr), _pDepthStencilBuffer(nullptr), _pBlendState(nullptr), _pSkyBoxDepthStencilState(nullptr), _pDefaultDepthStencilState(nullptr), _clearColor{ 0.0f, 0.3f, 0.3f, 1.0f }, _time(0.0f)
{

}

Application::~Application()
{
    Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    DebugLogManager::Initialise(true);
    DebugLogManager::Clear();
    DebugLogManager::Log("Starting up");

    if (FAILED(InitWindow(hInstance, nCmdShow)))
    {
        return E_FAIL;
    }

    RECT rc;
    GetClientRect(_hWnd, &rc);
    _WindowWidth = rc.right - rc.left;
    _WindowHeight = rc.bottom - rc.top;


    if (FAILED(InitDevice()))
    {
        Cleanup();

        return E_FAIL;
    }

    InitScene();

    DebugLogManager::Log("Created " + std::to_string(EntityManager::GetEntities().size()) + " entities");
    InputManager::Initialise();

    return S_OK;
}

void Application::Update(float deltaTime)
{
    _time += deltaTime;

    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < entities.size(); i++)
        entities[i]->Update(deltaTime);

    InputManager::Update();
    LightManager::UpdateLights();
}

void Application::Draw()
{
    //Clear the render target and the depth stencil buffers
    DeviceManager::GetContext()->ClearRenderTargetView(_pRenderTargetView, _clearColor);
    DeviceManager::GetContext()->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    //Set the GlobalConstantBuffer (contains variables that don't change between objects)
    GlobalConstantBuffer cb;
    cb.ViewMatrix = CameraManager::GetMainCamera()->GetViewMatrix();
    cb.ProjectionMatrix = CameraManager::GetMainCamera()->GetProjectionMatrix();
    cb.EyePosW = CameraManager::GetMainCamera()->GetPosition();
    cb.gTime = _time;
    cb.numLights = LightManager::GetNumLights();
    _globalConstantBuffer.UpdateSubresource(&cb);

    //Bind the global constant buffer and the light buffer to the shaders
    for (int i = 0; i < _shaders.size(); i++)
    {
        _globalConstantBuffer.Bind(_shaders[i], cGlobalConstantBufferSlot);
        LightManager::BindLightBuffer(_shaders[i], cLightBufferSlot);
    }


    //If an object is opaque, draw it. Else, add it to _transparentObjects
    std::vector<Entity*> _transparentObjects;
    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < entities.size(); i++)
    {
        Material* material;
        material = entities[i]->GetComponent<Material>();

        if (material != nullptr && material->IsTransparent())
            _transparentObjects.push_back(entities[i]);
        else
        {
            //If the object is a skybox, swap _pSkyBoxDepthStencilState, draw it then swap back
            SkyboxRasterState* skyboxRaster = entities[i]->GetComponent<SkyboxRasterState>();
            if (skyboxRaster != nullptr)
            {
                DeviceManager::GetContext()->OMSetDepthStencilState(_pSkyBoxDepthStencilState, 0);
                entities[i]->Draw();
                DeviceManager::GetContext()->OMSetDepthStencilState(_pDefaultDepthStencilState, 0);
            }
            else
                entities[i]->Draw();
        }
    }

    //Sort _transparentObjects so they are back to front, then render them in that order
    std::sort(_transparentObjects.begin(), _transparentObjects.end(), Entity::CompareDistance);

    for (int i = 0; i < _transparentObjects.size(); i++)
        _transparentObjects[i]->Draw();

    _pSwapChain->Present(0, 0);
}

void Application::Resize(UINT width, UINT height)
{
    if (width != 0 && height != 0)
    {
        _WindowWidth = width;
        _WindowHeight = height;

        if (CameraManager::GetMainCamera() != nullptr)
        {
            ResizeRenderTargetView();

            //When the window resizes, the render target view can resize but the depth stencil can't. So we have to release it, then recreate it
            _pDepthStencilBuffer->Release();
            _pDepthStencilView->Release();
            InitDepthStencilBuffer();

            DeviceManager::GetContext()->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);

            InitViewport();

            CameraManager::GetMainCamera()->Reshape(_WindowWidth, _WindowHeight);
        }
    }
}

HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    _hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        this);
    if (!_hWnd)
        return E_FAIL;

    ShowWindow(_hWnd, nCmdShow);

    return S_OK;
}

HRESULT Application::InitDevice()
{
    HRESULT hr = S_OK;

    UINT createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = _WindowWidth;
    sd.BufferDesc.Height = _WindowHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = _hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;


    ID3D11Device* _pd3dDevice;
    ID3D11DeviceContext* _pImmediateContext;

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &sd, &_pSwapChain, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    DeviceManager::Initialise(_pd3dDevice, _pImmediateContext);

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
        return hr;

    hr = DeviceManager::GetDevice()->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    //Set up the depth stencil buffer
    InitDepthStencilBuffer();
    InitDepthStencilStates();

    DeviceManager::GetContext()->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);

    // Setup the viewport
    InitViewport();


    // Set primitive topology
    DeviceManager::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //Initialize the blend state
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = false;

    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    DeviceManager::GetDevice()->CreateBlendState(&blendDesc, &_pBlendState);

    float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    DeviceManager::GetContext()->OMSetBlendState(_pBlendState, blendFactors, 0xFFFFFFFF);

    // Create the local constant buffer
    hr = _localConstantBuffer.Initialise(sizeof(LocalConstantBuffer));
    if (FAILED(hr))
        return hr;

    //Create the global constant buffer
    hr = _globalConstantBuffer.Initialise(sizeof(GlobalConstantBuffer));
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void Application::InitViewport()
{
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)_WindowWidth;
    vp.Height = (FLOAT)_WindowHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    DeviceManager::GetContext()->RSSetViewports(1, &vp);
}

void Application::InitDepthStencilBuffer()
{
    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    depthStencilBufferDesc.Width = _WindowWidth;
    depthStencilBufferDesc.Height = _WindowHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilBufferDesc.SampleDesc.Count = 1;
    depthStencilBufferDesc.SampleDesc.Quality = 0;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;

    DeviceManager::GetDevice()->CreateTexture2D(&depthStencilBufferDesc, nullptr, &_pDepthStencilBuffer);
    DeviceManager::GetDevice()->CreateDepthStencilView(_pDepthStencilBuffer, nullptr, &_pDepthStencilView);
}

void Application::InitDepthStencilStates()
{
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    DeviceManager::GetDevice()->CreateDepthStencilState(&depthStencilDesc, &_pSkyBoxDepthStencilState);

    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    DeviceManager::GetDevice()->CreateDepthStencilState(&depthStencilDesc, &_pDefaultDepthStencilState);

    DeviceManager::GetContext()->OMSetDepthStencilState(_pDefaultDepthStencilState, 0);
}

void Application::Cleanup()
{
    if (_pSwapChain) _pSwapChain->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_pSkyBoxDepthStencilState) _pSkyBoxDepthStencilState->Release();
    if (_pSkyBoxDepthStencilState) _pDefaultDepthStencilState->Release();
    if (_pBlendState) _pBlendState->Release();

    EntityManager::ClearEntities();

    for (int i = 0; i < _meshes.size(); i++)
    {
        //Static meshes delete themselves, so ignore them
        if((_meshes[i] != &Meshes::Cube) && (_meshes[i] != &Meshes::Icosphere) && (_meshes[i] != &Meshes::Pyramid))
            delete _meshes[i];
    }

    for (int i = 0; i < _shaders.size(); i++)
        delete _shaders[i];

    for (int i = 0; i < _textures.size(); i++)
        delete _textures[i];

    //Deallocate static ID3D11RasterizerStates
    SkyboxRasterState::DeallocateStates();

    DebugLogManager::Log("Closing");
}

void Application::InitTextures(const Scene& scene)
{
    for (int i = 0; i < scene.texturePaths.size(); i++)
    {
        std::wstring wideFilePath = std::wstring(scene.texturePaths[i].begin(), scene.texturePaths[i].end()).c_str();
        _textures.push_back(new Texture(wideFilePath.c_str()));
    }
}

void Application::InitMeshes(const Scene& scene)
{
    _meshes.push_back(Meshes::GeneratePlane(32, 8));
    _meshes.push_back(&Meshes::Pyramid);
    _meshes.push_back(&Meshes::Icosphere);
    _meshes.push_back(&Meshes::Cube);

    for (int i = 0; i < scene.modelsPaths.size(); i++)
        _meshes.push_back(OBJLoader::Load(scene.modelsPaths[i].c_str(), true));
}

void Application::InitShaders(const Scene& scene)
{
    // Define the input layouts for lit vertices
    D3D11_INPUT_ELEMENT_DESC lightingLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElementsLighting = ARRAYSIZE(lightingLayout);

    // Define the input layouts for unlit vertices
    D3D11_INPUT_ELEMENT_DESC basicLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElementsBasic = ARRAYSIZE(basicLayout);
    
    for (int i = 0; i < scene.shaderPaths.size(); i++)
    {
        Shader* shader;
        std::wstring wideFilePath = std::wstring(scene.shaderPaths[i].path.begin(), scene.shaderPaths[i].path.end()).c_str();
        switch (scene.shaderPaths[i].type)
        {
            case LIGHT:
                shader = new Shader(wideFilePath.c_str(), lightingLayout, numElementsLighting);
                break;
            case COLOR:
                shader = new Shader(wideFilePath.c_str(), basicLayout, numElementsBasic);
                break;
        }

        _shaders.push_back(shader);
    }
}

void Application::InitEntities(const Scene& scene)
{
    for (int i = 0; i < scene.loadedEntities.size(); i++)
    {
        Entity* newEntity = LoadEntity(scene.loadedEntities[i]);
        EntityManager::AddEntity(newEntity);
    }

    //Parents are initialised as nullptr, as they are indices in the scene file, and an entity may reference one that hasn't been loaded in yet
    //So, we need to set the parents here
    std::vector<Entity*> entities = EntityManager::GetEntities();
    for (int i = 0; i < scene.loadedEntities.size(); i++)
    {
        if (scene.loadedEntities[i].parent != -1)
            entities[i]->ChangeParent(entities[scene.loadedEntities[i].parent]);
    }

    //If no main camera is set, create a default
    if (CameraManager::GetMainCamera() == nullptr)
    {
        Entity* defaultCamera = new Entity(Transform(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1)), nullptr,
            std::vector<Component*>{ new Camera(_WindowWidth, _WindowHeight, 0.1, 100)}, false);
    }
}

Entity* Application::LoadEntity(LoadedEntity entity)
{
    std::vector<Component*> components;
    for (int i = 0; i < entity.components.size(); i++)
    {
        Component* component;

        LoadedMaterial* material;
        LoadedMesh* mesh;
        LoadedRasterState* raster;
        LoadedRotator* rotator;
        LoadedCamera* camera;
        LoadedLight* light;
        LoadedCustomComponent* customComponent;
        LoadedParticleModel* particleModel;
        Texture* diffuse = nullptr;
        Texture* specular = nullptr;
        Texture* ambient = nullptr;

        switch (entity.components[i]->type)
        {
        case MATERIAL:
            material = (LoadedMaterial*)entity.components[i];

            if (material->diffuse != -1)
                diffuse = _textures[material->diffuse];

            if (material->ambient != -1)
                ambient = _textures[material->ambient];

            if (material->specular != -1)
                specular = _textures[material->specular];

            component = new Material(_shaders[material->shader], diffuse, ambient, specular, material->isTransparent,
                material->diffuseMtrl, material->ambientMtrl, material->specularMtrl);
            break;

        case MESH:
            mesh = (LoadedMesh*)entity.components[i];
            component = _meshes[mesh->mesh];
            break;

        case RENDERER:
            component = new Renderer();
            break;

        case RASTER_STATE:
            raster = (LoadedRasterState*)entity.components[i];
            component = new RasterState(raster->startInWireframe);
            break;

        case ROTATOR:
            rotator = (LoadedRotator*)entity.components[i];
            component = new Rotator(rotator->tScale);
            break;

        case RENDERING_BUFFER:
            component = new RenderingBuffers(&_localConstantBuffer);
            break;

        case SELECTION_HIDE:
            component = new SelectionHide();
            break;

        case CAMERA:
            camera = (LoadedCamera*)entity.components[i];
            component = new Camera(_WindowWidth, _WindowHeight, camera->nearDepth, camera->farDepth);
            break;

        case DEBUG_CAMERA_CONTROLLER:
            component = new DebugCameraController();
            break;

        case SCENE_LIGHT:
            light = (LoadedLight*)entity.components[i];
            component = new LightComponent(light->sceneLight);
            break;

        case SKYBOX_RASTER_STATE:
            component = new SkyboxRasterState();
            break;

        case CUSTOM_COMPONENT:
            customComponent = (LoadedCustomComponent*)entity.components[i];
            component = new CustomComponent(customComponent->filePath);
            break;

        case PARTICLE_MODEL:
            particleModel = (LoadedParticleModel*)entity.components[i];
            component = new ParticleModel(particleModel->velocity, particleModel->acceleration, particleModel->angularVelocity, particleModel->angularAcceleration);
            break;
        }

        components.push_back(component);
    }

    Entity* newEntity = new Entity(entity.transform, nullptr, components, entity.selectable);

    return newEntity;
}

void Application::InitScene()
{
    json j;
    std::ifstream file = std::ifstream("Scene.txt");
    j << file;
    file.close();

    Scene scene = j.get<Scene>();

    InitMeshes(scene);
    InitTextures(scene);
    InitShaders(scene);
    InitEntities(scene);

    scene.CleanUp();
}

void Application::ResizeRenderTargetView()
{
    DeviceManager::GetContext()->OMSetRenderTargets(0, 0, 0);
    _pRenderTargetView->Release();

    HRESULT hr = _pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

    ID3D11Texture2D* pBuffer;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
    hr = DeviceManager::GetDevice()->CreateRenderTargetView(pBuffer, NULL, &_pRenderTargetView);

    pBuffer->Release();
}