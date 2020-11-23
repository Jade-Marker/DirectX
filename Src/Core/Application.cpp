#include "Application.h"

//todo
//Fix wireframe mode for transparent objects
//Add basic camera controller
//Add object picking/raycast
//Sort constant buffer materials
//Add support for multiple textures
//Add support for specular maps
//Add Camera Manager
//Add Object loading via JSON
//Add Custom component
//Add Skybox

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
    _pDepthStencilView(nullptr), _pDepthStencilBuffer(nullptr), _pBlendState(nullptr), _clearColor{ 0.0f, 0.3f, 0.3f, 1.0f },
    _pFishMesh(nullptr), _pPlaneMesh(nullptr), _pLightBuffer(nullptr)
{

}

Application::~Application()
{
    Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
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

    InitConstantBufferVars();
    InitLights();
    InitMeshes();
    InitTextures();
    InitShaders();
    InitEntities();

    DebugLogManager::Clear();
    DebugLogManager::Log("Starting up");

    InputManager::Initialise();

    return S_OK;
}

void Application::Update(float deltaTime)
{
    _time += deltaTime;

    for (int i = 0; i < _entities.size(); i++)
        _entities[i]->Update(deltaTime);

    InputManager::Update();
}

void Application::Draw()
{
    DeviceManager::GetContext()->ClearRenderTargetView(_pRenderTargetView, _clearColor);
    DeviceManager::GetContext()->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


    GlobalConstantBuffer cb;
    cb.ViewMatrix = XMMatrixTranspose(XMLoadFloat4x4(&CameraManager::GetMainCamera()->GetViewMatrix()));
    cb.ProjectionMatrix = XMMatrixTranspose(XMLoadFloat4x4(&CameraManager::GetMainCamera()->GetProjectionMatrix()));
    cb.DiffuseMtrl = _diffuseMaterial;
    cb.AmbientMtrl = _ambientMaterial;
    cb.SpecularMtrl = _specularMaterial;
    cb.EyePosW = CameraManager::GetMainCamera()->GetPosition();
    cb.gTime = _time;
    cb.numLights = _lights.size();
    _globalConstantBuffer.Update(&cb);


    for (int i = 0; i < _shaders.size(); i++)
    {
        _globalConstantBuffer.Bind(_shaders[i], cGlobalConstantBufferSlot);
        _pLightBuffer->Bind(_shaders[i], cLightBufferSlot);
    }

    std::vector<Entity*> _transparentObjects;

    for (int i = 0; i < _entities.size(); i++)
    {
        Material* material;
        material = _entities[i]->GetComponent<Material>();

        if (material != nullptr && material->IsTransparent())
            _transparentObjects.push_back(_entities[i]);
        else
            _entities[i]->Draw();
    }

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
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = _WindowWidth;
    depthStencilDesc.Height = _WindowHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    DeviceManager::GetDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &_pDepthStencilBuffer);
    DeviceManager::GetDevice()->CreateDepthStencilView(_pDepthStencilBuffer, nullptr, &_pDepthStencilView);
}

void Application::Cleanup()
{
    if (_pSwapChain) _pSwapChain->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_pBlendState) _pBlendState->Release();

    for (int i = 0; i < _entities.size(); i++)
        delete _entities[i];

    if (_pFishMesh) delete _pFishMesh;
    if (_pPlaneMesh) delete _pPlaneMesh;

    for (int i = 0; i < _shaders.size(); i++)
        delete _shaders[i];

    for (int i = 0; i < _crateTextures.size(); i++)
        delete _crateTextures[i];

    for (int i = 0; i < _fishTextures.size(); i++)
        delete _fishTextures[i];

    if (_pLightBuffer) delete _pLightBuffer;

    DebugLogManager::Log("Closing");
}

Mesh* Application::GenerateMesh(int width, int height)
{
    std::vector<BasicVertex> verticesVector;
    std::vector<WORD> indices;

   for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float xLower, xUpper, yLower, yUpper;

            xLower = -1.0f + (x * 2.0f);
            xUpper = 1.0f + (x * 2.0f);
            yLower = -1.0f + (y * 2.0f);
            yUpper = 1.0f + (y * 2.0f);

            BasicVertex vertex1 = { XMFLOAT3(xLower, yUpper, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) };
            BasicVertex vertex2 = { XMFLOAT3(xUpper, yUpper, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) };
            BasicVertex vertex3 = { XMFLOAT3(xLower, yLower, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) };
            BasicVertex vertex4 = { XMFLOAT3(xUpper, yLower, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) };

            verticesVector.push_back(vertex1);
            verticesVector.push_back(vertex2);
            verticesVector.push_back(vertex3);
            verticesVector.push_back(vertex4);
        }
    }

    for (int i = 0; i < width * height; i++)
    {
        indices.push_back(0 + 4 * i);
        indices.push_back(1 + 4 * i);
        indices.push_back(2 + 4 * i);
        indices.push_back(2 + 4 * i);
        indices.push_back(1 + 4 * i);
        indices.push_back(3 + 4 * i);
    }

    Mesh* mesh = new Mesh(verticesVector.data(), sizeof(BasicVertex), verticesVector.size(), indices.data(), indices.size());
    return mesh;
}

void Application::InitTextures()
{
    _crateTextures.push_back(new Texture(L"Res\\Textures\\ChainLink(2).dds"));
    _fishTextures.push_back(new Texture(L"Res\\Textures\\fish.dds"));
}

void Application::InitMeshes()
{
    _pFishMesh = OBJLoader::Load("Res\\Models\\fish.obj", true);
    _pPlaneMesh = GenerateMesh(32, 8);
}

