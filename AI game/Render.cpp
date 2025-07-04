#include "Render.h"
#include "World.h"
#include <cmath>

ID2D1Factory* pFactory = nullptr;
ID2D1HwndRenderTarget* pRenderTarget = nullptr;
ID2D1SolidColorBrush* pBrush = nullptr;

void createRenderTarget(HWND hwnd) {
    RECT rc;
    GetClientRect(hwnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, size),
        &pRenderTarget
    );

    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
}

void DrawTile(int screenX, int screenY, D2D1_COLOR_F color) {
    D2D1_RECT_F rect = D2D1::RectF(screenX, screenY, screenX + TILE_SIZE, screenY - TILE_SIZE);
    pBrush->SetColor(color);
    pRenderTarget->FillRectangle(rect, pBrush);
}

void DrawEntity(float screenX, float screenY, float width, float height, D2D1_COLOR_F color) {
    D2D1_RECT_F rect = D2D1::RectF(screenX, screenY, screenX + width, screenY - height);
    pBrush->SetColor(color);
    pRenderTarget->FillRectangle(rect, pBrush);
}

void drawWorld(const Player& player) {
    float offsetX = SCREEN_WIDTH / 2 - (player.posX + player.width / 2) * TILE_SIZE;
    float offsetY = SCREEN_HEIGHT / 2 - (WORLD_HEIGHT - (player.posY + player.height / 2)) * TILE_SIZE;

    for (int i = 0; i < WORLD_WIDTH; i++) {
        int coordX = TILE_SIZE * i + offsetX;
        if (coordX < -TILE_SIZE || coordX > SCREEN_WIDTH) continue;

        for (int j = WORLD_HEIGHT - 1; j >= 0; j--) {
            int coordY = ((WORLD_HEIGHT - j) * TILE_SIZE) + offsetY;
            if (coordY < -TILE_SIZE || coordY > SCREEN_HEIGHT + TILE_SIZE) continue;
            DrawTile(coordX, coordY, blockColors[getBlock(i,j)]);
        }
    }
}

void drawEntities(const Player& player, std::vector<TestEnemy> TestEnemies) {
    float offsetX = SCREEN_WIDTH / 2 - (player.posX + player.width / 2) * TILE_SIZE;
    float offsetY = SCREEN_HEIGHT / 2 - (WORLD_HEIGHT - (player.posY + player.height / 2)) * TILE_SIZE;

    

    for (int i = 0; i < TestEnemies.size(); i++)
    {
        int coordX = TILE_SIZE * TestEnemies[i].posX + offsetX;
        int coordY = ((WORLD_HEIGHT - TestEnemies[i].posY) * TILE_SIZE) + offsetY;

        DrawEntity(coordX, coordY, TestEnemies[i].width * TILE_SIZE, TestEnemies[i].height * TILE_SIZE, TestEnemies[i].color);
    }

    int coordX = TILE_SIZE * player.posX + offsetX;
    int coordY = ((WORLD_HEIGHT - player.posY) * TILE_SIZE) + offsetY;

    DrawEntity(coordX, coordY, player.width * TILE_SIZE, player.height * TILE_SIZE, player.color);
}
