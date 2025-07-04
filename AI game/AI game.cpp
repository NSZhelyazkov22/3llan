#include "World.h"
#include "Entity.h"
#include "Render.h"
#include "Window.h"
#include <windows.h>
#include <d2d1.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include "AI.h"

Player player(5, 20);
std::vector<TestEnemy> TestEnemies;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    HWND hwnd = CreateMainWindow(hInstance, L"3llan", L"3llan", SCREEN_WIDTH, SCREEN_HEIGHT);
    ShowWindow(hwnd, nCmdShow);

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    createRenderTarget(hwnd);

    fann* TestEnemyGBrain = TestEnemyInit();

    for (int i = 0; i < WORLD_WIDTH; i++)
        for (int j = 0; j < WORLD_HEIGHT; j++) {
            if (i == 0) world[i][j] = (j % 2 == 0) ? BLOCK_GRASS : BLOCK_DIRT;
            if (j == 0) world[i][j] = (i % 2 == 0) ? BLOCK_STONE : BLOCK_WATER;
        }

    //TestEnemies.push_back(TestEnemy{12, 3, TestEnemyGBrain});
    TestEnemies.push_back(TestEnemy{12, 3, TestEnemyGBrain});
    TestEnemies.push_back(TestEnemy{33, 3, TestEnemyGBrain});

    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) goto Exit;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        player.Think();
        for (int i = 0; i < TestEnemies.size(); i++)
        {
            TestEnemies[i].Think(player.posX, player.posY);
        }

        player.Physics();
        for (int i = 0; i < TestEnemies.size(); i++)
        {
            TestEnemies[i].Physics();
        }

        pRenderTarget->BeginDraw();
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        drawWorld(player);
        drawEntities(player, TestEnemies);
        pRenderTarget->EndDraw();
    }

Exit:
    SaveTestEnemyBrain(TestEnemyGBrain);
    if (pBrush) pBrush->Release();
    if (pRenderTarget) pRenderTarget->Release();
    if (pFactory) pFactory->Release();
    return 0;
}