void Application::InitShaders()
{
    // Define the input layouts
    D3D11_INPUT_ELEMENT_DESC lightingLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElementsLighting = ARRAYSIZE(lightingLayout);

    D3D11_INPUT_ELEMENT_DESC basicLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElementsBasic = ARRAYSIZE(basicLayout);

    _dx11Shader = new Shader(L"Res\\Shaders\\DX11 Framework.fx", lightingLayout, numElementsLighting);
    _discardShader = new Shader(L"Res\\Shaders\\Discard.fx", basicLayout, numElementsBasic);
    _basicShader = new Shader(L"Res\\Shaders\\BasicShader.fx", basicLayout, numElementsBasic);
    _waterShader = new Shader(L"Res\\Shaders\\Water.fx", basicLayout, numElementsBasic);

    _shaders.push_back(_dx11Shader);
    _shaders.push_back(_discardShader);
    _shaders.push_back(_basicShader);
    _shaders.push_back(_waterShader);
}

void Application::InitConstantBufferVars()
{
    _diffuseMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    _ambientMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    _specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    _time = 0;
}

void Application::InitEntities()
{
    Entity* cube;
    Entity* fish;
    Entity* pyramid1;
    Entity* pyramid2;
    Entity* icosphere;
    Entity* plane;
    Entity* cameraEntity;

    cube = new Entity(
        Transform(XMFLOAT3(0, 0, 5), XMFLOAT3(0, 0, 0), XMFLOAT3(2, 2, 2)), nullptr,
        std::vector<Component*> {new Material(_dx11Shader, _crateTextures, true), &Meshes::Cube, new Renderer(), new RasterState(false), new Rotator(XMFLOAT3(0, 1, 0)), new RenderingBuffers(&_localConstantBuffer)}
    );

    fish = new Entity(
        Transform(XMFLOAT3(0, -6, 5), XMFLOAT3(0, 0, 0), XMFLOAT3(4, 4, 4)), nullptr,
        std::vector<Component*> {new Material(_dx11Shader, _fishTextures, false), _pFishMesh, new Renderer(), new RasterState(false), new Rotator(XMFLOAT3(0, .5f, 0)), new RenderingBuffers(&_localConstantBuffer)}
    );

    pyramid1 = new Entity(
        Transform(XMFLOAT3(5, 0, -3), XMFLOAT3(30, 0, 20), XMFLOAT3(1, 2, 1)), cube,
        std::vector<Component*> {new Material(_basicShader, _blankTextures, false), &Meshes::Pyramid, new Renderer(), new RasterState(false), new Rotator(XMFLOAT3(0, -1, 0)), new RenderingBuffers(&_localConstantBuffer)}
    );

    pyramid2 = new Entity(
        Transform(XMFLOAT3(0, 6, 0), XMFLOAT3(-5, 0, 3), XMFLOAT3(1, 1, 1)), cube,
        std::vector<Component*> {new Material(_basicShader, _blankTextures, false), &Meshes::Pyramid, new Renderer(), new RasterState(false), new Rotator(XMFLOAT3(0.27f, -3.0f, 6)), new RenderingBuffers(&_localConstantBuffer)}
    );

    icosphere = new Entity(
        Transform(XMFLOAT3(-5, 0, 0), XMFLOAT3(30, 0, 20), XMFLOAT3(1, 1, 1)), cube,
        std::vector<Component*> {new Material(_basicShader, _blankTextures, false), &Meshes::Icosphere, new Renderer(), new RasterState(false), new Rotator(XMFLOAT3(-2, 0, 0.5f)), new RenderingBuffers(&_localConstantBuffer)}
    );

    plane = new Entity(
        Transform(XMFLOAT3(-15, -9, 0), XMFLOAT3(70, 0, 0), XMFLOAT3(0.5f, 0.5f, 0.5f)), nullptr,
        std::vector<Component*> {new Material(_waterShader, _blankTextures, true), _pPlaneMesh, new Renderer(), new RasterState(false), new RenderingBuffers(&_localConstantBuffer)}
    );

    Camera* camera = new Camera(_WindowWidth, _WindowHeight, 0.1f, 100.0f);
    CameraManager::SetMainCamera(camera);

    cameraEntity = new Entity(Transform(XMFLOAT3(0.0f, 0.0f, -10.0f), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1)), nullptr,
        std::vector<Component*> {camera}
    );

    _entities.push_back(cube);
    _entities.push_back(fish);
    _entities.push_back(pyramid1);
    _entities.push_back(pyramid2);
    _entities.push_back(icosphere);
    _entities.push_back(cameraEntity);
    _entities.push_back(plane);
}

void Application::InitLights()
{
    Light greenPointLight = PointLight(XMFLOAT3(30, 0.0f, -6.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
        XMFLOAT4(0.0f, 0.4f, 0.0f, 0.4f), XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f), 10.0f, 10.0f, 5.0f, 10.0f);
    Light redPointLight = PointLight(XMFLOAT3(-30, 0.0f, -6.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
        XMFLOAT4(1.0f, 0.0f, 0.0f, 0.4f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f, 5.0f, 10.0f);
    Light basicDirectional = DirectionalLight(XMFLOAT3(0.25f, 0.5f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
        XMFLOAT4(0.0f, 0.0f, 0.4f, 0.4f), XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f), 1.25f, 0.2f, 0.2f, 1.25f);

    _lights.push_back(greenPointLight);
    _lights.push_back(redPointLight);
    _lights.push_back(basicDirectional);

    _pLightBuffer = new StructuredBuffer(_lights.data(), _lights.size(), sizeof(Light));
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