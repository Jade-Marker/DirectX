#include "Application.h"

static SimpleVertex cubeVertices[] =
{
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },     //0
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },      //1
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },    //2
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },     //3

    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },      //4
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },       //5
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 5.0f, 1.0f) },     //6
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },      //7
};

static WORD cubeIndices[] =
{
    0,1,2,
    2,1,3,

    1,5,3,
    3,5,7,

    5,4,7,
    7,4,6,

    4,0,6,
    6,0,2,

    4,5,0,
    0,5,1,

    6,2,3,
    7,6,3
};

static SimpleVertex pyramidVertices[] =
{
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },      //0
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },       //1
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },     //2
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },      //3

    { XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },       //4
};

static WORD pyramidIndices[] =
{
    0,2,1,
    1,2,3,

    0,1,4,
    1,3,4,
    3,2,4,
    2,0,4
};

static SimpleVertex icosphereVertices[] =
{
    { XMFLOAT3( 0.0f,        -1.000000f,  0.000000f), XMFLOAT4(1.0f,                       1.0f,                       1.0f,                       1.0f) },     //0
    { XMFLOAT3(0.7236f,      -0.447215f,  0.525720f), XMFLOAT4(1.0f - (0.25f / 3.0f) * 1,  1.0f - (0.25f / 3.0f) * 1,  1.0f - (0.25f / 3.0f) * 1,  1.0f) },     //1
    { XMFLOAT3(-0.276385f,   -0.447215f, 0.850640f),  XMFLOAT4(1.0f - (0.25f / 3.0f) * 2,  1.0f - (0.25f / 3.0f) * 2,  1.0f - (0.25f / 3.0f) * 2,  1.0f) },     //2
    { XMFLOAT3(-0.894425f,   -0.447215f, 0.000000f),  XMFLOAT4(1.0f - (0.25f / 3.0f) * 3,  1.0f - (0.25f / 3.0f) * 3,  1.0f - (0.25f / 3.0f) * 3,  1.0f) },     //3
    { XMFLOAT3(-0.276385f,   -0.447215f, -0.850640f), XMFLOAT4(1.0f - (0.25f / 3.0f) * 4,  1.0f - (0.25f / 3.0f) * 4,  1.0f - (0.25f / 3.0f) * 4,  1.0f) },     //4
    { XMFLOAT3(0.723600f,    -0.447215f,  -0.525720f),XMFLOAT4(1.0f - (0.25f / 3.0f) * 5,  1.0f - (0.25f / 3.0f) * 5,  1.0f - (0.25f / 3.0f) * 5,  1.0f) },     //5
    { XMFLOAT3(0.276385f,     0.447215f, 0.850640f),  XMFLOAT4(1.0f - (0.25f / 3.0f) * 6,  1.0f - (0.25f / 3.0f) * 6,  1.0f - (0.25f / 3.0f) * 6,  1.0f) },     //6
    { XMFLOAT3(-0.723600f,    0.447215f,  0.525720f), XMFLOAT4(1.0f - (0.25f / 3.0f) * 7,  1.0f - (0.25f / 3.0f) * 7,  1.0f - (0.25f / 3.0f) * 7,  1.0f) },     //7
    { XMFLOAT3(-0.723600f,    0.447215f,  -0.525720f),XMFLOAT4(1.0f - (0.25f / 3.0f) * 8,  1.0f - (0.25f / 3.0f) * 8,  1.0f - (0.25f / 3.0f) * 8,  1.0f) },     //8
    { XMFLOAT3(0.276385f,     0.447215f, -0.850640f), XMFLOAT4(1.0f - (0.25f / 3.0f) * 9,  1.0f - (0.25f / 3.0f) * 9,  1.0f - (0.25f / 3.0f) * 9,  1.0f) },     //9
    { XMFLOAT3(0.894425f,     0.447215f, 0.000000f),  XMFLOAT4(1.0f - (0.25f / 3.0f) * 10, 1.0f - (0.25f / 3.0f) * 10, 1.0f - (0.25f / 3.0f) * 10, 1.0f) },     //10
    { XMFLOAT3(0.000000f,     1.000000f, 0.000000f),  XMFLOAT4(1.0f - (0.25f / 3.0f) * 11, 1.0f - (0.25f / 3.0f) * 11, 1.0f - (0.25f / 3.0f) * 11, 1.0f) },     //11
};

