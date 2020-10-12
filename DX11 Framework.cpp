#include "Application.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            static DWORD dwTimeStart = 0;

            if (dwTimeStart == 0)
                dwTimeStart = GetTickCount();

            static float timeOld;
            float time = (GetTickCount() - dwTimeStart) / 1000.0f;

            float deltaTime = time - timeOld;

			theApp->Update(deltaTime);
            theApp->Draw();

            timeOld = time;
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}