#include "Window.h"
#include "Render.h"
#include "World.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_SIZE:
        if (pRenderTarget && (LOWORD(lParam) != 0 || HIWORD(lParam) != 0)) {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            D2D1_SIZE_U size = D2D1::SizeU(width, height);
            pRenderTarget->Resize(size);

            SCREEN_WIDTH = width;
            SCREEN_HEIGHT = height;
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreateMainWindow(HINSTANCE hInstance, const wchar_t* className, const wchar_t* windowTitle, int width, int height) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    RegisterClass(&wc);

    return CreateWindowEx(0, className, windowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, hInstance, nullptr);
}
