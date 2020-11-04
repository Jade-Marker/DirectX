#include "Application.h"

//todo
//Do a general cleanup of code before moving onto next step
//Extract light stuff out to a class/struct
//Clean up Mesh/Vertices code

//Add support for multiple textures
//Use the specular map for the crate
//Add point, spotlight and directional light based on examples in chapter 7

static LightVertex cubeVertices[] =
{
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-0.5773502692f, 0.5773502692f, -0.5773502692f),   XMFLOAT2(0.0f,0.0f) },       //0
    { XMFLOAT3(1.0f, 1.0f, -1.0f),  XMFLOAT3(0.5773502692f, 0.5773502692f, -0.5773502692f),    XMFLOAT2(1.0f,0.0f) },       //1
    { XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT3(-0.5773502692f, -0.5773502692f, -0.5773502692f),  XMFLOAT2(0.0f,1.0f) },       //2
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.5773502692f, -0.5773502692f, -0.5773502692f),   XMFLOAT2(1.0f,1.0f) },       //3

    { XMFLOAT3(1.0f, 1.0f, -1.0f),  XMFLOAT3(0.5773502692f, 0.5773502692f, -0.5773502692f),    XMFLOAT2(0.0f,0.0f) },       //4
    { XMFLOAT3(1.0f, 1.0f, 1.0f),   XMFLOAT3(0.5773502692f, 0.5773502692f, 0.5773502692f),     XMFLOAT2(1.0f,0.0f) },       //5
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.5773502692f, -0.5773502692f, -0.5773502692f),   XMFLOAT2(0.0f,1.0f) },       //6
    { XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT3(0.5773502692f, -0.5773502692f, 0.5773502692f),    XMFLOAT2(1.0f,1.0f) },       //7

    { XMFLOAT3(1.0f, 1.0f, 1.0f),   XMFLOAT3(0.5773502692f, 0.5773502692f, 0.5773502692f),     XMFLOAT2(1.0f,0.0f) },       //8
    { XMFLOAT3(-1.0f, 1.0f, 1.0f),  XMFLOAT3(-0.5773502692f, 0.5773502692f, 0.5773502692f),    XMFLOAT2(0.0f,0.0f) },       //9
    { XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT3(0.5773502692f, -0.5773502692f, 0.5773502692f),    XMFLOAT2(1.0f,1.0f) },       //10
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-0.5773502692f, -0.5773502692f, 0.5773502692f),   XMFLOAT2(0.0f,1.0f) },       //11

    { XMFLOAT3(-1.0f, 1.0f, 1.0f),  XMFLOAT3(-0.5773502692f, 0.5773502692f, 0.5773502692f),    XMFLOAT2(0.0f,0.0f) },       //12
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-0.5773502692f, 0.5773502692f, -0.5773502692f),   XMFLOAT2(1.0f,0.0f) },       //13
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-0.5773502692f, -0.5773502692f, 0.5773502692f),   XMFLOAT2(0.0f,1.0f) },       //14
    { XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT3(-0.5773502692f, -0.5773502692f, -0.5773502692f),  XMFLOAT2(1.0f,1.0f) },       //15

    { XMFLOAT3(-1.0f, 1.0f, 1.0f),  XMFLOAT3(-0.5773502692f, 0.5773502692f, 0.5773502692f),    XMFLOAT2(0.0f,0.0f) },       //16
    { XMFLOAT3(1.0f, 1.0f, 1.0f),   XMFLOAT3(0.5773502692f, 0.5773502692f, 0.5773502692f),     XMFLOAT2(1.0f,0.0f) },       //17
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-0.5773502692f, 0.5773502692f, -0.5773502692f),   XMFLOAT2(0.0f,1.0f) },       //18
    { XMFLOAT3(1.0f, 1.0f, -1.0f),  XMFLOAT3(0.5773502692f, 0.5773502692f, -0.5773502692f),    XMFLOAT2(1.0f,1.0f) },       //19


    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-0.5773502692f, -0.5773502692f, 0.5773502692f),   XMFLOAT2(0.0f,0.0f) },       //20
    { XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT3(-0.5773502692f, -0.5773502692f, -0.5773502692f),  XMFLOAT2(1.0f,0.0f) },       //21
    { XMFLOAT3(1.0f, -1.0f, 1.0f),  XMFLOAT3(0.5773502692f, -0.5773502692f, 0.5773502692f),    XMFLOAT2(0.0f,1.0f) },       //22
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.5773502692f, -0.5773502692f, -0.5773502692f),   XMFLOAT2(1.0f,1.0f) },       //23

};

static Vertices cube = Vertices((void*)cubeVertices, sizeof(cubeVertices), sizeof(cubeVertices)/sizeof(cubeVertices[0]));

