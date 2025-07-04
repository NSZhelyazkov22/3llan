#pragma once
#include <windows.h>

HWND CreateMainWindow(HINSTANCE hInstance, const wchar_t* className, const wchar_t* windowTitle, int width, int height);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
