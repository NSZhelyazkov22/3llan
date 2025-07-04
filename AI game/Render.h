#pragma once
#include <d2d1.h>
#include "Entity.h"
#include <vector>

extern ID2D1Factory* pFactory;
extern ID2D1HwndRenderTarget* pRenderTarget;
extern ID2D1SolidColorBrush* pBrush;

void createRenderTarget(HWND hwnd);
void drawWorld(const Player& player);
void drawEntities(const Player& player, std::vector<TestEnemy> TestEnemies);