static WORD cubeIndices[] =
{
    0, 1, 2,
    2, 1, 3,

    4, 5, 6,
    6, 5, 7,

    8, 9,10,
    10,9,11,

    12,13,14,
    14,13,15,

    16,17,18,
    18,17,19,

    20,21,22,
    22,21,23
};

static BasicVertex pyramidVertices[] =
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
static Vertices pyramid = Vertices((void*)pyramidVertices, sizeof(pyramidVertices), sizeof(pyramidVertices) / sizeof(pyramidVertices[0]));


static BasicVertex icosphereVertices[] =
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
static Vertices icosphere = Vertices((void*)icosphereVertices, sizeof(icosphereVertices), sizeof(icosphereVertices) / sizeof(icosphereVertices[0]));


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

    Vertices* vertices = new Vertices(verticesVector.data(), verticesVector.size() * sizeof(BasicVertex), verticesVector.size(), true);
    Mesh* mesh = new Mesh(vertices, indices.data(), indices.size());
    return mesh;
}

Application::Application():
    _camera(XMFLOAT3(0.0f, 0.0f, -10.0f))
{
	_hInst = nullptr;
	_hWnd = nullptr;
	_driverType = D3D_DRIVER_TYPE_NULL;
	_featureLevel = D3D_FEATURE_LEVEL_11_0;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pRenderTargetView = nullptr;
	_pLocalConstantBuffer = nullptr;
	_pGlobalConstantBuffer = nullptr;

    _pDepthStencilView   = nullptr;
    _pDepthStencilBuffer = nullptr;
    _pBlendState        = nullptr;
    _pCubeMesh           = nullptr;
    _pFishMesh            = nullptr;
    _pPyramidMesh        = nullptr;
    _pIcosphereMesh      = nullptr;
    _pPlaneMesh          = nullptr;
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
    InitMeshes();
    InitTextures();
    InitSceneObjects();

	return S_OK;
}

void Application::InitTextures()
{
    _crateTextures.push_back(new Texture(_pd3dDevice, L"Crate_COLOR.dds"));
    _fishTextures.push_back(new Texture(_pd3dDevice, L"fish.dds"));
}

void Application::InitMeshes()
{
    _pCubeMesh = new Mesh(&cube, cubeIndices, sizeof(cubeIndices) / sizeof(WORD));
    _pFishMesh = OBJLoader::Load("fish.obj", _pd3dDevice, true);
    _pPyramidMesh = new Mesh(&pyramid, pyramidIndices, sizeof(pyramidIndices) / sizeof(WORD));
    _pIcosphereMesh = new Mesh(&icosphere, icosphereIndices, sizeof(icosphereIndices) / sizeof(WORD));
    _pPlaneMesh = GenerateMesh(32, 8);
}

void Application::InitConstantBufferVars()
{
    _lightDirection = XMFLOAT3(0.25f, 0.5f, -1.0f);
    _diffuseMaterial = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
    _diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    _ambientMaterial = XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f);
    _ambientLight = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.4f);
    _specularMaterial = XMFLOAT4(0.0f, 0.8f, 0.0f, 1.0f);
    _specularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    _specularPower = 10.0f;
    _time = 0;

    // Initialize the projection matrix
    XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));
}

