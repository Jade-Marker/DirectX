#include "Application.h"
#include <chrono>

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
            static auto timeOld = std::chrono::system_clock::now();
            auto timeNow = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsed = timeNow - timeOld;
            float deltaTime = elapsed.count();

            if(deltaTime > 0.0f)
            {
                theApp->Update(deltaTime);
                theApp->Draw();

                timeOld = timeNow;
            }
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}