static WORD icosphereIndices[] =
{
   0, 1, 2,
   1, 0, 5,
   0, 2, 3,
   0, 3, 4,

   0, 4, 5,
   1, 5, 10,
   2, 1, 6,
   3, 2, 7,

   4, 3, 8,
   5, 4, 9,
   1, 10,6,
   2, 6, 7,

   3, 7, 8,
   4, 8, 9,
   5, 9,10,
   6, 10,11,

   7, 6, 11,
   8, 7, 11,
   9,8, 11,
   10,9,11,

};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

Mesh* Application::GenerateMesh(int width, int height)
{
    std::vector<SimpleVertex> vertices;
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

            SimpleVertex vertex1 = { XMFLOAT3(xLower, yUpper, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) };
            SimpleVertex vertex2 = { XMFLOAT3(xUpper, yUpper, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) };
            SimpleVertex vertex3 = { XMFLOAT3(xLower, yLower, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) };
            SimpleVertex vertex4 = { XMFLOAT3(xUpper, yLower, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) };

            vertices.push_back(vertex1);
            vertices.push_back(vertex2);
            vertices.push_back(vertex3);
            vertices.push_back(vertex4);
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

    Mesh* mesh = new Mesh(vertices.data(), vertices.size(), indices.data(), indices.size());
    return mesh;
}