void Application::InitSceneObjects()
{
    SceneObject* cube;
    SceneObject* fish;
    SceneObject* pyramid1;
    SceneObject* pyramid2;
    SceneObject* icosphere;
    SceneObject* plane;
    Shader* _dx11Shader;
    Shader* _discardShader;
    Shader* _basicShader;
    Shader* _waterShader;

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

    _dx11Shader = new Shader(L"DX11 Framework.fx", lightingLayout, numElementsLighting, _pd3dDevice, _pImmediateContext);
    _discardShader = new Shader(L"Discard.fx", basicLayout, numElementsBasic, _pd3dDevice, _pImmediateContext);
    _basicShader = new Shader(L"BasicShader.fx", basicLayout, numElementsBasic, _pd3dDevice, _pImmediateContext);
    _waterShader = new Shader(L"Water.fx", basicLayout, numElementsBasic, _pd3dDevice, _pImmediateContext);

    _shaders.push_back(_dx11Shader);
    _shaders.push_back(_discardShader);
    _shaders.push_back(_basicShader);
    _shaders.push_back(_waterShader);

    cube = new SceneObject(
        XMFLOAT3(0, 0, 5),
        XMFLOAT3(0, 0, 0),
        XMFLOAT3(2, 2, 2),
        XMFLOAT3(0, 1, 0), nullptr, _pCubeMesh, false, _dx11Shader,
        _pd3dDevice, _pImmediateContext, _pLocalConstantBuffer, _crateTextures
    );

    fish = new SceneObject(
        XMFLOAT3(0, -6, 5),
        XMFLOAT3(0, 0, 0),
        XMFLOAT3(4, 4, 4),
        XMFLOAT3(0, .5f, 0), nullptr, _pFishMesh, false, _dx11Shader,
        _pd3dDevice, _pImmediateContext, _pLocalConstantBuffer, _fishTextures
    );

    pyramid1 = new SceneObject(
        XMFLOAT3(5, 0, -3),
        XMFLOAT3(30, 0, 20),
        XMFLOAT3(1, 2, 1),
        XMFLOAT3(0, -1, 0), cube, _pPyramidMesh, false, _basicShader,
        _pd3dDevice, _pImmediateContext, _pLocalConstantBuffer, _blankTextures
    );

    pyramid2 = new SceneObject(
        XMFLOAT3(0, 6, 0),
        XMFLOAT3(-5, 0, 3),
        XMFLOAT3(1, 1, 1),
        XMFLOAT3(0.27f, -3.0f, 6), cube, _pPyramidMesh, false, _basicShader,
        _pd3dDevice, _pImmediateContext, _pLocalConstantBuffer, _blankTextures
    );

    icosphere = new SceneObject(
        XMFLOAT3(-5, 0, 0),
        XMFLOAT3(30, 0, 20),
        XMFLOAT3(1, 1, 1),
        XMFLOAT3(-2, 0, 0.5f), cube, _pIcosphereMesh, false, _basicShader,
        _pd3dDevice, _pImmediateContext, _pLocalConstantBuffer, _blankTextures
    );

    plane = new SceneObject(
        XMFLOAT3(-15, -9, 0),
        XMFLOAT3(70, 0, 0),
        XMFLOAT3(0.5f, 0.5f, 0.5f),
        XMFLOAT3(0, 0, 0), nullptr, _pPlaneMesh, false, _waterShader,
        _pd3dDevice, _pImmediateContext, _pLocalConstantBuffer, _blankTextures
    );

    _sceneObjects.push_back(cube);
    _sceneObjects.push_back(fish);
    _sceneObjects.push_back(pyramid1);
    _sceneObjects.push_back(pyramid2);
    _sceneObjects.push_back(icosphere);
    _sceneObjects.push_back(plane);
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

    _pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_pDepthStencilBuffer);
    _pd3dDevice->CreateDepthStencilView(_pDepthStencilBuffer, nullptr, &_pDepthStencilView);

    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);

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

	// Create the local constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(LocalConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pLocalConstantBuffer);

    if (FAILED(hr))
        return hr;

    //Create the global constant buffer
    bd.ByteWidth = sizeof(GlobalConstantBuffer);
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pGlobalConstantBuffer);

    if (FAILED(hr))
        return hr;

    return S_OK;
}

void Application::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();

    if (_pLocalConstantBuffer) _pLocalConstantBuffer->Release();
    if (_pGlobalConstantBuffer) _pGlobalConstantBuffer->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();

    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();

    for (int i = 0; i < _sceneObjects.size(); i++)
        delete _sceneObjects[i];

    if(_pCubeMesh) delete _pCubeMesh;
    if(_pFishMesh) delete _pFishMesh;
    if(_pPyramidMesh) delete _pPyramidMesh;
    if(_pIcosphereMesh) delete _pIcosphereMesh;
    if(_pPlaneMesh) delete _pPlaneMesh;

    for (int i = 0; i < _shaders.size(); i++)
        delete _shaders[i];

    for (int i = 0; i < _crateTextures.size(); i++)
        delete _crateTextures[i];

    for (int i = 0; i < _fishTextures.size(); i++)
        delete _fishTextures[i];
}

void Application::Update(float deltaTime)
{
    _time += deltaTime;

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
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


    GlobalConstantBuffer cb;
    cb.ViewMatrix           = XMMatrixTranspose(XMLoadFloat4x4(&_camera.GetViewMatrix()));
    cb.ProjectionMatrix     = XMMatrixTranspose(XMLoadFloat4x4(&_projection));
    cb.DiffuseMtrl     = _diffuseMaterial;
    cb.DiffuseLight    = _diffuseLight;
    cb.AmbientMtrl     = _ambientMaterial;
    cb.AmbientLight    = _ambientLight;
    cb.SpecularMtrl    = _specularMaterial;
    cb.SpecularLight   = _specularLight;
    cb.EyePosW         = _camera.GetPosition();
    cb.SpecularPower   = _specularPower;
    cb.LightVecW       = _lightDirection;
    cb.gTime           = _time;

    _pImmediateContext->UpdateSubresource(_pGlobalConstantBuffer, 0, nullptr, &cb, 0, 0);

    for (int i = 0; i < _shaders.size(); i++)
        _shaders[i]->SetConstantBuffers(cGlobalConstantBufferSlot, 1, &_pGlobalConstantBuffer);

    for (int i = 0; i < _sceneObjects.size(); i++)
        _sceneObjects[i]->Draw();

    //
    // Present our back buffer to our front buffer
    //

    _pSwapChain->Present(0, 0);
}