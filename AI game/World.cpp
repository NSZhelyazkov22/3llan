#include "World.h"
#include <cstdlib>
#include <ctime>

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

D2D1_COLOR_F blockColors[BLOCK_COUNT] = {
    D2D1::ColorF(D2D1::ColorF::SkyBlue),
    D2D1::ColorF(D2D1::ColorF::SaddleBrown),
    D2D1::ColorF(D2D1::ColorF::LimeGreen),
    D2D1::ColorF(D2D1::ColorF::Gray),
    D2D1::ColorF(D2D1::ColorF::Blue),
    D2D1::ColorF(D2D1::ColorF::DarkRed),
};

BlockType world[WORLD_WIDTH][WORLD_HEIGHT] = {};

BlockType getBlock(int x, int y)
{
    BlockType block = BLOCK_AIR;
    if (x < WORLD_WIDTH && y < WORLD_HEIGHT && y >= 0 && x >= 0)
    {
        block = world[x][y];
    }
    return block;
}