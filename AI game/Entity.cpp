#include "Entity.h"
#include "World.h"
#include <cmath>
#include <xutility>
#include <iostream>

Entity::Entity(float X, float Y)
    : posX(X), posY(Y), velX(0.0f), velY(0.0f) {
}

void Entity::Think()
{
}

void Entity::Think(float playerPosX, float playerPosY)
{
}

void Entity::Physics() {
    bool collideLeft = false, collideRight = false, collideUp = false, collideDown = false;

    if (velY < 0) {
        int left = static_cast<int>(floor(posX));
        int right = static_cast<int>(ceil(posX + width));
        int bottom = static_cast<int>(floor(posY + velY));

        for (int i = left; i < right; ++i)
            if (getBlock(i, bottom) != BLOCK_AIR) { collideDown = true; break; }

        if (collideDown) { posY = bottom + 1.0f; velY = 0; }
        else { posY += velY; velY -= GRAVITY; }
    }
    else if (velY > 0) {
        int left = static_cast<int>(floor(posX));
        int right = static_cast<int>(ceil(posX + width));
        int top = static_cast<int>(floor(posY + velY + height));

        for (int i = left; i < right; ++i)
            if (getBlock(i,top) != BLOCK_AIR) { collideUp = true; break; }

        if (collideUp) { posY = top - height; velY = 0; }
        else { posY += velY; velY -= GRAVITY; }
    }
    else { posY += velY; velY -= GRAVITY; }

    if (velX < 0) {
        int bottom = static_cast<int>(floor(posY));
        int top = static_cast<int>(ceil(posY + height));
        int left = static_cast<int>(floor(posX + velX));

        for (int i = bottom; i < top; ++i)
            if (getBlock(left,i) != BLOCK_AIR) { collideLeft = true; break; }

        if (collideLeft) { posX = left + 1.0f; velX = 0; }
        else {
            posX += velX;
            velX += (velX + friction < 0) ? friction : -velX;
        }
    }
    else if (velX > 0) {
        int bottom = static_cast<int>(floor(posY));
        int top = static_cast<int>(ceil(posY + height));
        int right = static_cast<int>(floor(posX + velX + width));

        for (int i = bottom; i < top; ++i)
            if (getBlock(right, i) != BLOCK_AIR) { collideRight = true; break; }

        if (collideRight) { posX = right - width; velX = 0; }
        else {
            posX += velX;
            velX -= (velX - friction > 0) ? friction : velX;
        }
    }
    else { posX += velX; }
}

void Entity::Left() { if (velX > -0.15f) velX -= acceleration; }
void Entity::Right() { if (velX < 0.15f) velX += acceleration; }
void Entity::Up() { if (velY == 0) velY = 0.13f; }



void Player::Think() {
    if (GetAsyncKeyState('A') & 0x8000) Player::Left();
    if (GetAsyncKeyState('D') & 0x8000) Player::Right();
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) Player::Up();
}

void Player::ForceUp() {velY = 0.13f;}

void TestEnemy::Think(float playerPosX, float playerPosY)
{
    //if (posX > playerPosX) TestEnemy::Left();
    //if (posX < playerPosX) TestEnemy::Right();
    //return;
    
    float input[3];
    input[0] = playerPosX - posX;
    input[1] = playerPosY - posY;
    input[2] = posX / 100.0f;

    float* output = fann_run(indBrain, input);

    bool movedTowardPlayer = false;
    if (output[0] > 0.5f) {
        if (velY == 0) Right();
        if (playerPosX > posX)
            movedTowardPlayer = true;
    }
    else if (output[1] > 0.5f) {
        if (velY == 0) Left();
        if (playerPosX < posX)
            movedTowardPlayer = true;
    }

    if (output[2] > 0.5f) {
        Up();
        velX = 0;
        if (playerPosY > posY)
        {
            movedTowardPlayer = true;
        }
    }

    if (!movedTowardPlayer) {
        float desiredOutput[3] = {0.0f, 0.0f, 0.0f};
        if (playerPosX > posX)
        {
            desiredOutput[0] = 1.0f;
        }
        if (playerPosX < posX)
        {
            desiredOutput[1] = 1.0f;
        }
        if (playerPosY > posY)
        {
            desiredOutput[2] = 1.0f;
        }

        fann_train(indBrain, input, desiredOutput);
    }
}