Application::Application()
{
	_hInst = nullptr;
	_hWnd = nullptr;
	_driverType = D3D_DRIVER_TYPE_NULL;
	_featureLevel = D3D_FEATURE_LEVEL_11_0;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pRenderTargetView = nullptr;
	_pConstantBuffer = nullptr;
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

	// Initialize the world matrix
	XMStoreFloat4x4(&_world, XMMatrixIdentity());

    // Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));

    // Initialize the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT) _WindowHeight, 0.01f, 100.0f));

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

    _pd3dDevice->CreateBlendState(&blendDesc, &_pBlendState);

    float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    _pImmediateContext->OMSetBlendState(_pBlendState, blendFactors, 0xFFFFFFFF);

    _cubeMesh = new Mesh(cubeVertices, sizeof(cubeVertices) / sizeof(SimpleVertex), cubeIndices, sizeof(cubeIndices) / sizeof(WORD));
    _pyramidMesh = new Mesh(pyramidVertices, sizeof(pyramidVertices) / sizeof(SimpleVertex), pyramidIndices, sizeof(pyramidIndices) / sizeof(WORD));
    _icosphereMesh = new Mesh(icosphereVertices, sizeof(icosphereVertices) / sizeof(SimpleVertex), icosphereIndices, sizeof(icosphereIndices) / sizeof(WORD));
    _planeMesh = GenerateMesh(32,8);

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT numElements = ARRAYSIZE(layout);

    _dx11Shader = new Shader(L"DX11 Framework.fx", layout, numElements, _pd3dDevice, _pImmediateContext);
    _discardShader = new Shader(L"Discard.fx", layout, numElements, _pd3dDevice, _pImmediateContext);
    _basicShader = new Shader(L"BasicShader.fx", layout, numElements, _pd3dDevice, _pImmediateContext);
    _waterShader = new Shader(L"Water.fx", layout, numElements, _pd3dDevice, _pImmediateContext);

    SceneObject* cube;
    SceneObject* cube2;
    SceneObject* pyramid1;
    SceneObject* pyramid2;
    SceneObject* icosphere;
    SceneObject* plane;

    cube = new SceneObject(
        XMFLOAT3(0, 0, 5),
        XMFLOAT3(0, 0, 0),
        XMFLOAT3(2, 2, 2),
        XMFLOAT3(0, 1, 0), nullptr, _cubeMesh, false, _discardShader,
        _pd3dDevice, _pImmediateContext, _pConstantBuffer
    );

    cube2 = new SceneObject(
        XMFLOAT3(0, -9, 3),
        XMFLOAT3(35, 0, 0),
        XMFLOAT3(0.5f, 1, 1),
        XMFLOAT3(0, 1, 0), nullptr, _cubeMesh, false, _discardShader,
        _pd3dDevice, _pImmediateContext, _pConstantBuffer
    );

    pyramid1 = new SceneObject(
        XMFLOAT3(5, 0, -3),
        XMFLOAT3(30, 0, 20),
        XMFLOAT3(1, 2, 1),
        XMFLOAT3(0, -1, 0), cube, _pyramidMesh, false, _dx11Shader,
        _pd3dDevice, _pImmediateContext, _pConstantBuffer
    );                                
                                         
    pyramid2 = new SceneObject(
        XMFLOAT3(0, 6, 0),               
        XMFLOAT3(-5, 0, 3),
        XMFLOAT3(1, 1, 1),
        XMFLOAT3(0.27f, -3.0f,6), cube, _pyramidMesh, false, _dx11Shader,
        _pd3dDevice, _pImmediateContext, _pConstantBuffer
    );                                   
                                         
    icosphere = new SceneObject(
        XMFLOAT3(-5, 0, 0),              
        XMFLOAT3(30, 0, 20),
        XMFLOAT3(1, 1, 1),
        XMFLOAT3(-2, 0, 0.5f), cube, _icosphereMesh, false, _dx11Shader,
        _pd3dDevice, _pImmediateContext, _pConstantBuffer
    );

    plane = new SceneObject(
        XMFLOAT3(-15, -9, 0),
        XMFLOAT3(70, 0, 0),
        XMFLOAT3(0.5f, 0.5f, 0.5f),
        XMFLOAT3(0, 0, 0), nullptr, _planeMesh, false, _waterShader,
        _pd3dDevice, _pImmediateContext, _pConstantBuffer
    );

    _sceneObjects.push_back(cube);
    _sceneObjects.push_back(cube2);
    _sceneObjects.push_back(pyramid1);
    _sceneObjects.push_back(pyramid2);
    _sceneObjects.push_back(icosphere);
    _sceneObjects.push_back(plane);
	return S_OK;
}

HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW );
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    _hInst = hInstance;
    RECT rc = {0, 0, 640, 480};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                         nullptr);
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

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
        return hr;

    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
        return hr;

    //Set up the depth stencil buffer
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

    _pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
    _pd3dDevice->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)_WindowWidth;
    vp.Height = (FLOAT)_WindowHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    _pImmediateContext->RSSetViewports(1, &vp);


    // Set primitive topology
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void Application::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();

    if (_pConstantBuffer) _pConstantBuffer->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();

    if (_depthStencilView) _depthStencilView->Release();
    if (_depthStencilBuffer) _depthStencilBuffer->Release();

    for (int i = 0; i < _sceneObjects.size(); i++)
        delete _sceneObjects[i];

    delete _cubeMesh;
    delete _pyramidMesh;
    delete _icosphereMesh;
    delete _planeMesh;

    delete _dx11Shader;
    delete _basicShader;
    delete _discardShader;
    delete _waterShader;
}

void Application::Update(float deltaTime)
{
    for (int i = 0; i < _sceneObjects.size(); i++)
        _sceneObjects[i]->Update(deltaTime);
}

void Application::Draw()
{
    //
    // Clear the back buffer
    //

    float ClearColor[4] = {0.0f, 0.3f, 0.3f, 1.0f}; // red,green,blue,alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    _pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    for (int i = 0; i < _sceneObjects.size(); i++)
        _sceneObjects[i]->Draw(_view, _projection);

    //
    // Present our back buffer to our front buffer
    //

    _pSwapChain->Present(0, 0);
}