#pragma once
#include <d2d1.h>

// Screen and World Settings
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
constexpr int TILE_SIZE = 32;
constexpr int WORLD_HEIGHT = 30;
constexpr int WORLD_WIDTH = 100;

// Physics Constants
constexpr float GRAVITY = 0.006f;
constexpr float JUMP_FORCE = 0.134f;
constexpr float MAX_FALL_SPEED = 10.0f;
constexpr float MOVE_SPEED = 3.5f;

// Block Types
enum BlockType {
    BLOCK_AIR,
    BLOCK_DIRT,
    BLOCK_GRASS,
    BLOCK_STONE,
    BLOCK_WATER,
    BLOCK_BEDROCK,
    BLOCK_COUNT
};

// Global Arrays
extern D2D1_COLOR_F blockColors[BLOCK_COUNT];
extern BlockType world[WORLD_WIDTH][WORLD_HEIGHT];

BlockType getBlock(int x, int y);